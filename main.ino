// by vu3ave // Anish VR, North Paravur
// include index.h file while compiling

#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "index.h" //Our HTML webpage contents with javascripts

//SSID and Password of your WiFi router
const char* ssid = "192.168.4.1";
const char* password = "";

ESP8266WebServer server(80); //Server on port 80


// version 1



String data;
void writeString(char add,String data);
String read_String(char add);
String recivedData;


 int gipo0_pin = 0;
 int speed_pot_pin = A0;
 int speed_pot = 0;
 int a0max = 3000;
String message;



//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 String s = MAIN_page; //Read HTML contents on index.h 
 server.send(200, "text/html", s); //Send web page
}


void handleADATA(){
   message = server.arg("mytxt"); 
   // Serial.println(message);

    // converting int to string
    String sensor_value = String(speed_pot);

    server.send(200, "text/plane", sensor_value);
}


void handleSENDSEN(){
   message = server.arg("mytxt"); 
   // Serial.println(message);

 a0max = a0max + message.toInt();
    server.send(200, "text/plane", message);
}








//==============================================================
//                  SETUP
//==============================================================
void setup(void){

  Serial.begin(115200);
  EEPROM.begin(512);
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);



 
  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page

  server.on("/adata", handleADATA);
  
   server.on("/sendsen", handleSENDSEN);
  
  
    
  server.begin();                  //Start web server
  
  Serial.println("");
  Serial.println("HTTP server started");


  Serial.print("EEPROM length: ");
  Serial.println(EEPROM.length());
  
   pinMode( gipo0_pin, INPUT);
  
 
}//setup









//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  
  
  
   speed_pot = (map(analogRead(speed_pot_pin), 0, 1023, 0, a0max));
   
  
   server.handleClient();          //Handle client requests
   
   
   delay(100);
   
Serial.println(speed_pot);
Serial.println();

     
  
}

