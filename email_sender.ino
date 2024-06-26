#include <WiFiNINA.h>

WiFiClient client;

const char ssid[] = "Optus_B8E72A_5GHz"; // Your network's SSID
const char pass[] = "corns39526ys"; // Your network's password

char HOST_NAME[] = "maker.ifttt.com";
String sketch_received   = "b3RoZlEur7BVMMGubVBWSP"; // change your EVENT-NAME and YOUR-KEY
String queryString = "?value1=57&value2=25";

void setup() {
  // initialize WiFi connection
  Serial.begin(9600);
  while (!Serial);

  // connect to web server on port 80:
  if (client.connect(HOST_NAME, 80)) {
    // if connected:
    Serial.println("Connected to server");
  }
  else {// if not connected:
    Serial.println("connection failed");
  }
}

void loop() {
  if (Serial.read() == 's') {

    // make a HTTP request:
    // send HTTP header
    client.println("GET " + sketch_received + queryString + " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    client.println("Connection: close");
    client.println(); // end HTTP header


    while (client.connected()) {
      if (client.available()) {
        // read an incoming byte from the server and print it to serial monitor:
        char c = client.read();
        Serial.print(c);
      }
    }

    // the server's disconnected, stop the client:
    client.stop();
    Serial.println();
    Serial.println("disconnected");
  }
}