#include <Arduino.h>
#include <SR04.h>


#define TRIG_PIN 4 
#define ECHO_PIN 5
#define ON_BUTTON_PIN 6
#define OFF_BUTTON_PIN 7
#define ALARM_PIN 8
#define SYSTEM_ON "System status: ON"
#define SYSTEM_OFF "System status: OFF"
#define ALERT_MESSAGE "Alert: DANGER"


long dist;
SR04 sensor = SR04(ECHO_PIN, TRIG_PIN);
int alarm = ALARM_PIN, button_on = ON_BUTTON_PIN, button_off = OFF_BUTTON_PIN;
bool alert = false, is_active = false;
String dist_str;

// put your setup code here, to run once:
void setup() {
  pinMode(alarm, OUTPUT);
  pinMode(button_on, INPUT_PULLUP);
  pinMode(button_off, INPUT_PULLUP);
  Serial.begin(9600);
  delay(100);
}

void active_alarm(int distance)
{
  int time_d = (2 * distance >= 30) ? (2 * distance) : 30;
  digitalWrite(alarm, HIGH);
  delay(time_d);
  digitalWrite(alarm, LOW);
  delay(time_d);
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
    if(dist <= 50 && is_active){
      alert = true;
    }else{
      alert = false;
    }

    if (alert){
      dist_str = "Distance: " + String(dist) + " cm";
      Serial.println(ALERT_MESSAGE);
      Serial.println(dist_str);
      active_alarm((int)dist);
    }
  }
}
