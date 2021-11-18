#include "DHT.h"
#define DHTPIN 52
#define DHTTYPE DHT11
#define REDPIN 3
#define GREENPIN 6
#define BLUEPIN 9
#define FADESPEED 5
DHT dht(DHTPIN, DHTTYPE);

float humidity;
float temperature;

const int touchRGB = 48;
const int touchMusic = 46;
const int touchRGBPulse = 44; 

int RGBState = 0;
int RGBTrenutni = 0;
int RGBProsli = 0;
unsigned long RGBlastDebounceTime = 0;

int MusicState = 0;
int MusicTrenutni = 0;
int MusicProsli = 0;
unsigned long MusiclastDebounceTime = 0;

int PulseState = 0;
int PulseTrenutni = 0;
int PulseProsli = 0;
unsigned long PulselastDebounceTime = 0;

unsigned long debounceDelay = 10;
int crvena, zelena, plava;

int MicPIN = A0;
int sensorValue = 0;

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(touchRGB, INPUT);
  pinMode(touchMusic, INPUT);
  pinMode(touchRGBPulse, INPUT);
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
}

void loop() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  Serial.println(temperature);
  Serial.println(humidity);

  RGBTrenutni = digitalRead(touchRGB);
  MusicTrenutni = digitalRead(touchMusic);
  PulseTrenutni = digitalRead(touchRGBPulse);

  if (RGBTrenutni == HIGH && RGBProsli == LOW && millis() - RGBlastDebounceTime > debounceDelay) {
    if (RGBState == HIGH)
      RGBState = LOW;
    else
      RGBState = HIGH;

    RGBlastDebounceTime = millis();    
  }
  RGBProsli = RGBTrenutni;

  if (MusicTrenutni == HIGH && MusicProsli == LOW && millis() - MusiclastDebounceTime > debounceDelay) {
    if (MusicState == HIGH)
      MusicState = LOW;
    else
      MusicState = HIGH;

    MusiclastDebounceTime = millis();    
  }
  MusicProsli = MusicTrenutni;

  if (PulseTrenutni == HIGH && PulseProsli == LOW && millis() - PulselastDebounceTime > debounceDelay) {
    if (PulseState == HIGH)
      PulseState = LOW;
    else
      PulseState = HIGH;

    PulselastDebounceTime = millis();    
  }
  PulseProsli = PulseTrenutni;

  if (PulseState != HIGH && RGBState == HIGH && MusicState != HIGH)
    if(temperature<11){
      digitalWrite(REDPIN,135);
      digitalWrite(GREENPIN,206);
      digitalWrite(BLUEPIN,250);  
    }
    
    if(temperature<21&&temperature>10){
      digitalWrite(REDPIN,154);
      digitalWrite(GREENPIN,205);
      digitalWrite(BLUEPIN,50);
    }
    
    if(temperature>20&&temperature<31){
      digitalWrite(REDPIN,255);
      digitalWrite(GREENPIN,165);
      digitalWrite(BLUEPIN,0);
    }
    
    if(temperature>30){
      digitalWrite(REDPIN,255);
      digitalWrite(GREENPIN,0);
      digitalWrite(BLUEPIN,0);
    }
  else{
    digitalWrite(REDPIN,0);
    digitalWrite(GREENPIN,0);
    digitalWrite(BLUEPIN,0);
  }
  
  if (PulseState != HIGH && RGBState != HIGH && MusicState == HIGH){
    sensorValue = analogRead(MicPIN);
  
    if(sensorValue<31){
      digitalWrite(REDPIN,LOW);
      digitalWrite(GREENPIN,LOW);
      digitalWrite(BLUEPIN,LOW);
    }

    if(sensorValue<100&&sensorValue>30){
      digitalWrite(REDPIN,75);
      digitalWrite(GREENPIN,0);
      digitalWrite(BLUEPIN,130);
      delay(50); 
    }
  
    if(sensorValue>100&&sensorValue<201){
      digitalWrite(REDPIN,139);
      digitalWrite(GREENPIN,0);
      digitalWrite(BLUEPIN,0);
      delay(50);
    }
  
    if(sensorValue>200&&sensorValue<301){
      digitalWrite(REDPIN,165);
      digitalWrite(GREENPIN,42);
      digitalWrite(BLUEPIN,42);
      delay(50);
    }
    
    if(sensorValue>300&&sensorValue<401){
      digitalWrite(REDPIN,199);
      digitalWrite(GREENPIN,21);
      digitalWrite(BLUEPIN,133);
      delay(50);
    }

    if(sensorValue>400&&sensorValue<501){
      digitalWrite(REDPIN,255);
      digitalWrite(GREENPIN,20);
      digitalWrite(BLUEPIN,147);
      delay(50);
    }

    if(sensorValue>500&&sensorValue<601){
      digitalWrite(REDPIN,106);
      digitalWrite(GREENPIN,90);
      digitalWrite(BLUEPIN,205);
      delay(50);
    }

    if(sensorValue>600&&sensorValue<701){
      digitalWrite(REDPIN,0);
      digitalWrite(GREENPIN,0);
      digitalWrite(BLUEPIN,255);
      delay(50);
    }

    if(sensorValue>700&&sensorValue<801){
      digitalWrite(REDPIN,0);
      digitalWrite(GREENPIN,128);
      digitalWrite(BLUEPIN,128);
      delay(50);
    }

    if(sensorValue>800&&sensorValue<901){
      digitalWrite(REDPIN,0);
      digitalWrite(GREENPIN,128);
      digitalWrite(BLUEPIN,0);
      delay(50);
    }

    if(sensorValue>900&&sensorValue<1001){
      digitalWrite(REDPIN,0);
      digitalWrite(GREENPIN,255);
      digitalWrite(BLUEPIN,0);
      delay(50);
    }

    if(sensorValue>1000){
      digitalWrite(REDPIN,255);
      digitalWrite(GREENPIN,255);
      digitalWrite(BLUEPIN,0);
      delay(50);
    }
  }
  else {
    digitalWrite(REDPIN,255);
    digitalWrite(GREENPIN,255);
    digitalWrite(BLUEPIN,0);
  }
   
  if (PulseState == HIGH && RGBState != HIGH && MusicState != HIGH){
    
    for (crvena = 0; crvena < 256; crvena++) { 
      analogWrite(REDPIN, crvena);
      delay(FADESPEED);
    } 
  
    for (plava = 255; plava > 0; plava--) { 
      analogWrite(BLUEPIN, plava);
      delay(FADESPEED);
    } 
  
    for (zelena = 0; zelena < 256; zelena++) { 
      analogWrite(GREENPIN, zelena);
      delay(FADESPEED);
    } 
  
    for (crvena = 255; crvena > 0; crvena--) { 
      analogWrite(REDPIN, crvena);
      delay(FADESPEED);
    } 
  
    for (plava = 0; plava < 256; plava++) { 
      analogWrite(BLUEPIN, plava);
      delay(FADESPEED);
    } 

    for (zelena= 255; zelena > 0; zelena--) { 
      analogWrite(GREENPIN, zelena);
      delay(FADESPEED);
    }
  }
  else{
    digitalWrite(REDPIN,0);
    digitalWrite(GREENPIN,0);
    digitalWrite(BLUEPIN,0);
  }    
}
