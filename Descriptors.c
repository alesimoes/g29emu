/*
             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2013  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  USB Device Descriptors, for library use when in USB device mode. Descriptors are special
 *  computer-readable structures which the host requests upon device enumeration, to determine
 *  the device's capabilities and functions.
 */

#include "Descriptors.h"

const USB_Descriptor_HIDReport_Datatype_t PROGMEM Report[] =
{
      // Generic Desktop (Joystick)
    0x05, 0x01,                    // Usage Page (Generic Desktop)
    0x09, 0x04,                    // Usage (Joystick)
    0xA1, 0x01,                    // Collection (Application)

    // Axes (X, Y, Z for steering and pedals)
    0x05, 0x01,                    // Usage Page (Generic Desktop)
    0x09, 0x01,                    // Usage (Pointer)
    0xA1, 0x00,                    // Collection (Physical)
    0x09, 0x30,                    // Usage (X - Steering)
    0x09, 0x31,                    // Usage (Y - Future use)
    0x09, 0x32,                    // Usage (Z - Accelerometer)
    0x15, 0x00,                    // Logical Minimum (0)
    0x26, 0xFF, 0x03,              // Logical Maximum (1023)
    0x75, 0x10,                    // Report Size (16 bits)
    0x95, 0x03,                    // Report Count (3 - Axes)
    0x81, 0x02,                    // Input (Data, Variable, Absolute)
    0xC0,                          // End Collection

    // Buttons
    0x05, 0x09,                    // Usage Page (Button)
    0x19, 0x01,                    // Usage Minimum (Button 1)
    0x29, 0x14,                    // Usage Maximum (Button 20)
    0x15, 0x00,                    // Logical Minimum (0)
    0x25, 0x01,                    // Logical Maximum (1)
    0x75, 0x01,                    // Report Size (1 bit)
    0x95, 0x14,                    // Report Count (20)
    0x81, 0x02,                    // Input (Data, Variable, Absolute)
    0x75, 0x04,                    // Report Size (Padding)
    0x95, 0x01,                    // Report Count (Padding)
    0x81, 0x03,                    // Input (Constant)

    // Force Feedback Output Report
    0x05, 0x0F,                    // Usage Page (Physical Interface)
    0x09, 0x21,                    // Usage (Set Effect Report)
    0xA1, 0x02,                    // Collection (Logical)
    0x85, 0x01,                    // Report ID (1)
    0x09, 0x22,                    // Usage (Effect Block Index)
    0x15, 0x01,                    // Logical Minimum (1)
    0x25, 0x28,                    // Logical Maximum (40 effects)
    0x35, 0x01,                    // Physical Minimum (1)
    0x45, 0x28,                    // Physical Maximum (40)
    0x75, 0x08,                    // Report Size (8 bits)
    0x95, 0x01,                    // Report Count (1)
    0x91, 0x02,                    // Output (Data, Variable, Absolute)
    0xC0,                          // End Collection

    // End Application
    0xC0
};


/** Device descriptor structure. This descriptor, located in FLASH memory, describes the overall
 *  device characteristics, including the supported USB version, control endpoint size and the
 *  number of device configurations. The descriptor is read out by the USB host when the enumeration
 *  process begins.
 */
const USB_Descriptor_Device_t PROGMEM DeviceDescriptor =
{
  .Header                 = {.Size = sizeof(USB_Descriptor_Device_t), .Type = DTYPE_Device},
    
  .USBSpecification       = 0x0100,//1.00
  .Class                  = 0x00,
  .SubClass               = 0x00,
  .Protocol               = 0x00,
        
  .Endpoint0Size          = FIXED_CONTROL_ENDPOINT_SIZE,
    
  .VendorID               = 0x046D,
  .ProductID              = 0xC260,
  .ReleaseNumber          = 0x8900,
    
  .ManufacturerStrIndex   = 0x01,
  .ProductStrIndex        = 0x02,
  .SerialNumStrIndex      = NO_DESCRIPTOR,
    
  .NumberOfConfigurations = FIXED_NUM_CONFIGURATIONS
};;

/** Configuration descriptor structure. This descriptor, located in FLASH memory, describes the usage
 *  of the device in one of its supported configurations, including information about any device interfaces
 *  and endpoints. The descriptor is read out by the USB host during the enumeration process when selecting
 *  a configuration so that the host may correctly communicate with the USB device.
 */
