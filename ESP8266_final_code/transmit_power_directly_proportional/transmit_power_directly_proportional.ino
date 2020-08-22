//https://rootsaid.com/node-mcu-udp-streaming/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>


//Our HTML webpage contents
#include "index.h" 

/* Station Details */
const char *ssid = "username";
const char *password = "password";

/* Soft Access Point Details */
const char *apSSID = "ESP8266";
const char *apPassword = "";

/* Udp data settings*/
WiFiUDP Udp;
unsigned int port = 5514;
char packet[255];

//Sets array containing current power usage and the amount of users, with 5 levels 0-4
//const int powerLevel[] = {1,2,3,4,5};
float powerLevel[] = {0, 5, 10, 15, 20.5};
int currLevel = 4;
float currPower =  powerLevel[currLevel];
int numUsers;

int timeInterval = 0;

ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/

void handleRoot() {
  String s = MAIN_page; //Read HTML contents
  
  server.send(200, "text/html", s);
}

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_AP_STA);

  // Establish soft AP mode
  WiFi.softAP(apSSID, apPassword);

  /* If desired, sets ESP8266 also as an STA, to connect to the larger internet
  //Connect to your WiFi router
  WiFi.begin(ssid, password);     
  //Serial.println("");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }
 
  //If connection successful show IP address in serial monitor
  //Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  //Serial.println(WiFi.localIP());  //IP address assigned to your ESP
  Udp.begin(port);
  //Serial.printf("Listener started at IP %s, at port %d\n", WiFi.localIP().toString().c_str(), port);
 
  server.on("/", handleRoot);      //Which routine to handle at root location
 
  server.begin();                  //Start server
  //Serial.println("HTTP server started");
  */

}

void loop() {
  server.handleClient();

  timeInterval += 1;
  if (timeInterval % 200000 == 0)
  { 
    if (numUsers > 4) currLevel = 4;
    else currLevel = numUsers;
    currPower = powerLevel[currLevel];
    WiFi.setOutputPower(currPower);
    
    Serial.print(numUsers);
    Serial.print("\t");
    Serial.println(currPower);
  }

  /* Attempts to test throughput from the device were made, but uncompleted
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(packet, 255);
    
    if (len > 0)
    {
      packet[len] = 0;
    }
    
    Serial.printf("UDP packet contents: %s\n", packet);
    }  */
  }
