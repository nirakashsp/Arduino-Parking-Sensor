/// --- --------- --- ///
/// ---  includes --- ///
/// --- --------- --- ///
#include <Arduino.h>
#include<EEPROM.h>
///------------------------------------------------------------------------includes///

/// --- --------- --- ///
/// --- properties --- ///
/// --- --------- --- ///

/// Here are used variables for the project.
const int led = 13; /// led goes to our Led Diode
const int buzzer = 11; /// connects to our Piezo Speaker (buzzer)

/// Ultrasonic sensor
const int trig = 9; /// 'sends out a sound'
const int echo = 10; /// 'measures the trigger sound if reflected'
float speed = 0.0347 * 0.5; /// float 
long duration;
int distance;
float pingTime;

int buzNear = 20; /// Buzzer delay time on distance
int buzHigh = 50; 
int buzMid=130;
int buzFar =600;
int delayFar = 260;

int checkDist[5];
int currentCheckDist = 0;

boolean checking = false;
boolean parkState = false;
unsigned long time = 0;
int previousDist = 0;
int parkSecond = 0;
String lastParked; /// A variable to save last parked Distance.
///------------------------------------------------------------------------properties///



void setup() {
  pinMode(trig,OUTPUT);   /// Sets the ✨trigger✨ Pin give Output
  pinMode(echo,INPUT);    /// Sets the ✨echo✨ Pin to expect Input
  pinMode(buzzer,OUTPUT); /// Sets the ✨buzzer✨ Pin to expect Input
  pinMode(led,OUTPUT);    /// Sets the ✨led✨ Pin to expect Input
  Serial.begin(9600);     /// The serial communication starts. With Baud Rate(data symbols per second) 9600
  String LastParked = readStringFromEEPROM(0); /// Receive last parked data from the EEPROM.
  Serial.println(LastParked); /// Print LastParked Data.
}

void loop() {
  digitalWrite(trig,LOW); /// Before we run the sensor, we turn off the trigger to low;
  delayMicroseconds(20);
  digitalWrite(trig,HIGH); /// Sets the trig on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  pingTime = pulseIn(echo,HIGH);
  distance = (speed*pingTime);
  // Reads the Echo, returns the sound wave travel time in microseconds
  duration = pulseIn(echo,HIGH);

  Serial.println(checking);
  if (checking == false)
  {
    if(distance <= 20.0){
    digitalWrite(buzzer,HIGH);
    digitalWrite(led,HIGH);
    //digitalWrite(buzzer,LOW);
    // delay(buzNear);
  }
  else if(distance <= 30.0 && distance>20.0){
    digitalWrite(buzzer,HIGH);
    delay(buzHigh);
    digitalWrite(led,HIGH);
    digitalWrite(buzzer,LOW);
    delay(buzHigh);
  }
 else if(distance <= 30.0 && distance<60.0){
    digitalWrite(buzzer,HIGH);
    delay(buzMid);
    digitalWrite(led,HIGH);
    digitalWrite(buzzer,LOW);
    delay(buzMid);
  }

  else if(distance <= 60.0 && distance<120.0){
    digitalWrite(buzzer,HIGH);
    delay(buzFar);
    digitalWrite(led,HIGH);
    digitalWrite(buzzer,LOW);
    delay(buzFar);
  }
  else if(distance > 120){
    digitalWrite(buzzer,LOW);
  }
  // Prints the distance on the Serial Monitor

  }

  

  if(previousDist == distance || previousDist == distance-1 || previousDist == distance+1 ) {
    checking = true;
    time = millis();
  
  } else if(previousDist != distance){
    checking = false;
    time = 0;
    Serial.print("Distance: ");
    Serial.println(distance);
  }
  /// When car is hold still for fewer seconds then the car is stated as parked.
  if(time < millis() + 10000 && time!= 0){
    parkState = true;
    parkSecond++;
    /// If parked then print Parked and save data to EEPROM one Time only.
    if(parkState && parkSecond <= 1){
    Serial.println("parked");
    lastParked = "Last Parked in "+ distance ;
    /// Saving data to EEPROM using Function that saves.
    saveStringToEEPROM(0,lastParked);
    }
    delay(1000);
    /// When Car is Parked Buzzer should be turned off.
    digitalWrite(buzzer, LOW);
  }else{
    parkSecond = 0;
  }

  
  previousDist = distance;
}
/// Save String To EEPROM Method.
void saveStringToEEPROM(int address, const String data) {
  ///First it will save the length of the string and write the string.
  byte lengthOfString = data.length();
  EEPROM.write(address, lengthOfString);

  for (int i = 0; i < lengthOfString; i++) {
    EEPROM.write(address + 1 + i, data[i]);

  }
}

/// Read string from EEPROM Method.
String readStringFromEEPROM(int address) {
  int newStringLength = EEPROM.read(address);
  char data[newStringLength + 1];

  for (int i = 0; i < newStringLength; i++) {
    data[i] = EEPROM.read(address + 1 + i);
  }
  data[newStringLength] = '\0';
  return String(data);
}