const USB_Descriptor_Configuration_t PROGMEM ConfigurationDescriptor =
{
  .Config = 
    {
      .Header                 = {.Size = sizeof(USB_Descriptor_Configuration_Header_t), .Type = DTYPE_Configuration},

      .TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_t),
      .TotalInterfaces        = 1,
        
      .ConfigurationNumber    = 1,
      .ConfigurationStrIndex  = NO_DESCRIPTOR,
        
      .ConfigAttributes       = (USB_CONFIG_ATTR_RESERVED | USB_CONFIG_ATTR_SELFPOWERED),
      
      .MaxPowerConsumption    = USB_CONFIG_POWER_MA(200)
    },
    
  .Interface = 
    {
      .Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

      .InterfaceNumber        = 0x00,
      .AlternateSetting       = 0x00,
      
      .TotalEndpoints         = 2,
        
      .Class                  = 0x03,
      .SubClass               = 0x00,
      .Protocol               = 0x00,
        
      .InterfaceStrIndex      = NO_DESCRIPTOR
    },

  .HID =
    {  
      .Header                 = {.Size = sizeof(USB_Descriptor_HID_t), .Type = DTYPE_HID},
      
      .HIDSpec                = 0x0110,
      .CountryCode            = 0x00,
      .TotalReportDescriptors = 1,
      .HIDReportType          = DTYPE_Report,
      .HIDReportLength        = sizeof(Report)
    },

  .InEndpoint =
    {
      .Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

      .EndpointAddress        = IN_EPNUM,
      .Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
      .EndpointSize           = EPSIZE,
      .PollingIntervalMS      = 0x05
    },
    
  .OutEndpoint =
    {
      .Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

      .EndpointAddress        = OUT_EPNUM,
      .Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
      .EndpointSize           = EPSIZE,
      .PollingIntervalMS      = 0x05
    }
    
};

/** Language descriptor structure. This descriptor, located in FLASH memory, is returned when the host requests
 *  the string descriptor with index 0 (the first index). It is actually an array of 16-bit integers, which indicate
 *  via the language ID table available at USB.org what languages the device supports for its string descriptors.
 */
const USB_Descriptor_String_t PROGMEM LanguageString =
{
	.Header                 = {.Size = USB_STRING_LEN(1), .Type = DTYPE_String},

	.UnicodeString          = {LANGUAGE_ID_ENG}
};

/** Manufacturer descriptor string. This is a Unicode string containing the manufacturer's details in human readable
 *  form, and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
const USB_Descriptor_String_t PROGMEM ManufacturerString =
{
  .Header                 = {.Size = USB_STRING_LEN(8), .Type = DTYPE_String},
    
  .UnicodeString          = L"Logitech"
};

/** Product descriptor string. This is a Unicode string containing the product's details in human readable form,
 *  and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
const USB_Descriptor_String_t PROGMEM ProductString =
{
  .Header                 = {.Size = USB_STRING_LEN(30), .Type = DTYPE_String},
    
  .UnicodeString          = L"G29 Driving Force Racing Wheel"
};

/** This function is called by the library when in device mode, and must be overridden (see library "USB Descriptors"
 *  documentation) by the application code so that the address and size of a requested descriptor can be given
 *  to the USB library. When the device receives a Get Descriptor request on the control endpoint, this function
 *  is called so that the descriptor details can be passed back and the appropriate descriptor sent back to the
 *  USB host.
 */
uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                    const uint16_t wIndex,
                                    const void** const DescriptorAddress)
{
	const uint8_t  DescriptorType   = (wValue >> 8);
  const uint8_t  DescriptorNumber = (wValue & 0xFF);

  void*    Address = NULL;
  uint16_t Size    = NO_DESCRIPTOR;

  switch (DescriptorType)
  {
    case DTYPE_Device: 
      Address = (void*)&DeviceDescriptor;
      Size    = sizeof(USB_Descriptor_Device_t);
      break;
    case DTYPE_Configuration: 
      Address = (void*)&ConfigurationDescriptor;
      Size    = sizeof(USB_Descriptor_Configuration_t);
      break;
    case DTYPE_String: 
      switch (DescriptorNumber)
      {
        case 0x00: 
          Address = (void*)&LanguageString;
          Size    = pgm_read_byte(&LanguageString.Header.Size);
          break;
        case 0x01: 
          Address = (void*)&ManufacturerString;
          Size    = pgm_read_byte(&ManufacturerString.Header.Size);
          break;
        case 0x02: 
          Address = (void*)&ProductString;
          Size    = pgm_read_byte(&ProductString.Header.Size);
          break;
      }
      break;
    case DTYPE_HID:
      Address = (void*)&ConfigurationDescriptor.HID;
      Size    = sizeof(USB_Descriptor_HID_t);
      break;
    case DTYPE_Report:
      Address = (void*)&Report;
      Size    = sizeof(Report);
      break;
  }
  
  *DescriptorAddress = Address;
  return Size;
}
