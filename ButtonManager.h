// ButtonManager.h
#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

#include <Arduino.h>

class ButtonManager {
public:
    ButtonManager(int *pins, int numPins);
    void update();
    bool isPressed(int buttonIndex);

private:
    int *buttonPins;
    int buttonCount;
    bool *buttonStates;
};

#endif