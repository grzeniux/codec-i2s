#pragma once

#include <Arduino.h>

class BatteryMonitor {
public:
    BatteryMonitor(int adcPin, float r1, float r2, float vref = 3.3);
    float readVoltage();

private:
    int _adcPin;
    float _r1, _r2, _vref;
    static constexpr float ADC_RESOLUTION = 4095.0;
};
