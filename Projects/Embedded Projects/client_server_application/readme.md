# 🖥️ Client-Server Application
This a simple client-server application written in C++. The server listens for incoming connections on a specified port, while the client connects to the server using a hostname and port number. The client and server can exchange messages until the client decides to terminate the connection by sending the message "exit"


## 📑 Table of content

- [📁 Files](#-files)
- [🔧 Build Instructions](#-build-instructions)
- [🚀 Running the Server](#-running-the-server)
- [🔍 Viewing Listening Ports](#-viewing-listening-ports)
- [🛑 Terminating the Server](#-terminating-the-server)
- [💻 Running the Client](#-running-the-client)
- [🔄 Communication](#-communication)
- [🔎 Example Usage](#-example-usage)
- [⚠️ Troubleshooting](#-troubleshooting)


## 📂 Files

- `server.cpp`: Implements the server-side logic.
- `client.cpp`: Implements the client-side logic.

## 🛠️ Build Instructions

To compile the client and server programs, you need a C++ compiler. Here's how you can build them using `g++`:

```bash
g++ -o server server.cpp
g++ -o client client.cpp
```

## 🚀 Running the Server
To start the server, use the following command:
```bash
./server <port>
```

Replace `<port>` with the port number on which you want the server to listen. For example:
```bash
./server 12345
```
the server will start listening on port 12345.

## 🔍 Viewing Listening Ports
To view the listening ports and the corresponding processes with there pids, you can use the following commands:

- Using `netstat`:
```bash 
netstat -tlnp
```

- Using `ss`:
```bash 
ss -tlnp
```

These commands will show you which ports are currently being listened to and by which processes and display it`s pid.

## 🚫 Terminating the Server
If you need to terminate the server process, you can find its PID (Process ID) from the output of netstat or ss, and then use the kill command to terminate it. For example:

1. Find the PID of the server process:
```bash 
netstat -tlnp | grep <port>
```
or 

```bash 
ss -tlnp | grep <port>
```

2. Kill the process using its PID:
```bash 
kill -9 <pid>
```
Replace `<pid>` with the actual Process ID of the server.

## 🌐 Running the Client
To connect to the server, use the following command:
```bash 
./client <server_hostname> <port>
```
Replace `<server_hostname>` with the hostname or IP address of the server, and `<port>` with the port number the server is listening on. For example:
```bash
./client localhost 12345
```
The client will connect to the server at localhost on port 12345.

## 🔄 Communication
- Server:
    - Accepts connections from clients.
    - Sends a welcome message ("You are connected!") upon a successful connection.
    - Reads messages from the client and prints them to the console.
    - Ends the connection when the client disconnects.

- Client:
    - Connects to the server using the provided hostname and port.
    - Receives and prints a welcome message from the server.
    - Prompts the user to input messages to send to the server.
    - Ends the connection when the user inputs "exit" by terminating the client application.

## 🧩 Example Usage
1. Start the server:
```bash 
./server 12345
```

2. In a separate terminal, start the client:
```bash 
./client localhost 12345
```

3. The client will receive a welcome message from the server and prompt the user for input. Type your messages and press Enter to send them to the server.

4. Type "exit" to close the client application. This will terminate the client but keep the server running.

5. If needed, terminate the server using `kill -9 <pid>` as described above.


## 🔧 Troubleshooting
- Ensure that the server is running before starting the client.
- Verify that the hostname and port number provided to the client match those used by the server.
- Use netstat -tlnp or ss -tlnp to check the status of listening ports and their corresponding PIDs.
- Use kill -9 <pid> to forcefully terminate the server if necessary.
- Check for any errors printed to the terminal if something goes wrong.

##

Thank you for using our client-server application! If you have any questions or suggestions, please feel free to contribute or contact us.

Happy Coding!

