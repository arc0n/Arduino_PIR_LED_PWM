#include <SoftPWM.h>
#define FADE 1000   //fade in ms
#define ledPin9 9   //Led Pin +

int inPin8 = 8;    //input pin from IR Sensor
int irVal = 0;    //ir sensor value
int timer = 0;    //programmable countdown timer
int dur = 0;     //duration in seconds

void setup() {
  SoftPWMBegin();
  Serial.begin(9600);
  Serial.println("- - -");
  Serial.println("Digital 8 = OUT - inPin for IR Sensor");
  Serial.println("Digital 9 = LED Pin +");
  Serial.println("5V = PIR GCC");
  Serial.println("GND = - von allem");
  SoftPWMSet(ledPin9, 0);
  SoftPWMSetFadeTime(ledPin9, FADE, FADE);

  pinMode(inPin8, INPUT);    //Input for IR Sensor
}

void loop() {
  irVal = digitalRead(inPin8); //read the IR Sensor value and store it
  if (irVal > 0) {
    dur = 10;
    readIRSensor(dur);
    irVal = 0;
  }
}

int readIRSensor(int duration) {
  timer = duration;
  ledOn(timer);
  Serial.println("LED OFF");
  SoftPWMSetPercent(ledPin9, 0);
  delay(100);
}

int ledOn(int dur) {
  for(int i = 0; i <= dur; i++) {
    SoftPWMSetPercent(ledPin9, 100);
    delay(1000);
    if(digitalRead(inPin8)) {
      Serial.println("Motion detected, reset timer.");
      i = 0;
    }
    if(i == 5) {
      Serial.println("PIR reset. Detection online.");
      SoftPWMSetPercent(ledPin9, 10);
      delay(500);
      SoftPWMSetPercent(ledPin9, 100);
    }
  }
  
}

