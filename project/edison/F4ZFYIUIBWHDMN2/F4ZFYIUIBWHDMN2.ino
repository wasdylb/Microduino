/*
  InstaKISS : Networked Picture Frames
 Reads mic values on pin A0
 if threshold is crossed (blowed on)
 create HTML page and print the characters "(kiss)"
 
 Hardware:
 Edison `
 Adafuit electret mic MAX4466
 
 created from Web Server example
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe
 
 */

#include <SPI.h>
#include <WiFi.h>


char ssid[] = "Azure_work";      // your network SSID (name)
char pass[] = "azure001";   // your network password
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
unsigned long lastConnectionTime = 0;           // last time you connected to the server, in milliseconds
boolean lastConnected = false;                  // state of the connection last time through the main loop
const unsigned long postingInterval = 10 * 1000; // delay between updates, in milliseconds

WiFiServer server(8080);

int blowPin = A0;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if ( fv != "1.1.0" )
    Serial.println("Please upgrade the firmware");

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  server.begin();
  // you're connected now, so print out the status:
  printWifiStatus();
}


void loop() {
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 1");  // refresh the page automatically every second
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output the value of each analog input pin

            int sensorReading = analogRead(blowPin);
          // uncomment following four lines to print analog sensor value to HTML page
          //client.print("analog input ");
          //client.print(" is ");
          //client.print(sensorReading);
          //client.println("<br />");

          if (sensorReading > 300) { //put the threshold you discovered by testing your mic
            client.println("(kiss)");
            client.print("<br />");
          }
          else 
          {
            client.println("(none)");
            client.print("<br />");
          }
          client.println("</html>");
          delay(5000);
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }

}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}


