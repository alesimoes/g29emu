// ButtonManager.cpp
#include "ButtonManager.h"

ButtonManager::ButtonManager(int *pins, int numPins) {
    buttonPins = pins;
    buttonCount = numPins;
    buttonStates = new bool[numPins];

    for (int i = 0; i < buttonCount; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP);
        buttonStates[i] = false;
    }
}

void ButtonManager::update() {
    for (int i = 0; i < buttonCount; i++) {
        buttonStates[i] = !digitalRead(buttonPins[i]); // Active LOW
    }
}

bool ButtonManager::isPressed(int buttonIndex) {
    if (buttonIndex < 0 || buttonIndex >= buttonCount) return false;
    return buttonStates[buttonIndex];
}