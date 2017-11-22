# Unix-Socket Chat
This is a simple terminal socket chat between two pre-specified (using port numbers) clients connected to a server.</br> 
You can find the code for both server and the client in the socketChat folder. </br>
</br>
This folder contains config.h and libunp.a files, which is important to keep them in the directory above the socketChat folder,</br> as the 'compile' script located in socketChat folder will look for them in directory above.</br>
</br>
SocketChat folder:</br>

## Compile

This is file is a script which executes the commands in order to create the .o files and in order to link the libunp.a to that file.</br>
When called (./compile arg) it takes one argument which is the name of the .c file (without .c extension).</br>
</br>
## DayTimeServer
</br>
Server is allowing the two clients to connect through TCP/IP. </br>
After the connection is established, server decides which client is to send the message.</br>
Takes two parameters from the command line which are the two port numbers on which the communication is going to be based with each of the clients.</br>

## DayTimeClient
Client which connects to the server (Please note, server has to be up first, otherwise client will be unable to connect),</br> takes in two parameters, the IP address of the server and the port number (specified in server).</br>
After the connection to the server, client will await for second client to connect, after the connection is established within the 3 programs, each client will take turns to send a message to each other (through the server).</br>
The message will be first send to the server and then passed to the other client. </br>

