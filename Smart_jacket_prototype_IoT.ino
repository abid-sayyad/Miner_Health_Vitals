#include <String.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);

float sensorValueMQ135;
float sensorValueMQ9;
float heart_rate;

void setup()
{
  mySerial.begin(9600);               // the GPRS baud rate   
  Serial.begin(9600);    // the GPRS baud rate 
}
 
void loop()
{
   heart_rate = analogRead(2);                   //read analog data from temp sensor
   sensorValueMQ135 = analogRead(0);       // read analog input pin 0
   sensorValueMQ9 = analogRead(1);       // read analog input pin 1 
   delay(100);   
         
   Serial.print("\nAirQua(CO2/ NOx/ NH3/ S/ C6H6)=");
   Serial.print(sensorValueMQ135);               // prints the value read

   Serial.print("\nAirQua(Inflamable gasses)=");
   Serial.print(sensorValueMQ9);               // prints the value read

   Serial.print("\nBPM : ");
   Serial.print(heart_rate);               // prints the value read

   
  if (mySerial.available())
    Serial.write(mySerial.read());
 
  mySerial.println("AT");
  delay(1000);
 
  mySerial.println("AT+CPIN?");
  delay(1000);
 
  mySerial.println("AT+CREG?");
  delay(1000);
 
  mySerial.println("AT+CGATT?");
  delay(1000);
 
  mySerial.println("AT+CIPSHUT");
  delay(1000);
 
  mySerial.println("AT+CIPSTATUS");
  delay(2000);
 
  mySerial.println("AT+CIPMUX=0");
  delay(2000);
 
    while(mySerial.available()!=0)
  Serial.write(mySerial.read());
 
  mySerial.println("AT+CSTT=\"bsnlnet\"");//start task and setting the APN,
  delay(1000);
 
    while(mySerial.available()!=0)
  Serial.write(mySerial.read());
 
  mySerial.println("AT+CIICR");//bring up wireless connection
  delay(3000);
 
    while(mySerial.available()!=0)
  Serial.write(mySerial.read());
 
  mySerial.println("AT+CIFSR");//get local IP adress
  delay(2000);
 
    while(mySerial.available()!=0)
  Serial.write(mySerial.read());
 
  mySerial.println("AT+CIPSPRT=0");
  delay(3000);
 
    while(mySerial.available()!=0)
  Serial.write(mySerial.read());
  
  mySerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(6000);
 
    while(mySerial.available()!=0)
  Serial.write(mySerial.read());
 
  mySerial.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
    while(mySerial.available()!=0)
  Serial.write(mySerial.read());
  
  String str="GET https://api.thingspeak.com/update?api_key=ZYXK6HCDW4UKB4NK&field1="+String(sensorValueMQ135)+"&field2="+String(sensorValueMQ9);
  
  Serial.println(str);
  mySerial.println(str);//begin send data to remote server
  
  delay(4000);
    while(mySerial.available()!=0)
  Serial.write(mySerial.read());
 
  mySerial.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet 
  mySerial.println();
 
    while(mySerial.available()!=0)
  Serial.write(mySerial.read());
 
  mySerial.println("AT+CIPSHUT");//close the connection
  delay(100);
    while(mySerial.available()!=0)
  Serial.write(mySerial.read());
} 
/*void ShowSerialData()
{
  while(mySerial.available()!=0)
  Serial.write(mySerial.read());
  delay(5000); 
  
}*/
