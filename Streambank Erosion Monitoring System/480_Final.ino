#include <SPI.h> //for the SD card module
#include <SD.h>  //for the SD card module
#include <Wire.h> //for the RTC
#include <TimeLib.h>
#include <DS3232RTC.h>
#include <avr/sleep.h>
#include <avr/power.h>

const byte rxPIN = 0;  //indicate rx pin on arduino board
const byte txPIN = 1;  //indicate tx pine on arduino board
const byte rtcAlarmPin = 3; //indicate pin D3 for external interrupt
int chipSelect = 4;  //indicate pin where CS port for SD Card Module is connected
String distance = String("");
double distanceSum = 0; //
long distance_reading = 0;
double distanceAverage = 0;
char inChar = '0';
int i = 0;
tmElements_t tm;


// Create a file to store the data
File myFile;


void setup() {
  pinMode(rxPIN, INPUT); //set the rxPIN as an input coming from the sensor
  pinMode(txPIN, OUTPUT); //set the txPIN as a output to the sensor
  Serial.begin(9600); //initialize the serial monitor
  Wire.begin();


  Serial.print("Initializing SD card...");

  if(!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");//if there is no information going from the SD card module into the indicated chip select pin on the arduino board, this message will be printed to the serial monitor
    return;
  }
  Serial.println("initialization done.");//if there is information going into the chip select pin, this message will be printed to the serial monitor
    
  //open file
  myFile=SD.open("DATA.txt", FILE_WRITE);

  // if the file opened ok, write to it:
  if (myFile) {
    Serial.println("File opened ok");
    // print the headings for our data
    myFile.println("Date,Time,Distance mm");
  }
  myFile.close();

  pinMode(rtcAlarmPin, INPUT_PULLUP); //Set pin to an interrupt using INPUT_PULLUP
  RTC.squareWave(SQWAVE_NONE); //Disable the default square wave coming from the RTC

  RTC.setAlarm(ALM1_MATCH_SECONDS, 0, 0, 0, 0 ); // setAlarm Syntax (RTC.setAlarm(alarmType, seconds, minutes, hours, dayOrDate);)
  RTC.alarm(ALARM_1);
  RTC.alarmInterrupt(ALARM_1, true);  // Enable alarm 1 interrupt A1IE

}

void loggingDateTime(){
    setSyncProvider(RTC.get); //Get the current date and time from the RTC
    myFile = SD.open("DATA.txt", FILE_WRITE); //open the file

  if (myFile) {
    //print the current date and time in the DATA.txt file
    myFile.print(year(), DEC);
    myFile.print('/');
    myFile.print(month(), DEC);
    myFile.print('/');
    myFile.print(day(), DEC);
    myFile.print(',');
    myFile.print(hour(), DEC);
    myFile.print(':');
    myFile.print(minute(), DEC);
    myFile.print(':');
    myFile.print(second(), DEC);
    myFile.print(",");
  }
    myFile.close(); //close the file

    //also print date and time to serial monitor
    Serial.print(year(), DEC);
    Serial.print('/');
    Serial.print(month(), DEC);
    Serial.print('/');
    Serial.print(day(), DEC);
    Serial.print(' ');
    Serial.print(hour(), DEC);
    Serial.print(':');
    Serial.print(minute(), DEC);
    Serial.print(':');
    Serial.print(second(), DEC);
    Serial.println();
  
  
}

void loggingDistance(){
  myFile = SD.open("DATA.txt", FILE_WRITE); //open the file
  if (myFile) {
    Serial.println("open with success");
    myFile.println(distanceAverage); //print the average of 50 distance readings into the DATA.txt file
  }
  myFile.close(); //close the file

  //print the logged distance to the screen
  Serial.print("distance average is: ");
  Serial.println(distanceAverage);
  Serial.print('\n');
}

// Interrupt Service Routine (ISR) function
void wake ()
{
  sleep_disable();
  detachInterrupt (digitalPinToInterrupt (3)); // Disable interrupts on D3
}

void sleepNow ()
{
  sleep_enable();
  attachInterrupt (digitalPinToInterrupt(3), wake, FALLING);  // Wake on falling edge of D3
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  Serial.println("sleep mode now");
  delay(1000);
  sleep_cpu();
  Serial.println("just woke up");
}


void loop() {
 
  while(i < 50) {  
digitalWrite(txPIN, HIGH); //send a high singal to the sensor so it knows to take readings

    //check to see if there is a new serial output from the sensor
    if(Serial.available()){
        inChar = Serial.read(); //if there is a serial output, save the character as inChar
        if(isDigit(inChar)){
          //if that character is a digit, add it to the distance string
          distance += inChar;
        }
        if (inChar == '\r'){
          distance_reading = distance.toInt();
          if (distance_reading > 4999){
           Serial.print("Bad reading: ");
           Serial.println(distance_reading);
           distance = String("");
           distance_reading = 0;
          }
          else {
          Serial.print("The distance is: ");
          Serial.println(distance_reading);
          //once the incoming character is a tab, which means that the sensor is done sending that distance reading, convert the distance characters already collected to an integer and add them into the distance sum
          distanceSum = distanceSum + distance_reading;
          distance_reading = 0;
          distance = String(""); //reset the distance string
          i++; //increment i, the loop will break after 50 readings
          }
         
          }
      }
    }

Serial.print("The distance sum is: ");
Serial.println(distanceSum);

distanceAverage = distanceSum/50; //take the average of the readings
//run the two logging programs to write on the SD card
loggingDateTime();
loggingDistance();
//reset all necessary variables

i = 0;
distanceSum = 0;
distanceAverage = 0;

Serial.println("Entering sleep");
  delay(100);

  sleepNow(); // Enter sleep

  Serial.println("Awake...");
  if (RTC.alarm(ALARM_1))
  {
    RTC.read(tm);
    RTC.setAlarm(ALM1_MATCH_MINUTES, 0, (tm.Minute + 5) % 60, 0, 0); //set an alarm for 5 minutes from now
  }

}
