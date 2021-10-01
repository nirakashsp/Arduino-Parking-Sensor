/// --- --------- --- ///
/// ---  includes --- ///
/// --- --------- --- ///
#include <Arduino.h>
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
///------------------------------------------------------------------------properties///


void setup() {
  pinMode(trig,OUTPUT);   /// Sets the ✨trigger✨ Pin give Output
  pinMode(echo,INPUT);    /// Sets the ✨echo✨ Pin to expect Input
  pinMode(buzzer,OUTPUT); /// Sets the ✨buzzer✨ Pin to expect Input
  pinMode(led,OUTPUT);    /// Sets the ✨led✨ Pin to expect Input
  Serial.begin(9600);     /// The serial communication starts. With Baud Rate(data symbols per second) 9600

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
  Serial.print("Distance: ");
  Serial.println(distance);
  
}