#include "digital_convertor.h"
#include <Arduino.h>
#include <ArduinoSTL.h>

String DigitalConvertor::DecimalToBinary(){
    vector<int> nums;
    uint32_t number = int(_decimal_val);
    for (int i = 0; number > 0; i++){
        nums[i] = number % 2;
        number = number/2;
    }
};