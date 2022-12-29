#include <DS3231.h>
#include <Wire.h>
const int RELAY = 4;
DS3231  rtc(SDA, SCL);
Time  t;
int Hor;
int Min;
int Sec;
void setup()
{
  Wire.begin();
  rtc.begin();

  Serial.begin(9600);
  //rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
pinMode(RELAY, OUTPUT);
  //rtc.setTime(12, 43, 40);     // Set the time to 12:00:00 (24hr format)

  //rtc.setDate(19, 3, 2019);   // Set the date to January 1st, 2014
  delay(2000);
}
void loop()

{

  Serial.print("Time: ");
  Serial.println(rtc.getTimeStr());
  Serial.print("Time: ");
  Serial.println(rtc.getDateStr());
  t = rtc.getTime();
  Hor = t.hour;
  Min = t.min;
  Sec = t.sec;

  if ( Hor == 9 &&  Min == 00 && Sec == 00) //Comparing the current time with the Alarm time
  {
    digitalWrite(RELAY, HIGH);
    delay(20000);
    digitalWrite(RELAY, LOW);

  }

  else if ( Hor == 9 &&  Min == 46 && Sec == 00) //Comparing the current time with the Alarm time

  {
    digitalWrite(RELAY, HIGH);
    delay(6000);
    digitalWrite(RELAY, LOW);
  }

  else if ( Hor == 10 &&  Min == 31 && Sec == 00) //Comparing the current time with the Alarm time

  {
    digitalWrite(RELAY, HIGH);
    delay(6000);
    digitalWrite(RELAY, LOW);
  }
  else if ( Hor == 11 &&  Min == 15 && Sec == 00) //Comparing the current time with the Alarm time

  {
    digitalWrite(RELAY, HIGH);
    delay(14000);
    digitalWrite(RELAY, LOW);
  }
  else if ( Hor == 11 &&  Min == 31 && Sec == 00) //Comparing the current time with the Alarm time

  {
    digitalWrite(RELAY, HIGH);
    delay(14000);
    digitalWrite(RELAY, LOW);
  }
  else if ( Hor == 12 &&  Min == 15 && Sec == 00) //Comparing the current time with the Alarm time

  {
    digitalWrite(RELAY, HIGH);
    delay(6000);
    digitalWrite(RELAY, LOW);
  }

  else if ( Hor == 13 &&  Min == 00 && Sec == 00) //Comparing the current time with the Alarm time

  {
    digitalWrite(RELAY, HIGH);
    delay(14000);
    digitalWrite(RELAY, LOW);
  }

  else if ( Hor == 13 &&  Min == 45 && Sec == 00) //Comparing the current time with the Alarm time

  {
    digitalWrite(RELAY, HIGH);
    delay(14000);
    digitalWrite(RELAY, LOW);
  }

  else if ( Hor == 14 &&  Min == 30 && Sec == 00) //Comparing the current time with the Alarm time

  {
    digitalWrite(RELAY, HIGH);
    delay(6000);
    digitalWrite(RELAY, LOW);
  }
  else if ( Hor == 15 &&  Min == 15 && Sec == 00) //Comparing the current time with the Alarm time

  {
    digitalWrite(RELAY, HIGH);
    delay(6000);
    digitalWrite(RELAY, LOW);
  }
  else if ( Hor == 16 &&  Min == 00 && Sec == 00) //Comparing the current time with the Alarm time

  {
    digitalWrite(RELAY, HIGH);
    delay(14000);
    digitalWrite(RELAY, LOW);
  }
  else if ( Hor == 17 &&  Min == 15 && Sec == 00) //Comparing the current time with the Alarm time

  {
    digitalWrite(RELAY, HIGH);
    delay(20000);
    digitalWrite(RELAY, LOW);
  }
  delay(1000);

}
