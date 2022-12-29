 /*
 
#include <ESP8266WiFi.h>

#include <FirebaseArduino.h>

#define WIFI_SSID "MY_TEST"                                          
#define WIFI_PASSWORD "12345678"      
#define FIREBASE_HOST "https://kma-moisture-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "qWGH88JqZn4UWRglLHQZUsbEkE226edlej6Sz2ec"
qWGH88JqZn4UWRglLHQZUsbEkE226edlej6Sz2ec
*/
  #include <ESP8266WiFi.h>                                               
#include <FirebaseArduino.h>                                        
 
#define WIFI_SSID "MY_TEST"                                          
#define WIFI_PASSWORD "12345678"      
#define FIREBASE_HOST "water-d1f38-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "3LeHRZCxzKAfKiTbvVys9p4qVFexrb4awnAIwkId"                              



 //Ultra DEclaration 

#define echoPin D2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin D3 //attach pin D3 Arduino to pin Trig of HC-SR04
long duration;  
int distance; 

// ANLOG SENSOR  
const int analogInPin = A0;
    int sensorValue = 0;        


                                                      
void setup() 
{

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600);
  
 

  delay(1000);    
                
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                               
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.println("Connecting to the Network");
    delay(500);
     }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                   
                 
}
 
 
void loop() 
{



  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
 
  // print the readings in the Serial Monitor
 String Motor; 
 if(distance>20)
 {
   Motor="ON";
 }
 else
 {
   Motor="OFF";
 }

  sensorValue = analogRead(analogInPin);

  delay(500);
   Firebase.setString("/COE-MSEC/WMS/WATER_LEVEL",String(distance));
 Firebase.setString("/COE-MSEC/WMS/MOTOR_STATUS", Motor);
 Firebase.setString("/COE-MSEC/WMS/FLOW_LEVEL", String(sensorValue));
   
  delay(1000);
   
}
