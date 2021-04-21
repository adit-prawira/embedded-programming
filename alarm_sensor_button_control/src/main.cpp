#include <Arduino.h>
#include <SR04.h>

#define TRIG_PIN 4 
#define ECHO_PIN 5
#define ON_BUTTON_PIN 6
#define OFF_BUTTON_PIN 7
#define ALARM_PIN 8
#define ALARM_LED 9
#define SYSTEM_ON "System status: ON"
#define SYSTEM_OFF "System status: OFF"
#define ALERT_MESSAGE "Alert: DANGER"
long dist;
SR04 sensor = SR04(ECHO_PIN, TRIG_PIN);
int alarm = ALARM_PIN, button_on = ON_BUTTON_PIN, button_off = OFF_BUTTON_PIN, led = ALARM_LED;
bool alert = false, is_active = false;

// put your setup code here, to run once:
void setup() {
  pinMode(alarm, OUTPUT);
  pinMode(button_on, INPUT_PULLUP);
  pinMode(button_off, INPUT_PULLUP);
  Serial.begin(9600);
  delay(100);
}

void active_alarm()
{
  digitalWrite(alarm, HIGH);
  digitalWrite(led, HIGH);
  delay(100);
  digitalWrite(alarm, LOW);
  digitalWrite(led, LOW);
  delay(100);
}

// put your main code here, to run repeatedly:
void loop() {
  if(digitalRead(button_on) == LOW && !is_active){
    is_active = true;
    Serial.println(SYSTEM_ON);
  }

  if(digitalRead(button_off) ==LOW && is_active){
    is_active = false;
    Serial.println(SYSTEM_OFF);
  }
  
  if(is_active){
    dist = sensor.Distance();
    // active alarm when ultrasonic sensor detect object in 50 cm range
    // alarm will be turned off otherwise
    if(dist < 50 && is_active){
      alert = true;
    }else{
      alert = false;
    }
    if (alert){
      Serial.println(ALERT_MESSAGE);
      active_alarm();
    }
  }
}
