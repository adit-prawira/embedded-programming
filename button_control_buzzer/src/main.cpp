#include <Arduino.h>
#include <ArduinoSTL.h>
using namespace std;

int buzzer = 12, on_button = 9, off_button = 4;
bool is_active = false;


// put your setup code here, to run once:
void setup()
{
    pinMode(buzzer, OUTPUT);
    pinMode(on_button, INPUT_PULLUP);
    pinMode(off_button, INPUT_PULLUP);
}
void active_buzzer(){
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
}

// put your main code here, to run repeatedly:
void loop() {
    // on button will set buzzer flag as true when pressed
    if(digitalRead(on_button) == LOW){
        is_active = true;
    }

    // off button will do the opposite
    if(digitalRead(off_button) == LOW){
        is_active = false;
    }
    if(is_active){
        active_buzzer();
    }
}