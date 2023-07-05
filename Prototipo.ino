#include <Servo.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

const int servoPin1 = 9;    // Pin del primer servomotor
const int servoPin2 = 10;   // Pin del segundo servomotor
const int servoPin3 = 11;   // Pin del tercer servomotor   //revisar los pines sean correctos despues
const int servoPin4 = 12;   // Pin del cuarto servomotor
const int sensorPin = A0;   // Pin del sensor de luz
int lightThreshold = 150;   // Nivel de luz umbral para activar el movimiento del servomotor
const int Trigger = 2;      // Pin digital 2 para el Trigger del sensor ultrasonico
const int Echo = 3;         // Pin digital 3 para el Echo del sensor ultrasonico
const int LedPin = 6;

Servo servoMotor1;
Servo servoMotor2;
Servo servoMotor3;
Servo servoMotor4;


Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X); //Libreria
#define redpin 3
#define greenpin 5
#define bluepin 6
// set to false if using a common cathode LED
#define commonAnode true
// our RGB -> eye-recognized gamma color
byte gammatable[256];
int servoDelay = 10000;              // Duración del tiempo de espera en milisegundos (10 segundos)
int initialPosition = 0;             // Posición inicial del servomotor (90 grados)

void setup() {
  
  Serial.begin(9600);
Serial.begin(9600);//iniciailzamos la comunicación
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  pinMode(LedPin, OUTPUT);
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0

  servoMotor1.attach(servoPin1); // Adjuntar el primer servomotor al pin correspondiente
  servoMotor2.attach(servoPin2); // Adjuntar el segundo servomotor al pin correspondiente
  servoMotor3.attach(servoPin3); // Adjuntar el tercer servomotor al pin correspondiente
  servoMotor4.attach(servoPin4); // Adjuntar el cuarto servomotor al pin correspondiente
  
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
  servoMotor1.write(initialPosition); // Establecer la posición inicial del primer servomotor
  servoMotor2.write(initialPosition); // Establecer la posición inicial del segundo servomotor
  servoMotor3.write(initialPosition); // Establecer la posición inicial del tercer servomotor
  servoMotor4.write(initialPosition); // Establecer la posición inicial del cuarto servomotor
for (int i = 0; i < 256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;
 
    if (commonAnode) {
      gammatable[i] = 255 - x;
    } else {
      gammatable[i] = x;
    }
  }
 int lightLevel = analogRead(sensorPin); // Leer el nivel de luz del sensor
  float red, green, blue;
  tcs.setInterrupt(false);  // turn on LED
  delay(60);  // takes 50ms to read
  tcs.getRGB(&red, &green, &blue);
  tcs.setInterrupt(true);  // turn off LED


  Serial.print("R:\t"); Serial.print(int(red));
  Serial.print("\tG:\t"); Serial.print(int(green));
  Serial.print("\tB:\t"); Serial.print(int(blue));

  Serial.print("\n");
   // Verificar los valores de color para determinar el movimiento del servomotor
  if (red > green && red > blue && red>150)  {
    // Color Rojo detectado
    servoMotor1.write(180);               // Girar el servomotor a 180 grados
    delay(servoDelay);                 // Esperar durante el tiempo definido
  } else if (green > 95) {
    // Color Verde detectado
    servoMotor2.write(180);              // Girar el servomotor a 180 grados
    delay(servoDelay);                 // Esperar durante el tiempo definido
  } else if (blue>95) {
    // Color Azul detectado
    servoMotor3.write(180);             // Girar el servomotor a 180 grados
        delay(servoDelay);                 // Esperar durante el tiempo definido
  } else if (red > green && green > blue) {
  // Color Amarillo detectado
    servoMotor4.write(180);             // Girar el servomotor a 180 grados
        delay(servoDelay);                 // Esperar durante el tiempo definido
  }
long t; //timepo que demora en llegar el eco
 long d; //distancia en centimetros

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  
  Serial.print("Distancia: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();
  
  
  if (d < 5) {
    digitalWrite(LedPin, HIGH); // Encendemos el LED
  } else {
    digitalWrite(LedPin, LOW); // Apagamos el LED
  }
  delay(100);          //Hacemos una pausa de 100ms
  }
