/*
* This sketch sends data via HTTP GET requests to data.sparkfun.com service.
*
* You need to get streamId and privateKey at data.sparkfun.com and paste them
* below. Or just customize this script to talk to other HTTP servers.
* ESP8266 Arduino example
*/
#include <ESP8266WiFi.h>

#include "PA_functions.h"
int sendLog(String log_data="");


int connectWifi(){
  delay(10);
  // We start by connecting to a WiFi network

  WiFi.begin(ssid, password);

  //Try to connect for 10 seconds
  int tries = 20;
  while ((WiFi.status() != WL_CONNECTED) && (tries--)){
    delay(500);
  }
  /* Connected to wifi successfuly */
  //then disconnect the wifi 
  if((WiFi.status() == WL_CONNECTED)){
  
    myLocalIP = WiFi.localIP();
    /* sendLog("Local IP address: ");
    sendLog(myLocalIP.toString());
    sendLog("Connexion established");
    sendLog("\n");
    sendLog("WiFi connected"); */
    WiFi.softAPdisconnect(true);
    return true;
  }else{
    /* sendLog("Connexion failed to wifi : "+String(ssid));
    sendLog("Wifi AP is kept on"); */
    return false;
  }
}



int sendParams(String url) {

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, httpPort)) {
    return 0;
  }
  
  url = "/Arduino/config.php?" + url;
  sendLog("\n");
  sendLog("GET PARAMS - Requesting URL: ");
  sendLog(url);
  sendLog("");

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  int status=1;
  if (client.available() == 0) {
    status=0;
  }

  sendLog("\n");
  sendLog("closing connection\n");
  client.stop();
  return status;
}


int sendLog(String log_data) {

  WiFiClient client;
  if (!client.connect(host, httpPort)) {
    return 0;
  }
  String url = "/Arduino/log.php";

  String post_data = "log_data=" + log_data;
  client.print("POST " + url + " HTTP/1.1\r\n");
  client.print("Host: " + String(host) + "\r\n");
  client.print("Content-Type: application/x-www-form-urlencoded\r\n");
  client.print("Content-Length: " + String(post_data.length()) + "\r\n");
  client.print("Connection: close\r\n");
  client.print("\r\n");
  client.print(post_data);
  if (client.connected()) {
    client.stop();
    return 1;
  }
  client.stop();
  return 0;
}



int sendData(String url) {

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, httpPort)) {
    return 0;
  }

  url = "/Arduino/v1.php?" + url;
  /* sendLog("\n");
  sendLog("Requesting URL: ");
  sendLog(url);
  sendLog(""); */

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      /* sendLog(">>> Client Timeout !\n"); */
      client.stop();
      return 0;
    }
  }

  /* sendLog("\n");
  sendLog("closing connection\n"); */
}

void setup() {
  Serial.begin(115200);

/* *********************** */
/* ***** Initial Conf **** */
/* *********************** */

  /* sendLog(""); */
  //sendLog("Configuring access point...");
  ///-----------------------------------
  /* Serial.print("HTTP server started"); */
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssidAP, passwordAP);
  myLocalIP = WiFi.softAPIP();
  /* sendLog("AP IP address: "+String(myIP)); */
  ///-----------------------------------
  /* Serial.print("AP IP address: ");
  Serial.print(myLocalIP); */


  // Add CORS headers
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "GET,POST,PUT,DELETE,OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
  // Start web server
  server.on("/", handleRoot);
  server.on("/submit", handleSubmit);
  server.on("/message", handleMessage);
  server.begin();

  ///-----------------------------------
  /* Serial.print("HTTP server started"); */
  //sendLog("HTTP server started");
/* *********************** */

  
  connectWifi();

}



String currentMode = "InitialConf";
/* TWO MODES :
*  InitialConf 
*     - Acces Point is ON , 
*     - Wifi Connexion is NOT established , 
*     - the data are NOT sending to DB
*  SendingData
*     - Acces Point is OFF , 
*     - Wifi Connexion is established, 
*     - the data are sending to DB
*  */
unsigned long lastSent = millis();
void loop() {
    
  
  server.handleClient();

    

  if(millis() - lastSent > 5000){
    /* Send the Alert status */
    Serial.println(TurnAlert);
    /* READ SENSORS VALUE */
    String incomingvalue = Serial.readString();


    if(!incomingvalue.isEmpty()){
      lastSent = millis();
      // SEND DATA THROUGH THE API TO SERVER
      String url = incomingvalue;
      url += "&TurnAlert="+TurnAlert;
      sendData(url);
    }
  }
}