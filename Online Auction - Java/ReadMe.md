# Unix-Socket Chat
The idea of the system is to simulate an online auction system without implementing the actual credit card transactions. </br>
The system has to allow the client (user) to bid for the items that are listed in the server,</br> while at the same time receive appropriate information such as time, price etc. The item has to be sold to the highest bidder.</br>
The system is designed in a way to support socket connection from multiple clients connecting to the same server at the same time. </br>
The system consists of two main parts including the server and the client.</br>
The code for the system has been written using Java language with the support of Java sockets.</br>
</br>
In order to compile the programs, the provided bash files have to be run in the following order:</br>
</br>
1. serverStarter.bat </br>
2. clientStarter.bat</br>
</br>
Alternatively the following commands will start the system:</br>
</br>
```
Javac –classpath . *.java
Java ResourceServer 8742 
Java ConsumerClient 8742
``
</br>
In order to run the program, ensure 
</br>that PORT is specified in the command line, 
</br>that the port is the same for both server and 
</br>the client and that the port is available on the machine.</br>

## Client

Client software’s main purpose is to provide input and output to the user, while communicating with the server and making necessary error checking.</br>
</br>
The client software requirements have been specified in the assignment and are as follow:</br>
</br>

``
- Connects to the server. The item currently being offered for sale and the current bid or a reserve price is displayed.</br>
- Enter the bid. The amount entered should be greater than the current highest bid.</br>
- After a new bid is placed, the amount of the new bid must be displayed on the client’swindow/console.</br>
``

## Server
Server software’s main purpose is to create and manage the items that are listed for the auction, accept and manage connections but also to communicate with the multiple clients including notifying all of them when necessary.</br>
The server software requirements have been specified in the assignment and are as follow:</br>
</br>

``
- Receive connections from multiple clients.
- After a client connects, notify the client which item is currently on sale and the highest bid (or reserve price).
- Specify the bid period. Max allowed 1 minute. When a new bid is raised, the bid period is reset back.
- When a new bid is placed, all clients are notified immediately. Clients should be notified about the time left for bidding (when appropriate).
- If the bid period elapses without a new bid, then the auction for this item closes. The successful bidder (if any) is chosen and all clients are notified.
- When an auction for one item finishes, another item auctioning should start. Minimum of 5 items should be auctioned, one after another and only one item at a time.
- Any item not sold should be auctioned again (automatically).
``
