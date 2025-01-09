// ForceFeedbackManager.h
#ifndef FORCE_FEEDBACK_MANAGER_H
#define FORCE_FEEDBACK_MANAGER_H

#include <Arduino.h>

class ForceFeedbackManager {
public:
    ForceFeedbackManager(int pwmRPin, int pwmLPin, int enRPin, int enLPin);
    void initialize();
    void process();

private:
    int pwmRPin;
    int pwmLPin;
    int enRPin;
    int enLPin;

    void setForce(int intensity, bool clockwise);
};

#endif