/**
 * Shared Drawing Canvas (Server) 
 * by Alexander R. Galloway. 
 * 
 * A server that shares a drawing canvas between two computers. 
 * In order to open a socket connection, a server must select a 
 * port on which to listen for incoming clients and through which 
 * to communicate. Once the socket is established, a client may 
 * connect to the server and send or receive commands and data.
 * Get this program running and then start the Shared Drawing
 * Canvas (Client) program so see how they interact.
 */


import processing.net.*;

Server server;
Client client;
String input;
int data[];

void setup() 
{
  server = new Server(this, 1212); // Start a simple server on a port
  println("IP address: " + server.ip());
}

void draw()
{
  
}

void serverEvent(Server myServer, Client client)
{
  println("New Client: " + client.ip());
  while (client.available() > 0)
  {
    client = server.available();
    println(client.readChar());
  }
  
  myServer.write("Version 8008135!");
  myServer.write(0);
}
