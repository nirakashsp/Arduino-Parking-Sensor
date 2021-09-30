#include <Arduino.h>
// Defining All pins number
const int led = 13;
const int buzzer = 11;
const int trig = 9;
const int echo = 10;
float speed = 0.0347;
int buzNear = 20;
int buzHigh = 50;
int buzMid=130;
int buzFar =600;
int delayFar = 260;
// Here are used variables for the project.
long duration;
int distance;
int safetyDistance;
float pingTime;

void setup() {
  pinMode(trig,OUTPUT); // Sets the trigPin as an Output
  pinMode(echo,INPUT); // sets the EchoPin as an INput
  pinMode(buzzer,OUTPUT);
  pinMode(led,OUTPUT);
  Serial.begin(9600); // here the serial communication starts.

}

void loop() {
  // Before we run the sensor, we clear the trigger to low;
  digitalWrite(trig,LOW);
  delayMicroseconds(20);
  // Sets the trig on HIGH state for 10 micro seconds
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  pingTime = pulseIn(echo,HIGH);
  distance = (speed*pingTime*0.5);
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