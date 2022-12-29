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
#define FIREBASE_HOST "kma-moisture-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "qWGH88JqZn4UWRglLHQZUsbEkE226edlej6Sz2ec"                              
  
const int analogInPin = A0;
    int sensorValue = 0;                                                          
void setup() 
{
   pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
   pinMode(D4,OUTPUT);
    pinMode(D5,OUTPUT);
     pinMode(D6,OUTPUT);
          pinMode(D7,OUTPUT);
            pinMode(D8,OUTPUT);
  Serial.begin(9600);
  delay(1000);    
                
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                               
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
    digitalWrite(D8, LOW);  
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                  // connect to firebase
                     //send initial string of led status
}
 String Valve1;
  String Valve2;
   String Valve3;
    String Valve4;
     String Valve5;
     String Motor;
     String Manual;
 
void loop() 
{

   sensorValue = analogRead(analogInPin);
 
  // print the readings in the Serial Monitor
  Serial.print("sensor = ");
  Serial.print(sensorValue);

  if (sensorValue<=600)
  {
  String Rain_occured="YES";
   Firebase.setString("/Firebase/Rain",Rain_occured);
   digitalWrite(D2, LOW);
   digitalWrite(D3, LOW);
   digitalWrite(D4, LOW);
   digitalWrite(D5, LOW);
   digitalWrite(D6, LOW);
 
   Manual=Firebase.getString("Firebase/MANUAL");

if(Manual=="ON") {
  digitalWrite(D7, HIGH);Serial.println("mOTOR ON"); } else if(Manual=="OFF"){digitalWrite(D7, LOW);Serial.println("mOTOR OFF");
}
 
  }
else
  {
  String Rain_occured="NO";
   Firebase.setString("/Firebase/Rain",Rain_occured);
     digitalWrite(D8, HIGH);  
  
        
  Valve1=Firebase.getString("Firebase/V_1");
    Valve2=Firebase.getString("Firebase/V_2");
      Valve3=Firebase.getString("Firebase/V_3");
        Valve4=Firebase.getString("Firebase/V_4");
          Valve5=Firebase.getString("Firebase/V_5");
           Motor=Firebase.getString("Firebase/Motor");
  if(Firebase.failed())
  {
    Serial.println(Firebase.error());
       Serial.println("Failed");
  }
  else
  {  Serial.println("Comiing");
    Serial.println(Valve1);
    Serial.println(Valve2);
    Serial.println(Valve3);
    Serial.println(Valve4);
    Serial.println(Valve5);
       Serial.println(Motor);
      }
if(Valve1=="ON") {digitalWrite(D2, HIGH); } else if(Valve1=="OFF"){digitalWrite(D2, LOW);}
if(Valve2=="ON") {digitalWrite(D3, HIGH); } else if(Valve2=="OFF"){digitalWrite(D3, LOW);}
if(Valve3=="ON") {digitalWrite(D4, HIGH); } else if(Valve3=="OFF"){digitalWrite(D4, LOW);}
if(Valve4=="ON") {digitalWrite(D5, HIGH); } else if(Valve4=="OFF"){digitalWrite(D5, LOW);}
if(Valve5=="ON") {digitalWrite(D6, HIGH); } else if(Valve5=="OFF"){digitalWrite(D6, LOW);}
if(Motor=="ON") {digitalWrite(D7, HIGH);Serial.println("mOTOR ON"); } else if(Motor=="OFF"){digitalWrite(D7, LOW);Serial.println("mOTOR OFF");}
 
  }


  
  
  digitalWrite(D8,LOW );     
  delay(1000);
   
}
