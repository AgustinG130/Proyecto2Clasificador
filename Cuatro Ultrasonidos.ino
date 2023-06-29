// Sensor 1
const int Trigger = 2;   // Pin digital 2 para el Trigger del Sonido 1
const int Echo = 3;      // Pin digital 3 para el Echo del Sonido 1
const int LedPin = 6;    // Pin digital 6 para el LED del Sonido 1

// Sensor 2
const int Trigger2 = 8;   // Pin digital 8 para el Trigger del Sonido 2
const int Echo2 = 7;      // Pin digital 7 para el Echo del Sonido 2
const int LedPin2 = 5;    // Pin digital 5 para el LED del Sonido 2

// Sensor 3
const int Trigger3 = 9;   // Pin digital 9 para el Trigger del Sonido 3
const int Echo3 = 10;      // Pin digital 10 para el Echo del Sonido 3
const int LedPin3 = 4;    // Pin digital 4 para el LED del Sonido 3

// Sensor 4
const int Trigger4 = 12;   // Pin digital 12 para el Trigger del Sonido 3
const int Echo4 = 11;      // Pin digital 11 para el Echo del Sonido 3
const int LedPin4 = 13;   // Pin digital 1 para el LED del Sonido 3

void setup() {
  Serial.begin(9600);    // Iniciamos la comunicación

  // Configuración del Sonido 1
  pinMode(Trigger, OUTPUT); // Pin como salida
  pinMode(Echo, INPUT);  // Pin como entrada
  pinMode(LedPin, OUTPUT);
  digitalWrite(Trigger, LOW); // Inicializamos el pin con 0

  // Configuración del Sonido 2
  pinMode(Trigger2, OUTPUT);
  pinMode(Echo2, INPUT);
  pinMode(LedPin2, OUTPUT);
  digitalWrite(Trigger2, LOW);
  
  // Configuración del Sonido 3
  pinMode(Trigger3, OUTPUT);
  pinMode(Echo3, INPUT);
  pinMode(LedPin3, OUTPUT);
  digitalWrite(Trigger3, LOW);
  
  // Configuración del Sonido 4
  pinMode(Trigger4, OUTPUT);
  pinMode(Echo4, INPUT);
  pinMode(LedPin4, OUTPUT);
  digitalWrite(Trigger4, LOW);
}

void loop() {
  // Sonido 1
  long t; // Tiempo que demora en llegar el eco
  long d; // Distancia en centímetros

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          // Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH); // Obtenemos el ancho del pulso
  d = t / 59;             // Escalamos el tiempo a una distancia en cm
  
  Serial.print("Sonido 1 - Distancia: ");
  Serial.print(d);      // Enviamos serialmente el valor de la distancia
  Serial.println(" cm");
  
  if (d < 320) {
    digitalWrite(LedPin, HIGH); // Encendemos el LED del sensor 1
  } else {
    digitalWrite(LedPin, LOW); // Apagamos el LED del sensor 1
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
    digitalWrite(LedPin2, HIGH); // Encendemos el LED del sensor 2
  } else {
    digitalWrite(LedPin2, LOW); // Apagamos el LED del sensor 2
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
    digitalWrite(LedPin3, HIGH); // Encendemos el LED del sensor 3
  } else {
    digitalWrite(LedPin3, LOW); // Apagamos el LED del sensor 3
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
    digitalWrite(LedPin4, HIGH); // Encendemos el LED del sensor 4
  } else {
    digitalWrite(LedPin4, LOW); // Apagamos el LED del sensor 4
  }
}