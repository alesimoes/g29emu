

#ifndef _G29WHEELEMU_H_
#define _G29WHEELEMU_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/power.h>
		#include <avr/interrupt.h>
		#include <string.h>

		#include "Descriptors.h"

		#include <LUFA/LUFA/Drivers/Board/Joystick.h>
		#include <LUFA/LUFA/Drivers/USB/USB.h>
		#include <LUFA/LUFA/Platform/Platform.h>

  /* Macros: */
    /** HID Class specific request to get the next HID report from the device. */
    #define REQ_GetReport               0x01

    /** HID Class specific request to send the next HID report to the device. */
    #define REQ_SetReport               0x09
    
    /** LED mask for the library LED driver, to indicate that the USB interface is not ready. */
    #define LEDMASK_USB_NOTREADY        LEDS_LED1

    /** LED mask for the library LED driver, to indicate that the USB interface is enumerating. */
    #define LEDMASK_USB_ENUMERATING     (LEDS_LED2 | LEDS_LED3)

    /** LED mask for the library LED driver, to indicate that the USB interface is ready. */
    #define LEDMASK_USB_READY           (LEDS_LED2 | LEDS_LED4)

    /** LED mask for the library LED driver, to indicate that an error has occurred in the USB interface. */
    #define LEDMASK_USB_ERROR           (LEDS_LED1 | LEDS_LED3)

	/* Function Prototypes: */
		#ifdef __cplusplus
		extern "C" {
		#endif
		void SetupHardware(void);
    void InitUSB(void);
    void HID_Task(void);

		void EVENT_USB_Device_Connect(void);
		void EVENT_USB_Device_Disconnect(void);
		void EVENT_USB_Device_ConfigurationChanged(void);
		void EVENT_USB_Device_ControlRequest(void);
    void EVENT_USB_Device_StartOfFrame(void);
    
    void ProcessLEDReport(uint8_t LEDReport);
    void SendNextReport(void);
    void ReceiveNextReport(void);
		
		#ifdef __cplusplus
		}
		#endif
#endif

