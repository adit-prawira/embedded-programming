#include <Arduino.h>
#include "Servo.h"

#define SERVO_PIN 5
#define BUTTON_PIN 6

#define TIME_DELAY 500
#define MIN_ANGLE 0
#define MAX_ANGLE 180
#define STEP_ANGLE 30

Servo servo;

int button = BUTTON_PIN;
bool systemOn = false;
int angle = MIN_ANGLE;

// put your setup code here, to run once:
void setup() {
  pinMode(button, INPUT_PULLUP);
  servo.attach(SERVO_PIN);
  servo.write(0);
  Serial.begin(9600);
}

// put your main code here, to run repeatedly:
void loop() {
  if(systemOn){
    if(angle < MAX_ANGLE){
      angle += STEP_ANGLE;
    }else{
      angle = MIN_ANGLE;
    }
  }
  if(digitalRead(button) == LOW){
    if(!systemOn){
      systemOn = true;
      Serial.println("System ON");
    }
    else
    {
      systemOn = false;
      Serial.println("System OFF");
      angle = MIN_ANGLE;
    }
  }
  servo.write(angle);
  delay(TIME_DELAY);
}