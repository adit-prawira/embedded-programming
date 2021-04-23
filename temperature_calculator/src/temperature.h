#include <Arduino.h>

class Temperature{
    private:
        long _value;
        String _unit;

    public:
        Temperature(String input_unit){
            _value = 0;
            this->_unit = input_unit;
        };
        Temperature(long input_val, String input_unit){
            this->_value = input_val;
            this->_unit = input_unit;
        };
        
        long CelciusToFahrenheit();
        long CelciusToKelvin();
        long KelvinToFahrenheit();
        long KelvinToCelcius();
        long FahrenheitToCelcius();
        long FahrenheitToKelvin();
};