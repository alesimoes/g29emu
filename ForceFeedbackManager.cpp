// ForceFeedbackManager.cpp
#include "ForceFeedbackManager.h"
#include "Descriptors.h"
#include <lufa/LUFA/Drivers/USB/USB.h>

ForceFeedbackManager::ForceFeedbackManager(int pwmR, int pwmL, int enR, int enL) {
    pwmRPin = pwmR;
    pwmLPin = pwmL;
    enRPin = enR;
    enLPin = enL;
}

void ForceFeedbackManager::initialize() {
    pinMode(pwmRPin, OUTPUT);
    pinMode(pwmLPin, OUTPUT);
    pinMode(enRPin, OUTPUT);
    pinMode(enLPin, OUTPUT);

    digitalWrite(enRPin, HIGH); // Ativa o lado direito
    digitalWrite(enLPin, HIGH); // Ativa o lado esquerdo

    analogWrite(pwmRPin, 0); // Inicializa sem força
    analogWrite(pwmLPin, 0);
}

void ForceFeedbackManager::process() {
    Endpoint_SelectEndpoint(OUT_EPNUM);
    if (Endpoint_IsOUTReceived()) {
        uint8_t reportID;
        Endpoint_Read_Stream_LE(&reportID, sizeof(reportID), NULL);

        if (reportID == 1) { // Identificador do Force Feedback
            uint8_t effectData[4];
            Endpoint_Read_Stream_LE(&effectData, sizeof(effectData), NULL);

            int intensity = effectData[0]; // Intensidade do efeito
            bool clockwise = effectData[1] & 0x01; // Direção: 0 = anti-horário, 1 = horário

            setForce(intensity, clockwise);
        }

        Endpoint_ClearOUT();
    }
}

void ForceFeedbackManager::setForce(int intensity, bool clockwise) {
    if (clockwise) {
        analogWrite(pwmRPin, intensity);
        analogWrite(pwmLPin, 0);
    } else {
        analogWrite(pwmRPin, 0);
        analogWrite(pwmLPin, intensity);
    }
}
