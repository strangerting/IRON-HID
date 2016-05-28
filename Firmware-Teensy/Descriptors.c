/*
            IRON-HID Firmware for At90USB1286 in Teensy2.0++       
                    Copyright (C) 2016 Seunghun Han 
         at National Security Research Institute of South Korea
*/

/*
Copyright (c) 2016 Seunghun Han at NSR of South Kora

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/


/*
             LUFA Library
     Copyright (C) Dean Camera, 2010.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2010  Dean Camera (dean [at] fourwalledcubicle [dot] com)
  Copyright 2010  Matthias Hullin (lufa [at] matthias [dot] hullin [dot] net)

  Permission to use, copy, modify, distribute, and sell this 
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in 
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting 
  documentation, and that the name of the author not be used in 
  advertising or publicity pertaining to distribution of the 
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
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

/* On some devices, there is a factory set internal serial number which can be automatically sent to the host as
 * the device's serial number when the Device Descriptor's .SerialNumStrIndex entry is set to USE_INTERNAL_SERIAL.
 * This allows the host to track a device across insertions on different ports, allowing them to retain allocated
 * resources like COM port numbers and drivers. On demos using this feature, give a warning on unsupported devices
 * so that the user can supply their own serial number descriptor instead or remove the USE_INTERNAL_SERIAL value
 * from the Device Descriptor (forcing the host to generate a serial number for each device from the VID, PID and
 * port location).
 */
#if (USE_INTERNAL_SERIAL == NO_DESCRIPTOR)
	#warning USE_INTERNAL_SERIAL is not available on this AVR - please manually construct a device serial descriptor.
#endif

// Attack Mode
extern volatile uint8_t g_bAttackMode;

/** 
 * 	HID class report descriptor. This is a special descriptor constructed with values from the
 *  USBIF HID class specification to describe the reports and capabilities of the HID device. This
 *  descriptor is parsed by the host and its contents used to determine what data (and in what encoding)
 *  the device will send, and what it may be sent back from the host. Refer to the HID specification for
 *  more details on HID report descriptors.
 */
const USB_Descriptor_HIDReport_Datatype_t PROGMEM KeyboardReport[] =
{
	0x05, 0x01,          /* Usage Page (Generic Desktop)                    */
	0x09, 0x06,          /* Usage (Keyboard)                                */
	0xa1, 0x01,          /* Collection (Application)                        */
	0x75, 0x01,          /*   Report Size (1)                               */
	0x95, 0x08,          /*   Report Count (8)                              */
	0x05, 0x07,          /*   Usage Page (Key Codes)                        */
	0x19, 0xe0,          /*   Usage Minimum (Keyboard LeftControl)          */
	0x29, 0xe7,          /*   Usage Maximum (Keyboard Right GUI)            */
	0x15, 0x00,          /*   Logical Minimum (0)                           */
	0x25, 0x01,          /*   Logical Maximum (1)                           */
	0x81, 0x02,          /*   Input (Data, Variable, Absolute)              */
	0x95, 0x01,          /*   Report Count (1)                              */
	0x75, 0x08,          /*   Report Size (8)                               */
	0x81, 0x03,          /*   Input (Const, Variable, Absolute)             */
	0x95, 0x05,          /*   Report Count (5)                              */
	0x75, 0x01,          /*   Report Size (1)                               */
	0x05, 0x08,          /*   Usage Page (LEDs)                             */
	0x19, 0x01,          /*   Usage Minimum (Num Lock)                      */
	0x29, 0x05,          /*   Usage Maximum (Kana)                          */
	0x91, 0x02,          /*   Output (Data, Variable, Absolute)             */
	0x95, 0x01,          /*   Report Count (1)                              */
	0x75, 0x03,          /*   Report Size (3)                               */
	0x91, 0x03,          /*   Output (Const, Variable, Absolute)            */
	0x95, 0x06,          /*   Report Count (6)                              */
	0x75, 0x08,          /*   Report Size (8)                               */
	0x15, 0x00,          /*   Logical Minimum (0)                           */
	0x25, 0x65,          /*   Logical Maximum (101)                         */
	0x05, 0x07,          /*   Usage Page (Keyboard)                         */
	0x19, 0x00,          /*   Usage Minimum (Reserved (no event indicated)) */
	0x29, 0x65,          /*   Usage Maximum (Keyboard Application)          */
	0x81, 0x00,          /*   Input (Data, Array, Absolute)                 */
	0xc0                 /* End Collection                                  */
};

