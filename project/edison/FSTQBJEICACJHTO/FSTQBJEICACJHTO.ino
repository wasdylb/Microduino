/*
InstaKISS : Networked Picture Frames
 Connect to second Edison's IP address
 Use HTTP request and textFinder library to look for 
 "(" When found, store the next 4 characters in an array, 
 print to serial window and turn on LEDs. If button is pushed,
 turn off LED. 
 
 created using Repeating Wifi Web Client example
 by Tom Igoe
 modified 13 Jan 2014
 by Federico Vanzati
 
 http://arduino.cc/en/Tutorial/WifiWebClientRepeating
 This code is in the public domain.
 */

#include <SPI.h>
#include <WiFi.h>
#include <TextFinder.h>

String inString;
int stringPos = 0;
boolean startRead = false;
int ledPin = 13;

char ssid[] = "Azure_VPN";      //  your network SSID (name)
char pass[] = "azure001";   // your network password
//int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

// Initialize the Wifi client library
WiFiClient client;
TextFinder finder(client);

// server address:
IPAddress server(10,2,12,80); //Put the sending Edison's IP address here

unsigned long lastConnectionTime = 0;            // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 5 * 1000; // delay between updates, in milliseconds

char c;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
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
  // you're connected now, so print out the status:
  printWifiStatus();
}

void loop() {
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  while (client.available()) {
    if (c == '(')         
      startRead = true; 
    c = client.read();
    if (startRead){
      if (c != ')') //look for the ending paranthesis
        inString += c;
      else{
        Serial.println(inString);
        if(inString=="kiss")
        {
          Serial.println("LEDON");
          digitalWrite(ledPin, HIGH);
        }
        else if(inString=="none")
        {
          Serial.println("LEDOFF");
          digitalWrite(ledPin, LOW);
        }
        startRead = false;
        inString="";
      }
    } 
    // Serial.write(c);

  }

  // if ten seconds have passed since your last connection,
  // then connect again and send data:
  if (millis() - lastConnectionTime > postingInterval) {
    httpRequest();
  }

}

// this method makes a HTTP connection to the server:
void httpRequest() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(server, 8080)) {
    Serial.println("connecting...");
    // send the HTTP PUT request:
    client.println("GET /latest.txt HTTP/1.1");
    client.println("Host: wiki.microduino.cn");
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();

    while (client.available()) {
      if (c == '(')         
        startRead = true; 
      c = client.read();
      if (startRead){
        if (c != ')') //look for the ending paranthesis
          inString += c;
        else{
          Serial.println(inString);
          if(inString=="kiss")
            digitalWrite(ledPin, HIGH);
          else if(inString=="none")
            digitalWrite(ledPin, LOW);
          startRead = false;
          inString="";
        }
      } 
    }
    // note the time that the connection was made:
    lastConnectionTime = millis();
  }
  else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
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




