// Atualizações no g29emu.ino

#include <Arduino.h>
#include "LUFAConfig.h"
#include <LUFA.h>
#include "G29WheelEmu.h"
#include <SPI.h>
#include "ButtonManager.h"
#include "PedalManager.h"
#include "ForceFeedbackManager.h"

// Define os pinos para os botões disponíveis no Arduino Leonardo
int buttonPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}; // 12 botões
ButtonManager buttonManager(buttonPins, sizeof(buttonPins) / sizeof(buttonPins[0]));

PedalManager pedalManager(A0, A1, A2); // Pinos analógicos para pedais (Acelerador, Freio, Embreagem)

// Define pinos para LEDs de depuração
int ledPins[] = {22, 23, 24, 25}; // LEDs para indicar botões pressionados (apenas 4 para visualização básica)

// Instância para o gerenciamento de Force Feedback
ForceFeedbackManager forceFeedbackManager(7, 8, 9, 10); // Pinos PWM_R, PWM_L, EN_R, EN_L

void setup()
{
    SetupHardware(); // Configura o hardware usando LUFA
    InitUSB();

    // Inicializa os componentes
    buttonManager.update();
    pedalManager.update();

    // Configura os LEDs como saída
    for (int i = 0; i < 4; i++) {
        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], LOW); // Apaga os LEDs inicialmente
    }

    // Inicializa o Force Feedback Manager
    forceFeedbackManager.initialize();
}

void loop()
{
    // Atualiza os estados dos botões e pedais
    buttonManager.update();
    pedalManager.update();

    // Atualiza LEDs com base nos primeiros 4 botões pressionados (para visualização básica)
    for (int i = 0; i < 4; i++) {
        if (buttonManager.isPressed(i)) {
            digitalWrite(ledPins[i], HIGH); // Liga LED correspondente
        } else {
            digitalWrite(ledPins[i], LOW); // Apaga LED correspondente
        }
    }

    // Processa saídas de Force Feedback
    forceFeedbackManager.process();

    // Chama as tarefas HID e USB existentes
    HID_Task();
    USB_USBTask();
}
