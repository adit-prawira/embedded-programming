#include <Arduino.h>
#define RED 6
#define GREEN 5
#define BLUE 3
#define fading_delay 10

int red, green, blue;

void setup()
{
  // setup RGB outputs
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);  
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
}

// fade in and fade out helper method
void fade_in_out(int temp_c1, int target_c1, int temp_c2, int target_c2){
  for (int i = 0; i < 255; i++){
    temp_c1--;
    temp_c2++;
    analogWrite(target_c1, temp_c1);
    analogWrite(target_c2, temp_c2);
    delay(fading_delay);
  }
}

void loop() {  
  // transition from red -> green
  red = 255, green = 0, blue = 0;
  fade_in_out(red, RED, green, GREEN);

  // transition from green -> blue
  fade_in_out(green, GREEN, blue, BLUE);

  // transition from blue -> red
  fade_in_out(blue, BLUE, red, RED);
}