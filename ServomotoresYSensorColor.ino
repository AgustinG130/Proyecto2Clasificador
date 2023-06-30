#include <Servo.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

const int servoPin1 = 9;    // Pin del primer servomotor
const int servoPin2 = 10;   // Pin del segundo servomotor
const int servoPin3 = 11;   // Pin del tercer servomotor
const int servoPin4 = 12;   // Pin del cuarto servomotor
const int Trigger = 2;      // Pin digital 2 para el Trigger del sensor de color
const int Echo = 3;         // Pin digital 3 para el Echo del sensor de color
Servo servoMotor1;
Servo servoMotor2;
Servo servoMotor3; //declaro los servomotores
Servo servoMotor4;

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X); //Libreria

int servoDelay = 10000;              // Duración del tiempo de espera en milisegundos (10 segundos)
int initialPosition = 0;             // Posición inicial del servomotor (90 grados)

void setup() {
  Serial.begin(9600);

  servoMotor1.attach(servoPin1); // Adjuntar el primer servomotor al pin correspondiente
  servoMotor2.attach(servoPin2); // Adjuntar el segundo servomotor al pin correspondiente
  servoMotor3.attach(servoPin3); // Adjuntar el tercer servomotor al pin correspondiente
  servoMotor4.attach(servoPin4); // Adjuntar el cuarto servomotor al pin correspondiente
  
  servoMotor1.write(initialPosition); // Establecer la posición inicial del primer servomotor
  servoMotor2.write(initialPosition); // Establecer la posición inicial del segundo servomotor
  servoMotor3.write(initialPosition); // Establecer la posición inicial del tercer servomotor
  servoMotor4.write(initialPosition); // Establecer la posición inicial del cuarto servomotor

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found... check your connections");
    while (1);
  }

  pinMode(Trigger, OUTPUT);          // Pin como salida
  pinMode(Echo, INPUT);              // Pin como entrada
  digitalWrite(Trigger, LOW);
}

void loop() {
  uint16_t red, green, blue, clear;
  tcs.getRawData(&red, &green, &blue, &clear);

  Serial.print("Red: "); Serial.print(red); 
  Serial.print(" Green: "); Serial.print(green); 
  Serial.print(" Blue: "); Serial.print(blue); 
  Serial.print(" Clear: "); Serial.println(clear);

  long t; // Tiempo que demora en llegar el eco
  long d; // Distancia en centímetros

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);             // Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);

  t = pulseIn(Echo, HIGH);            // Obtenemos el ancho del pulso
  d = t / 59;                         // Escalamos el tiempo a una distancia en cm

  Serial.print("Distancia: ");
  Serial.print(d);                     // Enviamos serialmente el valor de la distancia
  Serial.println(" cm");

  // Verificar los valores de color para determinar el movimiento del servomotor
  if (red > green && red > blue && red > clear) {
    // Color Rojo detectado
    servoMotor1.write(180);               // Girar el servomotor a 180 grados
    delay(servoDelay);                 // Esperar durante el tiempo definido
  } else if (green > red && green > blue && green > clear) {
    // Color Verde detectado
    servoMotor2.write(180);              // Girar el servomotor a 180 grados
    delay(servoDelay);                 // Esperar durante el tiempo definido
  } else if (blue > red && blue > green && blue > clear) {
    // Color Azul detectado
    servoMotor3.write(180);             // Girar el servomotor a 180 grados
        delay(servoDelay);                 // Esperar durante el tiempo definido
  } else if (red > green && green > blue && blue > clear) {
  // Color Amarillo detectado
    servoMotor4.write(180);             // Girar el servomotor a 180 grados
        delay(servoDelay);                 // Esperar durante el tiempo definido
  }
}