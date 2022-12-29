
#define ENA   0         // Enable/speed motors Right        GPIO14(D5)
#define ENB   15          // Enable/speed motors Left         GPIO12(D6)
#define IN_1  14          // L298N in1 motors Right           GPIO15(D8)
#define IN_2  2          // L298N in2 motors Right           GPIO13(D7)
#define IN_3  12           // L298N in3 motors Left            GPIO2(D4)
#define IN_4  13           // L298N in4 motors Left            GPIO0(D3)
         // L298N in4 motors Left            GPIO0(D3)

//const int trigP = 5;  //D4 Or GPIO-2 of nodemcu
//const int echoP = 16;  //D3 Or GPIO-0 of nodemcu


long duration;
int distance;
 
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
//#include "ESPAsyncWebServer.h"
#include <ESP8266WebServer.h>

 
String command;             //String to store app command state.
int speedCar = 200;         // 400 - 1023.
int speed_Coeff = 3;
 
const char* ssid = "Robot";
const char* password = "12345678";

// Set your Static IP address

IPAddress local_IP(192, 168, 1, 123);
// Set your Gateway IP address
IPAddress gateway(192, 168, 1, 1);

IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional




ESP8266WebServer server(80);

 
void setup() {
 
 pinMode(ENA, OUTPUT);
 pinMode(ENB, OUTPUT);  
 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT); 
  
  Serial.begin(115200);

   
  Serial.println("Positioned at 0 Degrees");
  Serial.println("Input Desired Angle and Press Enter");
  
// Connecting WiFi
 // Configures static IP address  WiFi.softAPConfig(ip, gateway, subnet);
  if (!WiFi.softAPConfig(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }

 
  WiFi.mode(WIFI_AP);
 WiFi.softAP(ssid, password); 
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  
 
 // Starting WEB-server 
     server.on ( "/", HTTP_handleRoot );
     server.onNotFound ( HTTP_handleRoot );
     server.begin();  

    // pinMode(trigP, OUTPUT);  // Sets the trigPin as an Output
    // pinMode(echoP, INPUT);   // Sets the echoPin as an Input
   
     
}
 
void goAhead(){ 
 
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);
 
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }
 
 
void goBack(){ 
 
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);
 
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
      Serial.print("Speed: ");
      Serial.println(speedCar);
  }

void goLeft(){ 
 
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);
 
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);

     
  }


void goLeft90(){ 
 
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);
 
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
       delay(250);

      stopRobot();
  }
  
 
void goRight(){
 
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);
 
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }
 
void goBackLeft(){
      
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar/speed_Coeff);
 
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
   }
 
void goBackRight(){
      
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);
 
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar/speed_Coeff);
  }
 
void goAheadLeft(){ 
 
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar/speed_Coeff);
 
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }
 
void goAheadRight(){ 
 
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);
 
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar/speed_Coeff);
  }
 
void stopRobot(){  
 
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);
 
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
 }

 
void loop() {
    server.handleClient();
    
      command = server.arg("State");
      if (command == "F") goAhead();
      else if (command == "B") goBack();
      else if (command == "L") goLeft();
      else if (command == "L90") goLeft90();
      else if (command == "R") goRight();
      else if (command == "I") goAheadRight();
      else if (command == "G") goAheadLeft();
      else if (command == "J") goBackRight();
      else if (command == "H") goBackLeft();
      else if (command == "0") speedCar = 100;
      else if (command == "1") speedCar = 110;
      else if (command == "2") speedCar = 120;
      else if (command == "3") speedCar = 130;
      else if (command == "4") speedCar = 140;
      else if (command == "5") speedCar = 150;
      else if (command == "6") speedCar = 160;
      else if (command == "7") speedCar = 180;
      else if (command == "8") speedCar = 190;
      else if (command == "9") speedCar = 200;
      else if (command == "10") speedCar = 255;
      else if (command == "S") stopRobot();
 
 

      

//digitalWrite(trigP, LOW);   // Makes trigPin low
//delayMicroseconds(2);       // 2 micro second delay 
//
//digitalWrite(trigP, HIGH);  // tigPin high
//delayMicroseconds(10);      // trigPin high for 10 micro seconds
//digitalWrite(trigP, LOW);   // trigPin low
//
//duration = pulseIn(echoP, HIGH);   //Read echo pin, time in microseconds
//distance= duration*0.034/2;        //Calculating actual/real distance
//String data= String(distance);
//server.send ( 200, "text/html",data );
//
////Serial.print("Distance = ");        //Output distance on arduino serial monitor 
////Serial.println(data);
//delay(100); 



  
}
 
void HTTP_handleRoot(void) {
 
if( server.hasArg("State") ){
       Serial.println(server.arg("State"));
       server.send ( 200, "text/html", "Sent!" );
  }
  
  delay(1);
}
