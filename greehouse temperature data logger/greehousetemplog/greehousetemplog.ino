#include<Wire.h>
#include<SD.h> //sd library
#include<dht.h> //library for the temperature sensor DHT11.
#include <DS3232RTC.h> //library for the RTC on the board
#include<LowPower.h>
dht sensor1,sensor2,sensor3,sensor4;
File templog;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
    Wire.begin();
    pinMode(10,OUTPUT);
    Serial.print("Initializing SD card...");

  if(!SD.begin(10)) {
    Serial.println("initialization failed!");//if there is no information going from the SD card module into the indicated chip select pin on the arduino board, this message will be printed to the serial monitor
    return;
  }
  Serial.println("initialization done.");//if there is information going into the chip select pin, this message will be printed to the serial monitor
    
  //open file
  templog=SD.open("templog.txt", FILE_WRITE);

  // if the file opened ok, write to it:
  if (templog) {
    Serial.println("File opened ok");
    // print the headings for our table
    templog.println("Name,Date,Time,Temperature c,Temperature f");
  }
  templog.close();
}

void loop() {
  // put your main code here, to run repeatedly
  int n1=0,n2=0,n3=0,n4=0;
  int tempc1,tempc2,tempc3,tempc4;
  int tempf1,tempf2,tempf3,tempf4;
  int tempsum1=0.0,tempsum2=0.0,tempsum3=0.0,tempsum4=0.0;
  int averagetemp1,averagetemp2,averagetemp3,averagetemp4;
  int reading1,reading2,reading3,reading4;
 for(int i=0; i<60; i++){
  sensor1.read11(4);
  reading1=sensor1.temperature;
  if(reading1>1){
    n1+=1;
  tempsum1=tempsum1+reading1;
  reading1=0;
  }
 }
 averagetemp1=tempsum1/n1;
 n1=0;
 tempc1=averagetemp1;
 tempf1=(tempc1*9/5)+32.00;
 templog=SD.open("templog.txt",FILE_WRITE);
 if (templog) {
  setSyncProvider(RTC.get);
    Serial.println("open with success");
    templog.print("sensor1 ");
    templog.print(year(), DEC);
    templog.print('/');
    templog.print(month(), DEC);
    templog.print('/');
    templog.print(day(), DEC);
    templog.print(',');
    templog.print(hour(), DEC);
    templog.print(':');
    templog.print(minute(), DEC);
    templog.print(':');
    templog.print(second(), DEC);
    templog.print(", ");
    templog.print(tempc1); //print the average of 60 temperature readings into the templog.txt file
    templog.print(" c ");
    templog.print(tempf1);
    templog.println(" f "); 
  }
  templog.close(); //close the file
Serial.println("open with success");
    Serial.print("sensor1 ");
    Serial.print(year(), DEC);
    Serial.print('/');
    Serial.print(month(), DEC);
    Serial.print('/');
    Serial.print(day(), DEC);
    Serial.print(',');
    Serial.print(hour(), DEC);
    Serial.print(':');
    Serial.print(minute(), DEC);
    Serial.print(':');
    Serial.print(second(), DEC);
    Serial.print(", ");
    Serial.print(tempc1); //print the average of 60 temperature readings into the DATA.txt file
    Serial.print(" c ");
    Serial.print(tempf1);
    Serial.println(" f ");
 for(int i=0; i<60; i++){
  sensor2.read11(5);
  reading2=sensor2.temperature;
  if(reading2>1){
  tempsum2=tempsum2+reading2;
  reading2=0;
  n2+=1;
  }
 }
 averagetemp2=tempsum2/n2;
 n2=0;
 tempc2=averagetemp2;
 tempf2=(tempc2*9/5)+32;
 templog=SD.open("templog.txt",FILE_WRITE);
 if (templog) {
  setSyncProvider(RTC.get);
    Serial.println("open with success");
    templog.print("sensor2 ");
    templog.print(year(), DEC);
    templog.print('/');
    templog.print(month(), DEC);
    templog.print('/');
    templog.print(day(), DEC);
    templog.print(',');
    templog.print(hour(), DEC);
    templog.print(':');
    templog.print(minute(), DEC);
    templog.print(':');
    templog.print(second(), DEC);
    templog.print(", ");
    templog.print(tempc2); //print the average of 50 distance readings into the DATA.txt file
     templog.print(" c ");
    templog.print(tempf2); 
     templog.println(" f ");
  }
  templog.close(); //close the file
  Serial.println("open with success");
    Serial.print("sensor2 ");
    Serial.print(year(), DEC);
    Serial.print('/');
    Serial.print(month(), DEC);
    Serial.print('/');
    Serial.print(day(), DEC);
    Serial.print(',');
    Serial.print(hour(), DEC);
    Serial.print(':');
    Serial.print(minute(), DEC);
    Serial.print(':');
    Serial.print(second(), DEC);
    Serial.print(", ");
    Serial.print(tempc2); //print the average of 60 temperature readings into the DATA.txt file
    Serial.print(" c ");
    Serial.print(tempf2);
    Serial.println(" f ");
 for(int i=0; i<60; i++){
  sensor3.read11(6);
  reading3=sensor3.temperature;
  if(reading3>1){
  tempsum3=tempsum3+reading3;
  reading3=0;
  n3+=1;
  }
 }
 averagetemp3=tempsum3/n3;
 n3=0;
 tempc3=averagetemp3;
 tempf3=(tempc3*9/5)+32;
 templog=SD.open("templog.txt",FILE_WRITE);
 if (templog) {
  setSyncProvider(RTC.get);
    Serial.println("open with success");
    templog.print("sensor3 ");
    templog.print(year(), DEC);
    templog.print('/');
    templog.print(month(), DEC);
    templog.print('/');
    templog.print(day(), DEC);
    templog.print(',');
    templog.print(hour(), DEC);
    templog.print(':');
    templog.print(minute(), DEC);
    templog.print(':');
    templog.print(second(), DEC);
    templog.print(", ");
    templog.print(tempc3); //print the average of 50 distance readings into the DATA.txt file
     templog.print(" c ");
    templog.print(tempf3);
     templog.println(" f "); 
  }
  templog.close(); //close the file
  Serial.println("open with success");
    Serial.print("sensor3 ");
    Serial.print(year(), DEC);
    Serial.print('/');
    Serial.print(month(), DEC);
    Serial.print('/');
    Serial.print(day(), DEC);
    Serial.print(',');
    Serial.print(hour(), DEC);
    Serial.print(':');
    Serial.print(minute(), DEC);
    Serial.print(':');
    Serial.print(second(), DEC);
    Serial.print(", ");
    Serial.print(tempc3); //print the average of 60 temperature readings into the DATA.txt file
    Serial.print(" c ");
    Serial.print(tempf3);
    Serial.println(" f ");
 for(int i=0; i<60; i++){
  sensor4.read11(7);
  reading4=sensor4.temperature;
  if(reading4>1){
  tempsum4=tempsum4+reading4;
  reading4=0;
  n4+=1;
  }
 }
 averagetemp4=tempsum4/n4;
 n4=0;
 tempc4=averagetemp4;
 tempf4=(tempc4*9/5)+32;
 templog=SD.open("templog.txt",FILE_WRITE);
 if (templog) {
  setSyncProvider(RTC.get);
    Serial.println("open with success");
    templog.print("sensor4 ");
    templog.print(year(), DEC);
    templog.print('/');
    templog.print(month(), DEC);
    templog.print('/');
    templog.print(day(), DEC);
    templog.print(',');
    templog.print(hour(), DEC);
    templog.print(':');
    templog.print(minute(), DEC);
    templog.print(':');
    templog.print(second(), DEC);
    templog.print(", ");
    templog.print(tempc4); //print the average of 50 distance readings into the DATA.txt file
     templog.print(" c ");
    templog.print(tempf4); 
     templog.println(" f ");
  }
  templog.close(); //close the file
  Serial.println("open with success");
    Serial.print("sensor4 ");
    Serial.print(year(), DEC);
    Serial.print('/');
    Serial.print(month(), DEC);
    Serial.print('/');
    Serial.print(day(), DEC);
    Serial.print(',');
    Serial.print(hour(), DEC);
    Serial.print(':');
    Serial.print(minute(), DEC);
    Serial.print(':');
    Serial.print(second(), DEC);
    Serial.print(", ");
    Serial.print(tempc4); //print the average of 60 temperature readings into the DATA.txt file
    Serial.print(" c ");
    Serial.print(tempf4);
    Serial.println(" f ");
    delay(500);
   for(int i=0; i<114; i++){
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
  
}

