#include <Arduino.h>
#include <LiquidCrystal.h>
#include <temperature.h>
#include <IRremote.h>
#include <ArduinoSTL.h>
#include <string>
// NOTE: the LCD used for this program is LCD1602 module
// Hence, it has 16 columns and 2 rows.
#define LCD_COLS = 16
#define LCD_ROWS = 2
#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4
#define UNIT_NUMS 3
#define FIRST_INDEX 0
#define NEXT_ARROW " >>"
#define BACK_ARROW "<< "

// Initialize pin number used by the lcd, and receiver
const int rs = 12,
          e = 11, db4 = 10, db5 = 9, db6 = 8, db7 = 7, receiver = 13;
int index = 0;

// Initialize temperature units
String units[UNIT_NUMS] = {"Fahrenheit", "Celcius", "Kelvin"};
String message = units[0];
String navigation, input_num = "";

bool inConversionMode = false, isCalculationMode = false;
// Initialize lcd instances
LiquidCrystal lcd(rs, e, db4, db5, db6, db7);

// Initialize IRremote
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results message_codes; 
void refreshScreen(){
  lcd.clear();
  lcd.print("TempCalc");
  inConversionMode = false;
  isCalculationMode = false;
  input_num = "";
}
void decideLcd(){
  if(isCalculationMode){
    if (message[0] == 'F')
    {
      Temperature t(input_num.toInt(), String(message[0]));
      lcd.setCursor(0, 1);
      lcd.print(String(t.FahrenheitToCelcius())+"C, "+ String(t.FahrenheitToKelvin())+"K");
      Serial.println("Fahrenheit conversion: " + String(t.FahrenheitToCelcius())+"C, "+ String(t.FahrenheitToKelvin())+"K");
    }
    else if (message[0] == 'C')
    {
      Temperature t(input_num.toInt(), String(message[0]));
      lcd.setCursor(0, 1);
      lcd.print(String(t.CelciusToFahrenheit())+"F, "+ String(t.CelciusToKelvin())+"K");
    }
    else
    {
      Temperature t(input_num.toInt(), String(message[0]));
      lcd.setCursor(0, 1);
      lcd.print(String(t.KelvinToCelcius())+"C, "+ String(t.KelvinToFahrenheit())+"F");
    }
  }else{
    lcd.setCursor(0, 1);
    lcd.print("Input: " + input_num);
  }
}
void translateIR(){
  switch(message_codes.value){
    case 0xFFA25D:
      message = "POWER";
      break;
    case 0xFFE21D:
      navigation = "RETURN";
      refreshScreen();
      break;
    case 0xFF22DD:
      navigation = "BACK";
      if(index > 0){
        index --;
        message = units[index];
        refreshScreen();
      }
      inConversionMode =false;
      break;
    case 0xFF02FD:
      navigation = "ENTER";
      if(!inConversionMode){
        lcd.clear();
        lcd.print("TempCalc: " + String(message[0]));
        inConversionMode = true;
      }else{
        isCalculationMode = true;
        lcd.clear();
        lcd.print("TempCalc: " + input_num +  String(message[0]));
      }
      break;
    case 0xFFC23D:
      navigation = "NEXT";
      if(index < UNIT_NUMS-1){
        index ++;
        message = units[index];
        refreshScreen();
      }
      inConversionMode =false;
      break;
    case 0xFFE01F:
      navigation = "DOWN";
      break;
    case 0xFF906F:
      navigation = "UP";
      break;
    case 0xFF6897:
      input_num += "0";
      break;
    case 0xFF30CF:
      input_num += "1";
      break;
    case 0xFF18E7:
      input_num += "2";
      break;
    case 0xFF7A85:
      input_num += "3";
      break;
    case 0xFF10EF:
      input_num += "4";
      break;
    case 0xFF38C7:
      input_num += "5";
      break;
    case 0xFF5AA5:
      input_num += "6";
      break;
    case 0xFF42BD:
      input_num += "7";
      break;
    case 0xFF4AB5:
      input_num += "8";
      break;
    case 0xFF52AD:
      input_num += "9";
      break;
    default: 
      Serial.println("Button is un-used");
  }
}

// put your setup code here, to run once:
void setup()
{
  String num = "30";
  lcd.begin(16, 2);
  lcd.print("TempCalc" + String(Temperature(num.toDouble(), "C").CelciusToFahrenheit()));
  Serial.begin(9600);
  irrecv.enableIRIn();
}

// put your main code here, to run repeatedly:
void loop() {
  if(!inConversionMode){
    lcd.setCursor(0, 1);
    if(index == FIRST_INDEX){
      lcd.print(message + NEXT_ARROW);
    }else if(index == (sizeof(units)/sizeof(units[0]))-1){
      lcd.print(BACK_ARROW + message);
    }else{
      lcd.print(BACK_ARROW + message + NEXT_ARROW);
    }
  }else{
    decideLcd();
  }

  if(irrecv.decode(&message_codes)){
    translateIR();
    irrecv.resume();
  }
}