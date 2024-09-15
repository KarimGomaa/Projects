/******************************************************************************
 *
 * File Name: external_commands.c
 *
 * Description: Source file for the external commands and contain one internal command which is PHIST
 *
 * Author: Karim Gomaa
 *
 *******************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>

constexpr unsigned int MAX_BUFFER = 128;  /* Maximum buffer size for incoming messages */
constexpr unsigned int MSG_REPLY_LENGTH = 18;  /* Length of the reply message sent to clients */

int main(int argc, char *argv[])
{
    if (argc < 2) {  /* Check if port number is provided */
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return 1;
    }

    unsigned int serverPort = atoi(argv[1]);  /* Port passed as a command-line argument */

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);  /* Create a socket for the server */

    if (sockfd < 0) {  /* Check if socket creation was successful */
        std::cerr << "Failed to open socket" << std::endl;
        return 1;
    }

    int optval = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *) &optval, sizeof(int));  /* Set socket options to reuse address */

    struct sockaddr_in serv_addr, cli_addr;
    bzero((char *) &serv_addr, sizeof(serv_addr));  /* Zero out the server address structure */
    serv_addr.sin_family = AF_INET;  /* Set the address family to IPv4 */
    serv_addr.sin_addr.s_addr = INADDR_ANY;  /* Accept connections from any IP address */
    serv_addr.sin_port = htons(serverPort);  /* Set the port number */

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {  /* Bind the socket to the address */
        std::cerr << "Bind error" << std::endl;
        close(sockfd);  /* Close the socket on error */
        return 2;
    }

    listen(sockfd, 5);  /* Listen for incoming connections with a backlog of 5 */

    std::cout << "Server listening on port " << serverPort << std::endl;

    bool serverRunning = true;  /* Flag to keep the server running */

    while (serverRunning) {  /* Keep the server running until manually stopped */
        socklen_t clilen = sizeof(cli_addr);
        int incomingSock = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);  /* Accept incoming connections */

        if (incomingSock < 0) {  /* Check if connection acceptance was successful */
            std::cerr << "Accept error" << std::endl;
            close(sockfd);  /* Close the server socket on error */
            return 3;
        }

        std::cout << "Server: got connection from " << inet_ntoa(cli_addr.sin_addr)
                  << " and port " << ntohs(cli_addr.sin_port) << std::endl;

        write(incomingSock, "You are connected!", MSG_REPLY_LENGTH);  /* Send a welcome message to the client */

        while (true) {
            std::string buffer(MAX_BUFFER, 0);  /* Create buffer with size MAX_BUFFER */

            ssize_t bytesRead = read(incomingSock, &buffer[0], MAX_BUFFER - 1);  /* Read data from the client */
            if (bytesRead < 0) {  /* Check if reading from the socket was successful */
                std::cerr << "Read from socket error" << std::endl;
                close(incomingSock);  /* Close the client socket on error */
                break;
            } else if (bytesRead == 0) {  /* Connection closed by client */
                std::cout << "Client disconnected." << std::endl;
                close(incomingSock);  /* Close the client socket */
                break;
            }

            buffer[bytesRead] = '\0';  /* Null-terminate the string */

            std::cout << "Received message: " << buffer << std::endl;
        }
    }

    close(sockfd);  /* Gracefully close the server socket */
    return 0;
}
