#include <RF24Network.h> //library for the radio frequency module
#include <RF24.h> //library for the radio frequency module
#include <SPI.h>
RF24 radio(9, 10);//pin connection for recieving and sending on arduino               
RF24Network network(radio);
const uint16_t this_node = 01;//node for this arduino 
const uint16_t base00 = 00; //node for the master
#define li1 2 //VFD pin connection to the arduino
#define li2 3 //VFD pin connection to the arduino
#define li3 4 //VFD pin connection to the arduino
#define li4 5 //VFD pin connection to the arduino             
void setup() {
  Serial.begin(115200);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(li1, OUTPUT); // initializing VFD pin as outputs
  pinMode(li2, OUTPUT); // initializing VFD pin as outputs
  pinMode(li3, OUTPUT); // initializing VFD pin as outputs
  pinMode(li4, OUTPUT); // initializing VFD pin as outputs

  //===== starting the gantry when stopped=====//
  digitalWrite(li1,HIGH);
  digitalWrite(li2 ,HIGH);
  digitalWrite(li3,HIGH);
  digitalWrite(li4,LOW);
  radio.begin();// initializing radio communication
  network.begin(90, this_node); // initializing network for this arduino
  radio.setDataRate(RF24_2MBPS);  
}
void loop() {
  network.update(); // looking if thee is new data or connection
  //===== Receiving =====//
   while ( network.available() ) {   // checking if we received any command
    RF24NetworkHeader header;
    char received;
    network.read(header, &received, sizeof(received));
    if(received == 'b' or received =='p') // STOP the right side
{
    digitalWrite(li1,HIGH);
    digitalWrite(li2 ,LOW);
    digitalWrite(li3,HIGH);
}

  else if(received =='w' or received =='f') // moving FORWARD
 {
    digitalWrite(li1,HIGH);
    digitalWrite(li2,HIGH);
    digitalWrite(li3,LOW);
    Serial.println("received");
 }
  else if(received =='s' or received =='r' )// moving REVERSE
 {
    digitalWrite(li1,LOW);
    digitalWrite(li2 ,HIGH);
    digitalWrite(li3,HIGH);
    Serial.println("received");
 } 
  }
}
