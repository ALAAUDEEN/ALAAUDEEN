 #include "heltec.h" 
#include "images.h"
 

#define BAND    868E6  //you can set band here directly,e.g. 868E6,915E6
 
const int Sensorpin1 = 36;
 const int Temp_sen = 13;


byte msgCount = 0;
byte Sensor1;
byte Sensor2;
byte Sensor3;
byte Sensor4;
byte Sensor5;

byte localAddress = 0xBB;
byte destination = 0xFF;
void logo()
{
  Heltec.display->clear();
  Heltec.display->drawXbm(0,5,logo_width,logo_height,logo_bits);
  Heltec.display->display();
}
void setup() {
  Serial.begin(9600);
  
  Serial.println("LoRa Sender");
 
 Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  Serial.println("LoRa Initializing OK!");


   Heltec.display->init();
  Heltec.display->flipScreenVertically();  
  Heltec.display->setFont(ArialMT_Plain_10);
  logo();
  delay(1500);
  Heltec.display->clear();
  
  Heltec.display->drawString(0, 0, "Heltec.LoRa Initial success!");
  Heltec.display->display();
  delay(1000);
}

void loop() {

  
  Serial.print("Sending packet: ");
  Serial.println(msgCount);

 Sensor1 = analogRead(Sensorpin1);
   Serial.println(Sensor1);
Sensor1 = map(Sensor1,255,150,0,100);
       
 delay(1000); 
 Sensor2=0;
 Sensor3=0;
 Sensor4=0;
 Sensor5=0;
 
 
 
// Sensor2 = analogRead(Sensorpin2);
//  Sensor2 = map(Sensor2,3076,2300,0,100);
//  //if(String(Sensor2)>="100") { Sensor2=100; }      
// delay(250);
// 
// Sensor3 =analogRead(Sensorpin3);
//   Sensor3 = map(Sensor3,3076,2300,0,100);
// // if(String(Sensor3)>="100") { Sensor3=100; }      
// delay(250);
// 
// Sensor4 = analogRead(Sensorpin4);
//   Sensor4 = map(Sensor4,3076,2300,0,100);
// // if(String(Sensor4)>="100") { Sensor4=100; }      
// delay(250);
// 
// Sensor5=analogRead(Sensorpin5);
//   Sensor5 = map(Sensor5,3076,2300,0,100);
//  //if(String(Sensor5)>="100") { Sensor5=100; }      
 delay(250);
 
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  
  Heltec.display->drawString(0, 0, "Sensor 1:  ");
  Heltec.display->drawString(50, 0, String(Sensor1));
  Heltec.display->drawString(0, 10, "Sensor 2:  ");
  Heltec.display->drawString(50, 10, "No-Con");
    Heltec.display->drawString(0, 20, "Sensor 3:  ");
  Heltec.display->drawString(50, 20, "No-Con");
      Heltec.display->drawString(0, 30, "Sensor 4:  ");
  Heltec.display->drawString(50, 30, "No-Con");
  Heltec.display->drawString(0, 40, "Sensor 5");
  Heltec.display->drawString(50, 40, "No-Con");
 
   Heltec.display->drawString(0, 50, "Transmission OK!");
  Heltec.display->display();
 
  
  String outgoing = String(Sensor1) + String(Sensor2) + String(Sensor3) + String(Sensor4)+ String(Sensor5);
  // send packet
  LoRa.beginPacket();
  LoRa.write(destination);
  LoRa.write(localAddress);
  LoRa.write(msgCount);
  LoRa.write(outgoing.length());
  LoRa.write(Sensor1);
  LoRa.write(Sensor2);
  
  LoRa.write(Sensor3);
  LoRa.write(Sensor4);
    LoRa.write(Sensor5);
  LoRa.endPacket();
  msgCount++;
  delay(2000);
   Heltec.display->clear();
      Heltec.display->display();
}
