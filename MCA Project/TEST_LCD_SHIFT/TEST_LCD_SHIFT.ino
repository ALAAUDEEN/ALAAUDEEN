/*  Three Wire LCD Interface using 74HC595
    www.circuits4you.com                 */

//Define 74HC595 Connections with arduio
  #include <ESP8266WiFi.h>                                               
#include <FirebaseArduino.h>   

#define WIFI_SSID "MY_TEST"                                          
#define WIFI_PASSWORD "12345678"      
#define FIREBASE_HOST "water-d1f38-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "3LeHRZCxzKAfKiTbvVys9p4qVFexrb4awnAIwkId"          

const int Data=D0;// PIN NO 14
const int Clock=D2;// PIN NO 11

const int Latch=D1;// PIN NO 12
const int Internet=D7;// PIN NO 12
const int Relay=D8;// PIN NO 12
void LCDinit(void);
void LCDSendByte(char d,char RS);
void LCDPrint(char Line,char string[16]);
//=============================================================
//                Setup
//=============================================================
void setup() {                
  // initialize the digital pin as an output.
  pinMode(Data, OUTPUT);
  pinMode(Clock, OUTPUT);
  pinMode(Latch, OUTPUT); 
    pinMode(Internet, OUTPUT);
  pinMode(Relay, OUTPUT); 
  LCDinit();  //initalize LCD in 4-bit mode

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                               
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
    digitalWrite(Internet, LOW);  
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);    
}
//=============================================================
//               Loop
//=============================================================
int sensor1=0;
 
 
String alert="0";
char Buf_line1[50];
char Buf_line2[50];


String line1;

String line2;

void loop() {
      digitalWrite(Internet, HIGH);  
 LCDPrint(0,"    MCA - ISM    ");
 LCDPrint(1,"BATCH: 2021-2023");
 delay(1000);
 
  String Safe_level;
    int sensorValue = analogRead(A0);
 if(sensorValue>=500)
 {
    Safe_level="Warning";
       digitalWrite(Relay, HIGH);  
   
  }
  else
  { Safe_level="Safe to Hear";
       digitalWrite(Relay, LOW);  
       
     
    }
   Firebase.setString("/COE-MSEC/SMS/Snd",String(sensorValue));
 Firebase.setString("/COE-MSEC/SMS/Val", Safe_level);
 

    line1="Sound:   "+String(sensorValue)+" dB";
  line2= "Alert:"+Safe_level;


  
line1.toCharArray(Buf_line1, 50);
 line2.toCharArray(Buf_line2, 50);
 LCDPrint(0,Buf_line1);
 LCDPrint(1,Buf_line2);
 delay(1000);
     LCDPrint(0,"                ");
 LCDPrint(1,"                ");
 delay(100);


 

  digitalWrite(Internet, HIGH);  
}

//=============================================================
//             Send Data or Command to LCD
//=============================================================
void LCDSendByte(char d,char RS)
{
  char dH,dL,temp;
  //Keep Data on upper nybble
  dH = d & 0xF0;         //Get MSB
  dL = d & 0x0F;
  dL = d << 4;           //Get LSB
//Send MSB with E=clock  
  temp=0;
  temp=dH | RS | 0x02;  //MSB With RS+E bit
  ShiftData(temp);
//Send MSB with E=0
  temp=0;
  temp=dH | RS;  //MSB With RS bit
  ShiftData(temp);
//Send LSB with E=clock
  temp=0;
  temp=dL | RS | 0x02;  //MSB With RS+E bit
  ShiftData(temp);
//Send LSB with E=0
  temp=0;
  temp=dL | RS;  //MSB With RS bit
  ShiftData(temp);  
}
//=============================================
void ShiftData(char temp)
{
  int i;
  for(i=0;i<8;i++)      
  {
    if((temp & 0x80)==0x80)    //Send 1-bit to shift register
    {digitalWrite(Data,HIGH);}
    else
    {digitalWrite(Data,LOW);}
          
    digitalWrite(Clock,LOW);
    digitalWrite(Clock,HIGH);
    temp=temp<<1;
  }
  //Latch the data
  digitalWrite(Latch,LOW);
  delay(1);
  digitalWrite(Latch,HIGH);        
}
//=================================================================
//           LCD Display Initialization Function
//=================================================================
void LCDinit()
{
  int count;
  char t[]={0x43,0x03,0x03,0x02,0x28,0x01,0x0C,0x06,0x02,0x02};    
      for (count = 0; count <= 9; count++)
      {
        LCDSendByte(t[count],0);    //Command RS=0
      }
}
//=================================================================
//        Display Line on LCD at desired location Function
//=================================================================
void LCDPrint(char Line,char string[16])
{
  
 int len,count;
 if(Line==0) {
   LCDSendByte(0x80,0);    //Command RS=0 Move Cursor to Home   
   
 }
 else if(Line==1)  {
   LCDSendByte(0xC0,0);    //Command RS=0 Move Cursor to Second Line
 }

 else if(Line==2)  {
   LCDSendByte(01,0);   
 }

 
        len = strlen(string);
    for (count=0;count<len;count++)
  {
     LCDSendByte(string[count],1);  //Data RS=1
  }
  
}
//========
