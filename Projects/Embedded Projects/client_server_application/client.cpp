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
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>

constexpr unsigned int MAX_BUFFER = 128;  /* Maximum buffer size for reading messages */

int main(int argc, char *argv[])
{
    if (argc < 3) {  /* Check if server hostname and port number are provided */
        std::cerr << "Usage: " << argv[0] << " <server hostname> <port>" << std::endl;
        return 1;
    }

    unsigned int serverPort = atoi(argv[2]);  /* Port passed as a command-line argument */

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);  /* Create a socket for the client */

    if (sockfd < 0) {  /* Check if socket creation was successful */
        std::cerr << "Socket error" << std::endl;
        return 1;
    }

    struct hostent *server = gethostbyname(argv[1]);  /* Get server's IP address from hostname */

    if (server == nullptr) {  /* Check if the hostname could be resolved */
        std::cerr << "No such host" << std::endl;
        return 2;
    }

    struct sockaddr_in serv_addr;
    bzero((char *) &serv_addr, sizeof(serv_addr));  /* Zero out the server address structure */
    serv_addr.sin_family = AF_INET;  /* Set the address family to IPv4 */
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);  /* Copy the server's address */
    serv_addr.sin_port = htons(serverPort);  /* Set the port number */

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {  /* Connect to the server */
        std::cerr << "Connection error" << std::endl;
        return 3;
    }

    std::string readBuffer(MAX_BUFFER, 0);  /* Create a buffer for reading from the server */
    if (read(sockfd, &readBuffer[0], MAX_BUFFER - 1) < 0) {  /* Read data from the server */
        std::cerr << "Failed to read from socket" << std::endl;
        close(sockfd);  /* Close the socket on error */
        return 5;
    }
    readBuffer[MAX_BUFFER - 1] = '\0';  /* Ensure null-termination */
    std::cout << readBuffer << std::endl;  /* Print the received message */

    while (true) {
        std::string writeBuffer;  /* Buffer for user input */
        std::cout << "Message for the server: ";
        std::getline(std::cin, writeBuffer);  /* Read a line of input from the user */

        if (write(sockfd, writeBuffer.c_str(), writeBuffer.length()) < 0) {  /* Write the message to the server */
            std::cerr << "Failed to write to socket" << std::endl;
            close(sockfd);  /* Close the socket on error */
            return 4;
        }

        if (writeBuffer == "exit") {  /* Check if the user wants to exit */
            break;  /* Exit the loop */
        }
    }

    close(sockfd);  /* Gracefully close the connection */
    std::cout << "Connection closed." << std::endl;

    return 0;
}
