#include <Servo.h>

const int sensorPin = A0;   // Pin del sensor de luz
const int servoPin = 9;     // Pin del servomotor
const int Trigger = 2;   // Pin digital 2 para el Trigger del sensor
const int Echo = 3;   // Pin digital 3 para el Echo del sensor
const int LedPin = 4;  // Pin del LED

Servo servoMotor;
int lightThreshold = 1;
int servoDelay = 10000;
int initialPosition = 0;
int lightLevel =0;

void setup() {
  Serial.begin(9600);
  pinMode(Trigger, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(LedPin, OUTPUT);
  digitalWrite(Trigger, LOW);
  servoMotor.attach(servoPin);
  servoMotor.write(initialPosition);
}

void loop() {
  long t;
  long d;

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH);
  d = t / 59;
  
  Serial.print("Distancia: ");
  Serial.print(d);
  Serial.print("cm");
  Serial.println();

  int lightLevel = analogRead(sensorPin);

  Serial.print("Nivel de luz: ");
  Serial.println(lightLevel);

  if (d > 150 && lightLevel > lightThreshold) {
    servoMotor.write(180);
    delay(10000);
    servoMotor.write(initialPosition);
    delay(10000);
  }
}
