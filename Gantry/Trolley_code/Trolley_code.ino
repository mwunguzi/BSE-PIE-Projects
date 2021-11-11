#include <RF24Network.h> //library for the radio frequency module
#include <RF24.h> //library for the radio frequency module
#include <SPI.h>
RF24 radio(9, 10);//pin connection for recieving and sending on arduino               
RF24Network network(radio); //    
const uint16_t this_node = 02; //node for this arduino  
const uint16_t base00 = 00;// node for the master 
unsigned long start=0;
bool delaying=false;              
void setup() {
  pinMode(A2,INPUT);
  pinMode(6, OUTPUT);// relay pin
  pinMode(7, OUTPUT);//relay pin
  Serial.begin(9600);
  SPI.begin();// initializing SPI connection
  radio.begin();// initializing radio communication
  network.begin(90, this_node);  // initializinf network for this arduino
  radio.setDataRate(RF24_2MBPS);
  delaying=true;
  start=millis();
}
void loop() {
  network.update(); // looking if thee is new data or connection
 
  
  //===== Receiving =====//
   while ( network.available() ) {  // checking if we received any command
    RF24NetworkHeader header;
    char received;
    network.read(header, &received, sizeof(received));
    Serial.println(received);
    if(received == 'a')// moving the trolley on left
{
    digitalWrite(6,LOW);
    digitalWrite(7,HIGH);
    Serial.println("received");
}

  else if(received =='t')// moving the trolley on right
 {
    digitalWrite(6,HIGH);
    digitalWrite(7,LOW);
    Serial.println("received");
 }else if(received =='o')// stopping the trolley 
 {
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
    Serial.println("received");
 }
  }
}
