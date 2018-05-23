/*
  Web client
 */

//#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };


IPAddress server(192,168,227,1);    // Put the IP address for your server

// Set the static IP address to use for Arduino client
IPAddress ip(192, 168, 227, 8);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Ethernet.begin(mac, ip);
  Serial.println("10 seconds delay...");
  
  // give the Ethernet shield a second to initialize:
  delay(10000);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  int ret = client.connect(server, 80);
  if (ret==1) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
    Serial.println(ret);
  }
}

void loop() {
  // if there are incoming bytes available
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    while (true);
  }
}

