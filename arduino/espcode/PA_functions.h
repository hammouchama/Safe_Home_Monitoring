
#include <ESP8266WebServer.h>
ESP8266WebServer server(80);
int connectWifi();
int sendParams(String url);


/* *********************** */
/* ***** PointAccess ***** */
/* *********************** */
char* ssid = "ZOM";
char* password = "12345789";
char* host = "192.168.229.44";
int httpPort = 80;

char* phone = "+212644530219";
/* *********************** */

char *ssidAP = "ESPap";
char *passwordAP = "thereisnospoon";
bool isConnectedToWifi = false;
/* Just a little test message. Go to http://192.168.4.1 in a web browser
* connected to this access point to see it.*/

String TurnAlert = "On";
IPAddress myLocalIP;






void handleRoot() {
  String html = "<!DOCTYPE html>";
  html+="  <html lang='en'>";
  html+="  <head>";
  html+="    <meta charset='UTF-8'>";
  html+="    <meta http-equiv='X-UA-Compatible' content='IE=edge'>";
  html+="    <meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html+="    <title>Chart Gaz & Flame</title>";
  html+="    <link rel='stylesheet' href='css/style.css'>";
  html+="    <style>";
  html+="      .container {";
  html+="        background-color: white;";
  html+="        margin: auto;";
  html+="        max-width: 95%;";
  html+="        width: 900px;";
  html+="        padding: 10px;";
  html+="        box-shadow: 2px 2px 5px #999;";
  html+="      }";
  html+="      header {";
  html+="        width: 100%;";
  html+="        background: linear-gradient(to right, #FFB703, #FB8500);";
  html+="      }";
  html+="      header .Logo {";
  html+="        margin: auto;";
  html+="        max-width: 1000px;";
  html+="        width: 98%;";
  html+="        display: flex;";
  html+="        flex-direction: column;";
  html+="        align-items: center;";
  html+="      }";
  html+="      .title {";
  html+="        font-weight: bold;";
  html+="        font-family: 'Montserrat', sans-serif;";
  html+="        font-size: 48px;";
  html+="        color: #ffffff;";
  html+="        text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.5);";
  html+="        letter-spacing: -5px;";
  html+="      }";
  html+="      .desc {";
  html+="        font-size: 20px;";
  html+="        color: #ffffff;";
  html+="        font-family: 'Pacifico', cursive;";
  html+="        font-weight: bold;";
  html+="        line-height: 0.6em;";
  html+="        padding-bottom: 15px;";
  html+="      }";
  html+="      .config-form {";
  html+="        padding: 20px;";
  html+="        margin-bottom: 20px;";
  html+="      }";
  html+="      .config-form label {";
  html+="        font-size: 16px;";
  html+="        color: #333;";
  html+="      }";
  html+="      .config-form .input-field {";
  html+="        width: calc(100% - 20px);";
  html+="        padding: 8px;";
  html+="        margin-bottom: 10px;";
  html+="        border: 1px solid #ccc;";
  html+="        border-radius: 4px;";
  html+="      }";
  html+="      .submit-button {";
  html+="        align-items: center;";
  html+="        appearance: button;";
  html+="        background-color: #ffbe0b;";
  html+="        border-radius: 8px;";
  html+="        border-style: none;";
  html+="        box-shadow: rgba(255, 255, 255, 0.26) 0 1px 2px inset;";
  html+="        box-sizing: border-box;";
  html+="        color: #fff;";
  html+="        cursor: pointer;";
  html+="        display: flex;";
  html+="        flex-direction: row;";
  html+="        flex-shrink: 0;";
  html+="        font-family: 'RM Neue', sans-serif;";
  html+="        font-size: 100%;";
  html+="        line-height: 1.15;";
  html+="        margin: 0;";
  html+="        padding: 10px 21px;";
  html+="        text-align: center;";
  html+="        text-transform: none;";
  html+="        transition: color .13s ease-in-out, background .13s ease-in-out, opacity .13s ease-in-out, box-shadow .13s ease-in-out;";
  html+="        user-select: none;";
  html+="        -webkit-user-select: none;";
  html+="        touch-action: manipulation;";
  html+="      }";
  html+="      .submit-button:active {";
  html+="        background-color: #fdbc08;";
  html+="      }";
  html+="      .submit-button:hover {";
  html+="        background-color: #ffc935;";
  html+="      }";
  html+="      .status {";
  html+="        color: #023047;";
  html+="        background-color: #f2f2f2;";
  html+="        margin: 10px 0px;";
  html+="        padding: 20px;";
  html+="        border-radius: 10px;";
  html+="        box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);";
  html+="      }";
  html+="      .status h2 {";
  html+="        font-size: 24px;";
  html+="        color: #333;";
  html+="        margin-top: 0px;";
  html+="        margin-bottom: 10px;";
  html+="      }";
  html+="      .status p {";
  html+="        font-size: 16px;";
  html+="        color: #777;";
  html+="        margin-bottom: 5px;";
  html+="      }";
  html+="      ";
  html+="      body {";
  html+="        margin: 0;";
  html+="        padding: 0;";
  html+="        background-color: #fdfffc;";
  html+="      }";
  html+="      #configLink{";
  html+="        text-decoration: none;";
  html+="        color: #fdbc08;";
  html+="        transition: .2s;";
  html+="      }";
  html+="      #configLink:hover{";
  html+="        text-decoration: none;";
  html+="        color: #006AE8;";
  html+="      }";
  html+="      #configLink::after{";
  html+="        content: ">";";
  html+="        display: inline;";
  html+="        margin-left: 2px;";
  html+="        transition: .2s;";
  html+="      }";
  html+="      #configLink:hover::after{";
  html+="        margin-left: 5px;";
  html+="      }";
  html+="    /* FOR Mediem screens */";
  html+="    @media screen and (max-width: 768px) {";
  html+="      .title {";
  html+="        font-size: 36px;";
  html+="        letter-spacing: -4px;";
  html+="      }";
  html+="      .desc{";
  html+="        font-size: 14px;";
  html+="      }";
  html+="    }";
  html+="    /* FOR Small screens */";
  html+="    @media screen and (max-width: 400px) {";
  html+="      .title {";
  html+="        font-size: 30px;";
  html+="        letter-spacing: -4px;";
  html+="      }";
  html+="      .desc{";
  html+="        font-size: 10px;";
  html+="      }";
  html+="    }";
  html+="    </style>";
  html+="  </head>";
  html+="  <body>";
  html+="    <header>";
  html+="      <div class='Logo'>";
  html+="        <div class='title'>SafeHome Monitoring</div>";
  html+="        <div class='desc'>Gas and Flame Detection for a Secure Home</div>";
  html+="      </div>";
  html+="    </header>";
  html+="    <div class='container'>";
  html+="      <h2>Configurations:</h2>";
  html+="      <form method='POST' action='/submit' class='config-form'>";
  html+="        <label for='ssid'>Wi-Fi SSID:</label><br>";
  html+="        <input type='text' id='ssid' name='ssid' class='input-field'><br>";
  html+="        <label for='password'>Wi-Fi Password:</label><br>";
  html+="        <input type='text' id='password' name='password' class='input-field'><br>";
  html+="        <label for='host'>Host (IP):</label><br>";
  html+="        <input type='text' id='host' name='host' class='input-field'><br>";
  html+="        <label for='httpPort'>Port:</label><br>";
  html+="        <input type='text' id='httpPort' name='httpPort' class='input-field'><br>";
  html+="        <label for='phone'>Phone number:</label><br>";
  html+="        <input type='text' id='phone' name='phone' class='input-field'><br>";
  html+="        <input type='submit' value='Submit' class='submit-button'>";
  html+="      </form>";
  html+="      <div class='status'>";
  html+="          <p>Current Wifi : "+(isConnectedToWifi?String(ssid):String(ssidAP))+"</p>";
  html+="          <p>Current ESP IP : "+String(myLocalIP.toString())+"</p>";
  html+="          <p>";
        if(isConnectedToWifi)
  html+="            <a id='configLink' href='http://"+String(myLocalIP.toString())+"'>Access to Monitoring</a>";
        else
  html+="            <a id='configLink' href='#'>Initial Configuration!</a>";
  html+="          </p>";
  html+="      </div>";
  html+="    </div>";
  html+="  </body>";
  html+=" </html>";

  server.send(200, "text/html", html);
}

