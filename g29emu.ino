

#include <Arduino.h>
#include "LUFAConfig.h"
#include <LUFA.h>
#include "G29WheelEmu.h"
#include <SPI.h>


void setup()
{
	SetupHardware(); // ask LUFA to setup the hardware
  InitUSB();
}

void loop()
{
 	HID_Task();
	USB_USBTask();  
}

