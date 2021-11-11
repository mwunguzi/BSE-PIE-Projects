#include <RF24Network.h> //library for the radio frequency module
#include <RF24.h> //library for the radio frequency module
#include <SPI.h>
RF24 radio(9, 10);//pin connection for recieving and sending on arduino               
RF24Network network(radio);   
const uint16_t this_node = 00;//node for the master  
const uint16_t node01 = 01; //node for the right side      
const uint16_t node02 = 02; //node for the trolley
#define li1 2 //VFD pin connection to the arduino
#define li2 3 //VFD pin connection to the arduino
#define li3 4 //VFD pin connection to the arduino
#define li4 5 //VFD pin connection to the arduino   
void setup() {
 pinMode(A0,INPUT); // initializing left side the front distance sensor as input
 pinMode(A1,INPUT); // initializing left side the back distance sensor as input
 pinMode(A2,INPUT); // initializing right side the front distance sensor as input
 pinMode(A3,INPUT); // initializing right side the back distance sensor as input
 pinMode(A4,INPUT); // initializing trolley the right distance sensor as input
 pinMode(A5,INPUT); // initializing trolley the left distance sensor as input
 pinMode(li1, OUTPUT); // initializing VFD pin as outputs
  pinMode(li2, OUTPUT); // initializing VFD pin as outputs
  pinMode(li3, OUTPUT); // initializing VFD pin as outputs
  pinMode(li4, OUTPUT); // initializing VFD pin as outputs
  //===== starting the gantry when stopped=====//
 digitalWrite(li1,HIGH);
 digitalWrite(li2 ,HIGH);
 digitalWrite(li3,HIGH);
 digitalWrite(li4,LOW);
 Serial.begin(9600);
 Serial.println("Transmitter Starting ...");
 radio.begin();// initializing radio communication
  network.begin(90, this_node); // initializing network for this arduino
  radio.setDataRate(RF24_2MBPS); 
}
void loop() {
network.update(); // looking if thee is new data or connection
int lf,lb,rf,rb,tr,tl;
int incomingData;
//===== reading distances from the distance sensors=====//
  int voltage1 = analogRead(A0);
  int voltage2 = analogRead(A1);
  int voltage3 = analogRead(A2);
  int voltage4 = analogRead(A3);
  int voltage5 = analogRead(A4);
  int voltage6 = analogRead(A5);
  //=====mapping the distances to the desired values =====//
  lf=map(voltage1,0,1023,0,10000);// reading left side the front distance sensor 
  lb=map(voltage2,0,1023,0,10000);//reading left side the back distance sensor
  rf=map(voltage3,0,1023,0,10000);//reading right side the front distance sensor
  rb=map(voltage4,0,1023,0,10000);//reading right side the back distance sensor
  tl=map(voltage5,0,1023,0,10000);//reading trolley the right distance sensor
  tr=map(voltage6,0,1023,0,10000);//reading trolley the left distance sensor
  //=====printing the distances=====//
  Serial.print("lf: ");
  Serial.println(lf);
  Serial.print("lb: ");
  Serial.println(lb);
  Serial.print("rf: ");
  Serial.println(rf);
  Serial.print("rb: ");
  Serial.println(rb);
  Serial.print("tl: ");
  Serial.println(tl);
  Serial.print("tr: ");
  Serial.println(tr);
  delay(1000);
  /*
  if(l1<=300 or r1<=300){
   digitalWrite(li1,HIGH);
    digitalWrite(li2 ,LOW);
    digitalWrite(li3,HIGH);
    char text='b';
    RF24NetworkHeader header2(node01);     
    network.write(header2, &text, sizeof(text));
   }
  else if(l2<=300 or r2<=300){
    digitalWrite(li1,HIGH);
    digitalWrite(li2 ,LOW);
    digitalWrite(li3,HIGH);
    char text='b';
    RF24NetworkHeader header2(node01);     
    network.write(header2, &text, sizeof(text));
    }
  */
  //===== Receiving =====//
  /*while ( network.available() ) {  
    RF24NetworkHeader header;
    
    network.read(header, &incomingData, sizeof(incomingData)); 
  }
  Serial.println(incomingData); */
  
  //===== Sending =====//
  char sendcommand;
  if(Serial.available()) // checking if we received any command from the serial
 {
 sendcommand=Serial.read();
if(sendcommand =='s') // moving the whole gantry REVERSE
{
    digitalWrite(li1,LOW);
    digitalWrite(li2 ,HIGH);
    digitalWrite(li3,HIGH);
    RF24NetworkHeader header2(node01);     
    bool ok=network.write(header2, &sendcommand, sizeof(sendcommand));
    if (ok)
      Serial.println("ok.");
    else
      Serial.println("failed.");
}
 else if(sendcommand =='w') // moving the whole gantry FORWARD
 {
    digitalWrite(li1,HIGH);
    digitalWrite(li2,HIGH);
    digitalWrite(li3,LOW);
    RF24NetworkHeader header2(node01);     
    bool ok=network.write(header2, &sendcommand, sizeof(sendcommand));
     if (ok)
      Serial.println("ok.");
    else
      Serial.println("failed.");
 }
 else if(sendcommand =='b')// // STOPPING THE WHOLE GANTRY
 {
    digitalWrite(li1,HIGH);
    digitalWrite(li2 ,LOW);
    digitalWrite(li3,HIGH);
   RF24NetworkHeader header2(node01);     
  bool ok=network.write(header2, &sendcommand, sizeof(sendcommand));
   if (ok)
      Serial.println("ok.");
    else
      Serial.println("failed.");
 }else if(sendcommand =='f') //moving the right side FORWARD only
 {
   
    RF24NetworkHeader header2(node01);     
    bool ok=network.write(header2, &sendcommand, sizeof(sendcommand));
     if (ok)
      Serial.println("ok.");
    else
      Serial.println("failed.");
 }
 else if(sendcommand =='r') //moving the right side REVERSE only
 {
    RF24NetworkHeader header2(node01);     
    bool ok=network.write(header2, &sendcommand, sizeof(sendcommand));
     if (ok)
      Serial.println("ok.");
    else
      Serial.println("failed.");
 } else if(sendcommand =='p')//  STOPPING THE RIGHT SIDE ONLY
 {
    RF24NetworkHeader header2(node01);     
    bool ok=network.write(header2, &sendcommand, sizeof(sendcommand));
     if (ok)
      Serial.println("ok.");
    else
      Serial.println("failed.");
 } else if(sendcommand =='a') //moving the TROLLEY FORWARD only
 {
    RF24NetworkHeader header2(node02);     
    bool ok=network.write(header2, &sendcommand, sizeof(sendcommand));
    if (ok)
      Serial.println("ok.");
    else
      Serial.println("failed.");
 } else if(sendcommand =='t') //moving the TROLLEY REVERSE only
 {
    RF24NetworkHeader header2(node02);     
    bool ok=network.write(header2, &sendcommand, sizeof(sendcommand));
    if (ok)
      Serial.println("ok.");
    else
      Serial.println("failed.");
 }else if(sendcommand =='o')//STOPPING THE TROLLEY
 {
    RF24NetworkHeader header2(node02);     
    bool ok=network.write(header2, &sendcommand, sizeof(sendcommand));
    if (ok)
      Serial.println("ok.");
    else
      Serial.println("failed.");
 }
 else if(sendcommand =='x')// stopping the left side
{
    digitalWrite(li1,HIGH);
    digitalWrite(li2 ,LOW);
    digitalWrite(li3,HIGH);
  
}
 else if(sendcommand =='d')//moving the left side FORWARD
 {
    digitalWrite(li1,HIGH);
    digitalWrite(li2,HIGH);
    digitalWrite(li3,LOW);
 }
 else if(sendcommand =='e')//moving the left side Reverse
 {
    digitalWrite(li1,LOW);
    digitalWrite(li2 ,HIGH);
    digitalWrite(li3,HIGH);
 }
}
}  
