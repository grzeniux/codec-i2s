#include "BatteryMonitor.h"

BatteryMonitor::BatteryMonitor(int adcPin, float r1, float r2, float vref)
    : _adcPin(adcPin), _r1(r1), _r2(r2), _vref(vref) {
    analogReadResolution(12);
}

float BatteryMonitor::readVoltage() {
    constexpr int samples = 10;
    int sum = 0;
    for (int i = 0; i < samples; ++i) {
        sum += analogRead(_adcPin);
        delay(2); // krótki odstęp czasowy, by uniknąć zakłóceń
    }

    float avgRaw = static_cast<float>(sum) / samples;
    float voltageADC = (avgRaw / ADC_RESOLUTION) * _vref;

    voltageADC *= 1.15f; // korekta niedokładności ADC

    float realVoltage = voltageADC * (_r1 + _r2) / _r2;

    return realVoltage;
}
