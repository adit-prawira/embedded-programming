#include "temperature.h"
#define KELVIN_CONSTANT 273.15

long Temperature::CelciusToFahrenheit(){
    return (_value * (9 / 5)) + 32;
}
long Temperature::CelciusToKelvin(){
    return _value + KELVIN_CONSTANT;
}

long Temperature::KelvinToCelcius(){
    return _value - KELVIN_CONSTANT;
}
long Temperature::KelvinToFahrenheit(){
    return ((_value - KELVIN_CONSTANT) * (9 / 5)) + 32;
}

long Temperature::FahrenheitToCelcius(){
    return (5*(_value - 32))/9;
}

long Temperature::FahrenheitToKelvin(){
    return FahrenheitToCelcius() + KELVIN_CONSTANT;
}
