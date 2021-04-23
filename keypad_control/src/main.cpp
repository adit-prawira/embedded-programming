#include <Arduino.h>
#include <Keypad.h>

#define ROWS 4
#define COLS 4

char hexaKeys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keys = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
// put your setup code here, to run once:
void setup()
{
  Serial.begin(9600);
}

//put your main code here, to run repeatedly:
void loop() {
  char key = keys.getKey();
  if(key){
    Serial.println(key);  
  }
}