const USB_Descriptor_HIDReport_Datatype_t PROGMEM VendorReport[] = {
    0x06, 0x00, 0xff,              // USAGE_PAGE (Vendor Defined Page 1)
    0x09, 0x01,                    // USAGE (Vendor Usage 1)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
    0x85, 0x01,                    //   REPORT_ID (1)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x95, 0x40,                    //   REPORT_COUNT (64)
    0x09, 0x00,                    //   USAGE (Undefined)
    0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)
    0x85, 0x02,                    //   REPORT_ID (2)
    0x75, 0x10,                    //   REPORT_SIZE (16)
    0x95, 0x80,                    //   REPORT_COUNT (128)
   	0x09, 0x00,                    //   USAGE (Undefined)
	0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)
	0xc0                           // END_COLLECTION
};

/** 
 *	Device descriptor structure. This descriptor, located in FLASH memory, describes the overall
 *  device characteristics, including the supported USB version, control endpoint size and the
 *  number of device configurations. The descriptor is read out by the USB host when the enumeration
 *  process begins.
 */
const USB_Descriptor_Device_t PROGMEM DeviceDescriptor =
{
	.Header                 = {.Size = sizeof(USB_Descriptor_Device_t), .Type = DTYPE_Device},
		
	.USBSpecification       = VERSION_BCD(01.10),
	.Class                  = 0x00,
	.SubClass               = 0x00,
	.Protocol               = 0x00,
				
	.Endpoint0Size          = FIXED_CONTROL_ENDPOINT_SIZE,

#if defined CHERRY_COMPACT
	.VendorID               = 0x046A,
	.ProductID              = 0x0011,
#elif defined MATIAS_TACTILE_PRO
	.VendorID               = 0x04D9,
	.ProductID              = 0x4250,
#elif defined MATIAS_LAPTOP_PRO				// Set as same as Tactile Pro
	.VendorID               = 0x04D9,
	.ProductID              = 0x4250,
#else
	.VendorID               = 0x045E,
	.ProductID              = 0xFFF8,
#endif
	.ReleaseNumber          = 0x0000,
		
	.ManufacturerStrIndex   = 0x01,
	.ProductStrIndex        = 0x02,
	.SerialNumStrIndex      = USE_INTERNAL_SERIAL,
		
	.NumberOfConfigurations = FIXED_NUM_CONFIGURATIONS
};

/** 
 *	Configuration descriptor structure. This descriptor, located in FLASH memory, describes the usage
 *  of the device in one of its supported configurations, including information about any device interfaces
 *  and endpoints. The descriptor is read out by the USB host during the enumeration process when selecting
 *  a configuration so that the host may correctly communicate with the USB device.
 */
const USB_Descriptor_Configuration_Normal_t PROGMEM ConfigurationDescriptorForNormal =
{
	.Config = 
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Configuration_Header_t), .Type = DTYPE_Configuration},

			.TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_Normal_t),
			.TotalInterfaces        = 2,
				
			.ConfigurationNumber    = 1,
			.ConfigurationStrIndex  = NO_DESCRIPTOR,
				
			.ConfigAttributes       = USB_CONFIG_ATTR_BUSPOWERED,
			
			.MaxPowerConsumption    = USB_CONFIG_POWER_MA(100)
		},

	.HID_KeyboardInterface = 
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

			.InterfaceNumber        = KEYBOARD_IFNUM,
			.AlternateSetting       = 0,
			
			.TotalEndpoints         = 1,
				
			.Class                  = 0x03,
			.SubClass               = 0x01,
			.Protocol               = 0x01,
				
			.InterfaceStrIndex      = NO_DESCRIPTOR
		},

	.HID_KeyboardHID = 
		{  
			.Header                 = {.Size = sizeof(USB_HID_Descriptor_t), .Type = DTYPE_HID},
			
			.HIDSpec                = VERSION_BCD(01.11),
			.CountryCode            = 0x00,
			.TotalReportDescriptors = 1,
			.HIDReportType          = DTYPE_Report,
			.HIDReportLength        = sizeof(KeyboardReport)
		},
		
	.HID_ReportINEndpoint = 
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

			.EndpointAddress        = (ENDPOINT_DESCRIPTOR_DIR_IN | KEYBOARD_EPNUM),
			.Attributes             = EP_TYPE_INTERRUPT,
			.EndpointSize           = KEYBOARD_EPSIZE,
			.PollingIntervalMS      = 0x0A
		},

	// For Communication
	.HID_UserInterface = 
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

			.InterfaceNumber        = USER_IFNUM,
			.AlternateSetting       = 0,
			
			.TotalEndpoints         = 1,
				
			.Class                  = 0x03,
			.SubClass               = 0x01,
			.Protocol               = 0x01,
				
			.InterfaceStrIndex      = NO_DESCRIPTOR
		},

	.HID_UserHID = 
		{  
			.Header                 = {.Size = sizeof(USB_HID_Descriptor_t), .Type = DTYPE_HID},
			
			.HIDSpec                = VERSION_BCD(01.11),
			.CountryCode            = 0x00,
			.TotalReportDescriptors = 1,
			.HIDReportType          = DTYPE_Report,
			.HIDReportLength        = sizeof(VendorReport)
		},
		
	.HID_UserReportINEndpoint = 
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

			.EndpointAddress        = (ENDPOINT_DESCRIPTOR_DIR_IN | USER_EPNUM),
			.Attributes             = EP_TYPE_INTERRUPT,
			.EndpointSize           = USER_EPSIZE,
			.PollingIntervalMS      = 0x0A
		},
};

