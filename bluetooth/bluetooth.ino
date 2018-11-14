#include<SoftwareSerial.h>
#define PIN A5
SoftwareSerial BT(10,11);
String readdata;
char data = 0;            //Variable for storing received data
bool ledOn = false;
int startDelay, stopAfter;

void setup()
{
    BT.begin(38400);
    Serial.begin(9600);   //Sets the baud for serial data transmission                               
    pinMode(PIN, OUTPUT);  //Sets digital pin 13 as output pin
}

void loop()
{
   while(BT.available())      // Send data only when you receive data:
   {
    delay(10);
      data = BT.read();
      readdata+=data;
   }

   int bulb_1, bulb_2;
   //Read the incoming data & store into data
   if(readdata.length()>0)
   {
      Serial.print(readdata);          //Print Value inside data in Serial monitor
      Serial.print("\n");   

      if(readdata == "1") {
        bulb_1 = readdata.toInt();
        bulb_2 = 0;
      }

      if(readdata == "2") {
        bulb_1 = 0;
        bulb_2 = readdata.toInt();
      }

      if(readdata == "12") {
        bulb_1 = 1;
        bulb_2 = 2;
      }
           
      if(readdata == "ON") {             // Checks whether value of data is equal to 1
         analogWrite(PIN, 255);
         readdata = "";
         ledOn = true;
      }
      else if(readdata == "OFF") {         //  Checks whether value of data is equal to 0
         analogWrite(PIN, 0);    //If value is 0 then LED turns OFF
         readdata = "";
         ledOn = false;
      }
      else if(readdata != "") {
        if(readdata[0] == 'b') {
          startDelay = readdata.substring(1, 4).toInt();
          stopAfter = readdata.substring(6, 9).toInt();
          delay(startDelay);
          analogWrite(PIN, (readdata.substring(10).toInt()));  
          delay(stopAfter);
          analogWrite(PIN, 0);
        }
        else
          analogWrite(PIN, readdata.toInt());
        readdata="";
        ledOn = true;
      }
   }
}
