// PedalManager.h
#ifndef PEDAL_MANAGER_H
#define PEDAL_MANAGER_H

#include <Arduino.h>

class PedalManager {
public:
    PedalManager(int accelPin, int brakePin, int clutchPin);
    void update();
    int getAccelerator();
    int getBrake();
    int getClutch();

private:
    int acceleratorPin;
    int brakePin;
    int clutchPin;
    int accelValue;
    int brakeValue;
    int clutchValue;
};

#endif