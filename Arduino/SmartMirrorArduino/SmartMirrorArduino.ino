#include "DHT.h"
#define DHTPIN 52
#define DHTTYPE DHT11
#define REDPIN A3
#define GREENPIN A6
#define BLUEPIN A9
#define FADESPEED 5
DHT dht(DHTPIN, DHTTYPE);

float humidity;
float temperature;

const int touchMusic = 46;

int MusicState = 0;
int MusicTrenutni = 0;
int MusicProsli = 0;
unsigned long MusiclastDebounceTime = 0;

unsigned long debounceDelay = 10;
int crvena, zelena, plava;

int MicPIN = A0;
int sensorValue = 0;

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(touchMusic, INPUT);
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
}

void loop() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  Serial.println(temperature);
  Serial.println(humidity);
  
  MusicTrenutni = digitalRead(touchMusic);

  if (MusicTrenutni == HIGH && MusicProsli == LOW && millis() - MusiclastDebounceTime > debounceDelay) {
    if (MusicState == HIGH)
      MusicState = LOW;
    else
      MusicState = HIGH;

    MusiclastDebounceTime = millis();    
  }
  MusicProsli = MusicTrenutni;

  if (MusicState == HIGH){
    sensorValue = analogRead(MicPIN);
    if(sensorValue<31){
      analogWrite(REDPIN,LOW);
      analogWrite(GREENPIN,LOW);
      analogWrite(BLUEPIN,LOW);
    }

    if(sensorValue<100&&sensorValue>30){
      analogWrite(REDPIN,75);
      analogWrite(GREENPIN,0);
      analogWrite(BLUEPIN,130);
      delay(50); 
    }
  
    if(sensorValue>100&&sensorValue<201){
      analogWrite(REDPIN,139);
      analogWrite(GREENPIN,0);
      analogWrite(BLUEPIN,0);
      delay(50);
    }
  
    if(sensorValue>200&&sensorValue<301){
      analogWrite(REDPIN,165);
      analogWrite(GREENPIN,42);
      analogWrite(BLUEPIN,42);
      delay(50);
    }
    
    if(sensorValue>300&&sensorValue<401){
      analogWrite(REDPIN,199);
      analogWrite(GREENPIN,21);
      analogWrite(BLUEPIN,133);
      delay(50);
    }

    if(sensorValue>400&&sensorValue<501){
      analogWrite(REDPIN,255);
      analogWrite(GREENPIN,20);
      analogWrite(BLUEPIN,147);
      delay(50);
    }

    if(sensorValue>500&&sensorValue<601){
      analogWrite(REDPIN,106);
      analogWrite(GREENPIN,90);
      analogWrite(BLUEPIN,205);
      delay(50);
    }

    if(sensorValue>600&&sensorValue<701){
      analogWrite(REDPIN,0);
      analogWrite(GREENPIN,0);
      analogWrite(BLUEPIN,255);
      delay(50);
    }

    if(sensorValue>700&&sensorValue<801){
      analogWrite(REDPIN,0);
      analogWrite(GREENPIN,128);
      analogWrite(BLUEPIN,128);
      delay(50);
    }

    if(sensorValue>800&&sensorValue<901){
      analogWrite(REDPIN,0);
      analogWrite(GREENPIN,128);
      analogWrite(BLUEPIN,0);
      delay(50);
    }

    if(sensorValue>900&&sensorValue<1001){
      analogWrite(REDPIN,0);
      analogWrite(GREENPIN,255);
      analogWrite(BLUEPIN,0);
      delay(50);
    }

    if(sensorValue>1000){
      analogWrite(REDPIN,255);
      analogWrite(GREENPIN,255);
      analogWrite(BLUEPIN,0);
      delay(50);
    }
  }
  else {
    analogWrite(REDPIN,255);
    analogWrite(GREENPIN,255);
    analogWrite(BLUEPIN,0);
  }
}
