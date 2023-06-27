#include <Servo.h>

const int sensorPin = A0;   // Pin del sensor de luz
const int servoPin = 9;     // Pin del servomotor

Servo servoMotor;
int lightThreshold = 1;   // Nivel de luz umbral para activar el movimiento del servomotor
int servoDelay = 10000;     // Duración del tiempo de espera en milisegundos (10 segundos)
int initialPosition = 0;   // Posición inicial del servomotor (90 grados)

void setup() {
  Serial.begin(9600);
  servoMotor.attach(servoPin); // Adjuntar el servomotor al pin correspondiente
  servoMotor.write(initialPosition); // Establecer la posición inicial del servomotor
}

void loop() {
  int lightLevel = analogRead(sensorPin); // Leer el nivel de luz del sensor

  Serial.print("Nivel de luz: ");
  Serial.println(lightLevel);

  if (lightLevel > lightThreshold) {
    // Girar el servomotor a 90 grados
    servoMotor.write(180);
    delay(10000); // Esperar durante el tiempo definido
    servoMotor.write(initialPosition);// Volver a la posición inicial
    delay(10000); // Esperar 1 segundo antes de la siguiente lectura
    }
  }