void handleSubmit() {
  strcpy(ssid,server.arg("ssid").c_str());
  strcpy(password,server.arg("password").c_str());
  strcpy(host,server.arg("host").c_str());
  httpPort = atoi(server.arg("httpPort").c_str());
  strcpy(phone,server.arg("phone").c_str());


  String tmphtml = "<!DOCTYPE html>";
  tmphtml+="  <html lang='en'>";
  tmphtml+="  <head>";
  tmphtml+="    <meta charset='UTF-8'>";
  tmphtml+="    <meta http-equiv='X-UA-Compatible' content='IE=edge'>";
  tmphtml+="    <meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  tmphtml+="    <title>Chart Gaz & Flame</title>";
  tmphtml = "</head><body>";


  /* password = const_cast<char*>(server.arg("password").c_str());
  host = const_cast<char*>(server.arg("host").c_str());
  
  phone = const_cast<char*>(server.arg("phone").c_str()); */


  /* Serial.println("Wifi ssid: " + String(ssid));
  Serial.println("Wifi Password: " + String(password));
  Serial.println("Host (IP): " + String(host));
  Serial.println("Port: " + String(httpPort)); */


  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "GET,POST,PUT,DELETE,OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");

  
  if(!connectWifi()){///////////// Inversed
    String tmp = "phone="+String(phone)+"&EspIP="+String(myLocalIP.toString());
    server.send(200, "text/html", tmphtml+"<h1>Well Connected</h1><h3>Current Wifi : "+String(ssid)+"</h3></body></html>");
    isConnectedToWifi=true;
    /* delay(3000); */
    /* WiFi.softAPdisconnect(true); */
    sendParams(tmp);
  }else{
    isConnectedToWifi=false;
    server.send(200, "text/html", tmphtml+"<h1>Not Connected</h1><h3>Current Wifi : "+String(ssidAP)+"</h3></body></html>");
  }

}



void handleMessage() {
  char* msg = const_cast<char*>(server.arg("msg").c_str());

  //Serial.println("recieved msg: " + String(msg));

  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "GET,POST,PUT,DELETE,OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");

  if(strcmp(msg,"Off")==0||strcmp(msg,"On")==0){
    TurnAlert=msg;
    server.send(200, "text/html", "Well turned "+String(msg));

  }else if(strcmp(msg,"reset")==0){
    server.send(200, "text/html", "The module is reseting");
    // Reset ESP-01S
    ESP.reset();
  }else if(strcmp(msg,"ping")==0){
    server.send(200, "text/html", "ok");
  }else{
    server.send(404, "text/html", "Not found");
  }
}


