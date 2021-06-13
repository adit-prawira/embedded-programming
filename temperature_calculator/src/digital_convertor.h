#include <iostream>
#include <Arduino.h>
#include <ArduinoSTL.h>
#include <map>
using namespace std;

const int HEX_SIZE = 17;
String HEXADECIMAL[HEX_SIZE] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"};
// std::map<char, String[HEX_SIZE]> map;


class DigitalConvertor
{
private:
    long _decimal_val;
    String _unit;

    DigitalConvertor(String input_unit)
    {
        _decimal_val = 0;
        this->_unit = input_unit;
    }

    DigitalConvertor(long input_val, String input_unit)
    {
        this->_decimal_val = input_val; 
        this->_unit = input_unit;
    }

    String DecimalToBinary();
    String DecimalToHexadecimal();
    String DecimalToOctal();
};