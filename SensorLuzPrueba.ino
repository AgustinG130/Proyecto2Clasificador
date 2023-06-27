const int sensorPin = 6;
const int LedPin = 2;

void setup() {
  Serial.begin(9600);   //iniciar puerto serie
  pinMode(sensorPin , INPUT);  //definir pin como entrada
  pinMode(LedPin, OUTPUT);
}
 
void loop(){
  int value = 0;
  value = digitalRead(sensorPin );  //lectura digital de pin
  
 
  if (value == HIGH) {
      Serial.println("Detectado obstaculo");
  }
  if (value==HIGH) {
    digitalWrite(LedPin, HIGH); // Encendemos el LED
  } else {
    digitalWrite(LedPin, LOW); // Apagamos el LED
  }
  delay(1000);
}
