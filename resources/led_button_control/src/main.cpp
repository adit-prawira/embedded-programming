#include <Arduino.h>
using namespace std;
int led = 5, button_a = 9, button_b = 8;

// put your setup code here, to run once:
void setup()
{
  pinMode(led, OUTPUT);
  
  // set button a as input and intially not pressed
  pinMode(button_a, INPUT_PULLUP);

  // set button b as input and intially not pressed
  pinMode(button_b, INPUT_PULLUP);
}

// put your main code here, to run repeatedly:
void loop() {
  // button a is on button
  if(digitalRead(button_a) == LOW){
    digitalWrite(led, HIGH);
  }

  // button b is off button
  if(digitalRead(button_b) == LOW){
    digitalWrite(led, LOW);
  }
  
}