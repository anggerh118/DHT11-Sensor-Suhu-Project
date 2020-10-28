#include "DHT.h"

const int pinMerah = 25;
const int pinKuning = 26;
const int pinHijau = 23;
const int pinDHT = 4;
const int pinButton = 33;

#define DHTTYPE DHT11   // DHT 11

DHT dht(pinDHT, DHTTYPE);

int buttonState = 0;
boolean starting = false;

void setup() {
  delay(5000);
  Serial.begin(9600);
  Serial.println(F("DHT11 test!"));

  pinMode(pinButton, INPUT);
  pinMode(pinHijau, OUTPUT);
  pinMode(pinKuning, OUTPUT);
  pinMode(pinMerah, OUTPUT);
  
  dht.begin();
}

void loop() {
  delay(1000);
  buttonState = digitalRead(pinButton);

  Serial.println(starting);
  float t = dht.readTemperature();
  if (isnan(t)) {
    Serial.println(F("Gagal membaca suhu !"));
    return;
  }

  if(buttonState == HIGH){
    starting = !starting;
  }
  if(starting == 1){
    if(t<35){
      digitalWrite(pinHijau, HIGH);
      digitalWrite(pinKuning, LOW);
      digitalWrite(pinMerah, LOW);
    }
    else if(t>=35 && t<=50){
      digitalWrite(pinHijau, HIGH);
      digitalWrite(pinKuning, HIGH); 
      digitalWrite(pinMerah, LOW); 
    }
    else if(t>50){
      digitalWrite(pinHijau, HIGH);
      digitalWrite(pinKuning, HIGH);
      digitalWrite(pinMerah, HIGH);  
    }
    Serial.print(t);
    Serial.print(F("°C "));
  }
   else{
     digitalWrite(pinHijau, LOW);
     digitalWrite(pinKuning, LOW);
     digitalWrite(pinMerah, LOW);
   }
}