const USB_Descriptor_Configuration_Attack_t PROGMEM ConfigurationDescriptorForAttack =
{
	.Config = 
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Configuration_Header_t), .Type = DTYPE_Configuration},

			.TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_Attack_t),
			.TotalInterfaces        = 3,
				
			.ConfigurationNumber    = 1,
			.ConfigurationStrIndex  = NO_DESCRIPTOR,
				
			.ConfigAttributes       = USB_CONFIG_ATTR_BUSPOWERED,
			
			.MaxPowerConsumption    = USB_CONFIG_POWER_MA(100)
		},
		
	.HID_KeyboardInterface = 
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

			.InterfaceNumber        = KEYBOARD_IFNUM,
			.AlternateSetting       = 0,
			
			.TotalEndpoints         = 1,
				
			.Class                  = 0x03,
			.SubClass               = 0x01,
			.Protocol               = 0x01,
				
			.InterfaceStrIndex      = NO_DESCRIPTOR
		},

	.HID_KeyboardHID = 
		{  
			.Header                 = {.Size = sizeof(USB_HID_Descriptor_t), .Type = DTYPE_HID},
			
			.HIDSpec                = VERSION_BCD(01.11),
			.CountryCode            = 0x00,
			.TotalReportDescriptors = 1,
			.HIDReportType          = DTYPE_Report,
			.HIDReportLength        = sizeof(KeyboardReport)
		},
		
	.HID_ReportINEndpoint = 
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

			.EndpointAddress        = (ENDPOINT_DESCRIPTOR_DIR_IN | KEYBOARD_EPNUM),
			.Attributes             = EP_TYPE_INTERRUPT,
			.EndpointSize           = KEYBOARD_EPSIZE,
			.PollingIntervalMS      = 0x0A
		},

	// For Communication
	.HID_UserInterface = 
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

			.InterfaceNumber        = USER_IFNUM,
			.AlternateSetting       = 0,
			
			.TotalEndpoints         = 1,
				
			.Class                  = 0x03,
			.SubClass               = 0x01,
			.Protocol               = 0x01,
				
			.InterfaceStrIndex      = NO_DESCRIPTOR
		},

	.HID_UserHID = 
		{  
			.Header                 = {.Size = sizeof(USB_HID_Descriptor_t), .Type = DTYPE_HID},
			
			.HIDSpec                = VERSION_BCD(01.11),
			.CountryCode            = 0x00,
			.TotalReportDescriptors = 1,
			.HIDReportType          = DTYPE_Report,
			.HIDReportLength        = sizeof(VendorReport)
		},
		
	.HID_UserReportINEndpoint = 
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

			.EndpointAddress        = (ENDPOINT_DESCRIPTOR_DIR_IN | USER_EPNUM),
			.Attributes             = EP_TYPE_INTERRUPT,
			.EndpointSize           = USER_EPSIZE,
			.PollingIntervalMS      = 0x0A
		},

	.MS_Interface = 
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

			.InterfaceNumber        = MASS_STORAGE_IFNUM,
			.AlternateSetting       = 0,
			
			.TotalEndpoints         = 2,
				
			.Class                  = 0x08,
			.SubClass               = 0x06,
			.Protocol               = 0x50,
				
			.InterfaceStrIndex      = NO_DESCRIPTOR
		},

	.MS_DataInEndpoint = 
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

			.EndpointAddress        = (ENDPOINT_DESCRIPTOR_DIR_IN | MASS_STORAGE_IN_EPNUM),
			.Attributes             = EP_TYPE_BULK,
			.EndpointSize           = MASS_STORAGE_IO_EPSIZE,
			.PollingIntervalMS      = 0x00
		},

	.MS_DataOutEndpoint = 
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

			.EndpointAddress        = (ENDPOINT_DESCRIPTOR_DIR_OUT | MASS_STORAGE_OUT_EPNUM),
			.Attributes             = EP_TYPE_BULK,
			.EndpointSize           = MASS_STORAGE_IO_EPSIZE,
			.PollingIntervalMS      = 0x00
		}
};



