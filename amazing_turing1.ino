#include <Servo.h>
Servo myServo;

int sensorValue = 0;

void setup() {
  myServo.attach(9);
  Serial.begin (9600);
  pinMode(10, OUTPUT);
}

void loop(){
  
  sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  delay(15);
   
  if(sensorValue >= 100){
    
  digitalWrite(10, HIGH);
  
  myServo.write(360);
  delay(15);
    
  }
  else
  {
    
  digitalWrite(10, LOW);  
  myServo.write(-360);
  delay(1500);
}
}

