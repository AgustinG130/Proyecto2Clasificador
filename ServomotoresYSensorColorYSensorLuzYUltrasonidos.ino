#include <Servo.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

const int servoPin1 = 9;    // Pin del primer servomotor
const int servoPin2 = 10;   // Pin del segundo servomotor
const int servoPin3 = 11;   // Pin del tercer servomotor   //revisar los pines sean correctos despues
const int servoPin4 = 12;   // Pin del cuarto servomotor
const int sensorPin = A0;   // Pin del sensor de luz
int lightThreshold = 150;   // Nivel de luz umbral para activar el movimiento del servomotor
const int Trigger = 2;      // Pin digital 2 para el Trigger del sensor de color
const int Echo = 3;         // Pin digital 3 para el Echo del sensor de color
Servo servoMotor1;
Servo servoMotor2;
Servo servoMotor3; //declaro los servomotores
Servo servoMotor4;

const int Trigger1 = 13;    // Pin digital 13 para el Trigger del Sonido 1
const int Echo1 = 14;       // Pin digital 14 para el Echo del Sonido 1

const int Trigger2 = 8;     // Pin digital 8 para el Trigger del Sonido 2
const int Echo2 = 7;        // Pin digital 7 para el Echo del Sonido 2

const int Trigger3 = 9;     // Pin digital 9 para el Trigger del Sonido 3
const int Echo3 = 10;       // Pin digital 10 para el Echo del Sonido 3

const int Trigger4 = 12;    // Pin digital 12 para el Trigger del Sonido 4
const int Echo4 = 11;       // Pin digital 11 para el Echo del Sonido 4
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X); //Libreria

int servoDelay = 10000;              // Duración del tiempo de espera en milisegundos (10 segundos)
int initialPosition = 0;             // Posición inicial del servomotor (90 grados)

void setup() {
  Serial.begin(9600);

  // Configuración del Sonido 1
  pinMode(Trigger, OUTPUT); // Pin como salida
  pinMode(Echo, INPUT);  // Pin como entrada
  digitalWrite(Trigger, LOW); // Inicializamos el pin con 0

  // Configuración del Sonido 2
  pinMode(Trigger2, OUTPUT);
  pinMode(Echo2, INPUT);
  digitalWrite(Trigger2, LOW);
  
  // Configuración del Sonido 3
  pinMode(Trigger3, OUTPUT);
  pinMode(Echo3, INPUT);
  digitalWrite(Trigger3, LOW);
  
  // Configuración del Sonido 4
  pinMode(Trigger4, OUTPUT);
  pinMode(Echo4, INPUT);
  digitalWrite(Trigger4, LOW);

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

  int lightLevel = analogRead(sensorPin); // Leer el nivel de luz del sensor
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
  /* if (lightLevel > lightThreshold) {
    // Gira a la posicion inicial //revisar si es la que debe ir
    servoMotor1.write(initialPosition); // Volver a la posición inicial
    delay(1000); // Esperar 1 segundo antes de la siguiente lectura
  }*/

  if (d < 320) {
    Serial.print("Tacho lleno"); // Mandamos a la consola el estado
}
  
  // Sonido 2
  long t2; // Tiempo que demora en llegar el eco del Sonido 2
  long d2; // Distancia en centímetros del Sonido 2

  digitalWrite(Trigger2, HIGH);
  delayMicroseconds(10);          // Enviamos un pulso de 10us
  digitalWrite(Trigger2, LOW);
  
  t2 = pulseIn(Echo2, HIGH); // Obtenemos el ancho del pulso del sensor 2
  d2 = t2 / 59;
  
  if (d2 < 320) {
    Serial.print("Tacho lleno"); // Mandamos a la consola el estado
}
  
  // Sonido 3
  long t3; // Tiempo que demora en llegar el eco del Sonido 3
  long d3; // Distancia en centímetros del Sonido 3

  digitalWrite(Trigger3, HIGH);
  delayMicroseconds(10);          // Enviamos un pulso de 10us
  digitalWrite(Trigger3, LOW);
  
  t3 = pulseIn(Echo3, HIGH); // Obtenemos el ancho del pulso del sensor 3
  d3 = t3 / 59;
  
  if (d3 < 320) {
    Serial.print("Tacho lleno"); // Mandamos a la consola el estado
}
  
  // Sonido 4
  long t4; // Tiempo que demora en llegar el eco del Sonido 4
  long d4; // Distancia en centímetros del Sonido 4

  digitalWrite(Trigger4, HIGH);
  delayMicroseconds(10);          // Enviamos un pulso de 10us
  digitalWrite(Trigger4, LOW);
  
  t4 = pulseIn(Echo4, HIGH); // Obtenemos el ancho del pulso del sensor 4
  d4 = t4 / 59;
  
  if (d4 < 320) {
    Serial.print("Tacho lleno"); // Mandamos a la consola el estado
}
}