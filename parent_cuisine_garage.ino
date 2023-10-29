
//chambre parent//
#include <DHT.h>;
#define DHT11_PIN 2
#define DHTTYPE DHT11
#define ventilateurpin 3
DHT dht(DHT11_PIN, DHTTYPE);
float temp, hum;

//cuisine//
#define PIN_MQ2 A0
int buzzer = 7;
int value;

//garage//
#include <Servo.h>
#define trigPin 12
#define echoPin 11
Servo servo;
int sound = 250;


void setup() {
Serial.begin(9600);
  
//chambe parents//
dht.begin();
pinMode(ventilateurpin, OUTPUT);

//cuisine//
pinMode(buzzer, OUTPUT);
pinMode(PIN_MQ2, INPUT);

//garage//
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
servo.attach(9);


  
}

void loop() {
 //*********************************cuisine************************************************************** 
 value = analogRead(PIN_MQ2);


   if (value > 100) { 
      digitalWrite(buzzer, HIGH); 
      String Data = "C " + String(value)+  " " + "ON";
      Serial.println(Data);
     }
   else { 
      digitalWrite(buzzer, LOW);
      String Data = "C " + String(value)+  " " + "OFF";
      Serial.println(Data);
   }
   delay(1000);
   
//*********************************chambre parents**************************************************************
  byte temp = dht.readTemperature();
 byte  hum = dht.readHumidity();

  delay(1000);
  if (temp >= 27) {
    analogWrite(ventilateurpin, 255);
    String Data = "CP " + String(temp) + " " + String(hum) + " " + "ON";
     Serial.println(Data);
  }
  else {
    analogWrite(ventilateurpin, 0);
      String Data = "CP " + String(temp) + " " + String(hum) + " " + "OFF";
     Serial.println(Data);
  }
 delay(1000);
//*********************************garage**************************************************************
  long duration, distance;
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;
if (distance < 20) {
    servo.write(90);
    String Data = "G " +String(distance) +  " " + "ouvert";
    Serial.println(Data);
    delay(1500);
}
else {
    servo.write(0);
   String Data = "G " +String(distance) + " " + "fermé";
    Serial.println(Data);
}

delay(1000);
 
  }
