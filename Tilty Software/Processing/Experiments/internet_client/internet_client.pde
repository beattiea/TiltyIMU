import processing.net.*;

Client client;

void setup()
{
  delay(500);
  client = new Client(this, "192.168.1.145", 1212);
  check();
} 

void draw()
{
  
}

void check()
{
  client.write("version?");
  client.write(0);
}

void clientEvent(Client someClient)
{
  print("Client: " + someClient.readStringUntil(0));
}