/** 
 *	Language descriptor structure. This descriptor, located in FLASH memory, is returned when the host requests
 *  the string descriptor with index 0 (the first index). It is actually an array of 16-bit integers, which indicate
 *  via the language ID table available at USB.org what languages the device supports for its string descriptors.
 */
const USB_Descriptor_String_t PROGMEM LanguageString =
{
	.Header                 = {.Size = USB_STRING_LEN(1), .Type = DTYPE_String},
		
	.UnicodeString          = {LANGUAGE_ID_ENG}
};

/** 
 *	Manufacturer descriptor string. This is a Unicode string containing the manufacturer's details in human readable
 *  form, and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
const USB_Descriptor_String_t PROGMEM ManufacturerString =
{
		
	//.UnicodeString          = L"Dean Camera"
#if defined CHERRY_COMPACT
	.Header                 = {.Size = USB_STRING_LEN(6), .Type = DTYPE_String},
	.UnicodeString          = L"Cherry"
#elif defined MATIAS_TACTILE_PRO
	.Header                 = {.Size = USB_STRING_LEN(6), .Type = DTYPE_String},
	.UnicodeString          = L"Matias"
#elif defined MATIAS_LAPTOP_PRO
	.Header                 = {.Size = USB_STRING_LEN(6), .Type = DTYPE_String},
	.UnicodeString          = L"Matias"
#else
	.Header                 = {.Size = USB_STRING_LEN(9), .Type = DTYPE_String},
	.UnicodeString          = L"Microsoft"
#endif
};

/** 
 *	Product descriptor string. This is a Unicode string containing the product's details in human readable form,
 *  and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
const USB_Descriptor_String_t PROGMEM ProductString =
{
		
	//.UnicodeString          = L"LUFA Mass Storage and Keyboard Demo"
#if defined CHERRY_COMPACT
	.Header                 = {.Size = USB_STRING_LEN(15), .Type = DTYPE_String},
	.UnicodeString          = L"Cherry Keyboard"
#elif defined MATIAS_TACTILE_PRO
	.Header                 = {.Size = USB_STRING_LEN(27), .Type = DTYPE_String},
	.UnicodeString          = L"Matias Tactile Pro Keyboard"
#elif defined MATIAS_LAPTOP_PRO
	.Header                 = {.Size = USB_STRING_LEN(29), .Type = DTYPE_String},
	.UnicodeString          = L"Matias Notebook Pro Keyboard"
#else
	.Header                 = {.Size = USB_STRING_LEN(26), .Type = DTYPE_String},
	.UnicodeString          = L"Microsoft Generic Keyboard"
#endif
};

/** 
 *	This function is called by the library when in device mode, and must be overridden (see library "USB Descriptors"
 *  documentation) by the application code so that the address and size of a requested descriptor can be given
 *  to the USB library. When the device receives a Get Descriptor request on the control endpoint, this function
 *  is called so that the descriptor details can be passed back and the appropriate descriptor sent back to the
 *  USB host.
 */
uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                    const uint8_t wIndex,
                                    void** const DescriptorAddress)
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
			if (g_bAttackMode == 0)
			{
				Address = (void*)&ConfigurationDescriptorForNormal;
				Size    = sizeof(USB_Descriptor_Configuration_Normal_t);
			}
			else
			{
				Address = (void*)&ConfigurationDescriptorForAttack;
				Size    = sizeof(USB_Descriptor_Configuration_Attack_t);
			}
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
			if (g_bAttackMode == 0)
			{
				Address = (void*)&ConfigurationDescriptorForNormal.HID_KeyboardHID;
			}
			else
			{
				Address = (void*)&ConfigurationDescriptorForAttack.HID_KeyboardHID;
			}
			Size    = sizeof(USB_HID_Descriptor_t);
			break;

		case DTYPE_Report:
			if (wIndex == USER_IFNUM)
			{
				Address = (void*)&VendorReport;
				Size    = sizeof(VendorReport);
			}
			else
			{
				Address = (void*)&KeyboardReport;
				Size    = sizeof(KeyboardReport);
			}
			break;
	}
	
	*DescriptorAddress = Address;
	return Size;
}
