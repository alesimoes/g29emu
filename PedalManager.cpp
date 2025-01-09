// PedalManager.cpp
#include "PedalManager.h"

PedalManager::PedalManager(int accelPin, int brakePin, int clutchPin) {
    acceleratorPin = accelPin;
    brakePin = brakePin;
    clutchPin = clutchPin;

    pinMode(acceleratorPin, INPUT);
    pinMode(brakePin, INPUT);
    pinMode(clutchPin, INPUT);
}

void PedalManager::update() {
    accelValue = analogRead(acceleratorPin);
    brakeValue = analogRead(brakePin);
    clutchValue = analogRead(clutchPin);
}

int PedalManager::getAccelerator() {
    return accelValue;
}

int PedalManager::getBrake() {
    return brakeValue;
}

int PedalManager::getClutch() {
    return clutchValue;
}