 #include "heltec.h" 
#include "images.h"
#include <WiFi.h>
#include <FirebaseESP32.h>
#define BAND    868E6  //you can set band here directly,e.g. 868E6,915E6
#define FIREBASE_HOST "https://kma-moisture-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "qWGH88JqZn4UWRglLHQZUsbEkE226edlej6Sz2ec"
#define WIFI_SSID "MY_TEST"
#define WIFI_PASSWORD "12345678"



 
//Define FirebaseESP32 data object
FirebaseData firebaseData;
FirebaseJson json;
 
 
byte localAddress = 0xFF;
int recipient;
String incoming;
byte sender;
int incomingMsgId;
int incomingLength;
int Sensor1;
int Sensor2;
int Sensor3;
int Sensor4;
int Sensor5;
String valve1;
String valve2;
String valve3;
String valve4;
String valve5;
String motor;
int Temp_sensor;
int Rain_sensor;

 
 

byte Sensor_Temp;
byte Sensor_Rain;
  


void setup() {

  analogSetPinAttenuation(12,ADC_11db);
  Serial.begin(9600);
  Serial.println("LoRa Receiver");
 Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
 
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
 
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
    //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");

  
}


void loop() {
  
 Sensor_Temp = analogRead(36);
    Serial.println("Sensor_Temp");
    Serial.println(Sensor_Temp);
Sensor_Temp = map(Sensor_Temp,136,110,25,34);
   Serial.println(Sensor_Temp);
 delay(2000);

   
 delay(2000);
  int packetSize = LoRa.parsePacket();
  if (packetSize == 0) return;
  recipient = LoRa.read();
  sender = LoRa.read();
  incomingMsgId = LoRa.read();
  incomingLength = LoRa.read();
  Sensor1 = LoRa.read();
  Sensor2 = LoRa.read();
  Sensor3 = LoRa.read();
  Sensor4 = LoRa.read();
  Sensor5 = LoRa.read();
  incoming = String(Sensor1) + String(Sensor2) + String(Sensor3) + String(Sensor4) + String(Sensor5);


  
  if (incomingLength != incoming.length()) {
    Serial.println("error: message length does not match length");
    return;
  }
  if (recipient != localAddress) {
    Serial.println("This message is not for me.");
    return;
  }
  Serial.println("********************************************");
  Serial.println("Received from: 0x" + String(sender, HEX));
  Serial.println("Sent to: 0x" + String(recipient, HEX));
  Serial.println("Message ID: " + String(incomingMsgId));
  Serial.println("Message length: " + String(incomingLength));
  Serial.println("Sensor1: " + String(Sensor1));
  Serial.println("Sensor2: " + String(Sensor2));
  Serial.println("Sensor3: " + String(Sensor3));
  Serial.println("Sensor4: " + String(Sensor4));
  Serial.println("Sensor5: " + String(Sensor5));
  Serial.println("RSSI: " + String(LoRa.packetRssi()));
  Serial.println("Snr: " + String(LoRa.packetSnr()));
  Serial.println("");
//firesbase updatation

if(Sensor1<=40)
{
  valve1="ON";
}
else
{
  valve1="OFF";
}
//if(Sensor2<50)
//{
//  valve2="ON";
//}
//else
//{
//  valve2="OFF";
//}
//if(Sensor3<50)
//{
//  valve3="ON";
//}
//else
//{
//  valve3="OFF";
//}
//if(Sensor4<50)
//{
//  valve4="ON";
//}
//else
//{
//  valve4="OFF";
//}
//if(Sensor5<50)
//{
//  valve5="ON";
//}
//else
//{
//  valve5="OFF";
//}

if(valve1=="OFF"&&valve2=="OFF"&&valve3=="OFF"&&valve4=="OFF"&&valve5=="OFF")
{
  motor="OFF";
  
}
else
{
  motor="ON";
}
    
  
delay(100); 
  json.set("/Moi1", Sensor1);
  json.set("/Moi2", Sensor2);
  json.set("/Moi3", Sensor3);
  json.set("/Moi4", Sensor4);
  json.set("/Moi5", Sensor5);
 
    json.set("/V_1", valve1);
  json.set("/V_2", valve2);
  json.set("/V_3", valve3);
  json.set("/V_4", valve4);
  json.set("/V_5", valve5);
    json.set("/Motor", motor);
  Firebase.updateNode(firebaseData,"/Firebase",json);

  
}
