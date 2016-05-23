/********************************************************************
 FileName:     	usb_config.h
 Dependencies: 	usb.h
 Processor:     PIC16, PIC18, PIC24, or dsPIC USB Microcontrollers
 Hardware:      This demo is natively intended to be used on Microchip USB demo
                boards supported by the MCHPFSUSB stack.  See release notes for
                support matrix.  This demo can be modified for use on other 
                hardware platforms.
 Complier:      Microchip XC8 (for PIC16/PIC18), C18 (for PIC18), or XC16 (for PIC24/dsPIC)
 Company:       Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the "Company") for its PIC(R) Microcontroller is intended and
 supplied to you, the Company's customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************
 File Description:

 Change History:
  Rev   Date         Description
  2.8   8 Oct 2010   Added definitions for supporting new 
                     USB_ENABLE_STATUS_STAGE_TIMEOUTS feature.
                     Changed the CDC comm EP and data EP from 2,3
                     (respectively) to 1,2 respectively, so as to
                     save RAM.
 *******************************************************************/

/*********************************************************************
 * Descriptor specific type definitions are defined in: usbd.h
 ********************************************************************/

#ifndef USBCFG_H
#define USBCFG_H

/** DEFINITIONS ****************************************************/
#define USB_EP0_BUFF_SIZE		8	// Valid Options: 8, 16, 32, or 64 bytes.
								// Using larger options take more SRAM, but
								// does not provide much advantage in most types
								// of applications.  Exceptions to this, are applications
								// that use EP0 IN or OUT for sending large amounts of
								// application related data.
									
#define USB_MAX_NUM_INT     	2   //Set this number to match the maximum interface number used in the descriptors for this firmware project
#define USB_MAX_EP_NUMBER	    2   //Set this number to match the maximum endpoint number used in the descriptors for this firmware project

//Device descriptor - if these two definitions are not defined then
//  a const USB_DEVICE_DESCRIPTOR variable by the exact name of device_dsc
//  must exist.
#define USB_USER_DEVICE_DESCRIPTOR &device_dsc
#define USB_USER_DEVICE_DESCRIPTOR_INCLUDE extern const USB_DEVICE_DESCRIPTOR device_dsc

//Configuration descriptors - if these two definitions do not exist then
//  a const uint8_t *const variable named exactly USB_CD_Ptr[] must exist.
#define USB_USER_CONFIG_DESCRIPTOR USB_CD_Ptr
#define USB_USER_CONFIG_DESCRIPTOR_INCLUDE extern const uint8_t *const USB_CD_Ptr[]


//------------------------------------------------------------------------------
//Select an endpoint ping-pong bufferring mode.  Some microcontrollers only
//support certain modes.  For most applications, it is recommended to use either 
//the USB_PING_PONG__FULL_PING_PONG or USB_PING_PONG__EP0_OUT_ONLY options.  
//The other settings are supported on some devices, but they are not 
//recommended, as they offer inferior control transfer timing performance.  
//See inline code comments in usb_device.c for additional details.
//Enabling ping pong bufferring on an endpoint generally increases firmware
//overhead somewhat, but when both buffers are used simultaneously in the 
//firmware, can offer better sustained bandwidth, especially for OUT endpoints.
//------------------------------------------------------
//#define USB_PING_PONG_MODE USB_PING_PONG__NO_PING_PONG    //Not recommended
#define USB_PING_PONG_MODE USB_PING_PONG__FULL_PING_PONG    //A good all around setting
//#define USB_PING_PONG_MODE USB_PING_PONG__EP0_OUT_ONLY    //Another good setting
//#define USB_PING_PONG_MODE USB_PING_PONG__ALL_BUT_EP0	    //Not recommended
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//Select a USB stack operating mode.  In the USB_INTERRUPT mode, the USB stack
//main task handler gets called only when necessary as an interrupt handler.
//This can potentially minimize CPU utilization, but adds context saving
//and restoring overhead associated with interrupts, which can potentially 
//decrease performance.
//When the USB_POLLING mode is selected, the USB stack main task handler
//(ex: USBDeviceTasks()) must be called periodically by the application firmware
//at a minimum rate as described in the inline code comments in usb_device.c.
//------------------------------------------------------
//#define USB_POLLING
#define USB_INTERRUPT
//------------------------------------------------------------------------------

/* Parameter definitions are defined in usb_device.h */
#define USB_PULLUP_OPTION USB_PULLUP_ENABLE
//#define USB_PULLUP_OPTION USB_PULLUP_DISABLED

#define USB_TRANSCEIVER_OPTION USB_INTERNAL_TRANSCEIVER
//External Transceiver support is not available on all product families.  Please
//  refer to the product family datasheet for more information if this feature
//  is available on the target processor.
//#define USB_TRANSCEIVER_OPTION USB_EXTERNAL_TRANSCEIVER

#define USB_SPEED_OPTION USB_FULL_SPEED
//#define USB_SPEED_OPTION USB_LOW_SPEED //(this mode is only supported on some microcontrollers)

//------------------------------------------------------------------------------------------------------------------
//Option to enable auto-arming of the status stage of control transfers, if no
//"progress" has been made for the USB_STATUS_STAGE_TIMEOUT value.
//If progress is made (any successful transactions completing on EP0 IN or OUT)
//the timeout counter gets reset to the USB_STATUS_STAGE_TIMEOUT value.
//
//During normal control transfer processing, the USB stack or the application
//firmware will call USBCtrlEPAllowStatusStage() as soon as the firmware is finished
//processing the control transfer.  Therefore, the status stage completes as
//quickly as is physically possible.  The USB_ENABLE_STATUS_STAGE_TIMEOUTS
//feature, and the USB_STATUS_STAGE_TIMEOUT value are only relevant, when:
//1.  The application uses the USBDeferStatusStage() API function, but never calls
//      USBCtrlEPAllowStatusStage().  Or:
//2.  The application uses host to device (OUT) control transfers with data stage,
//      and some abnormal error occurs, where the host might try to abort the control
//      transfer, before it has sent all of the data it claimed it was going to send.
//
//If the application firmware never uses the USBDeferStatusStage() API function,
//and it never uses host to device control transfers with data stage, then
//it is not required to enable the USB_ENABLE_STATUS_STAGE_TIMEOUTS feature.

#define USB_ENABLE_STATUS_STAGE_TIMEOUTS    //Comment this out to disable this feature.

//Section 9.2.6 of the USB 2.0 specifications indicate that:
//1.  Control transfers with no data stage: Status stage must complete within
//      50ms of the start of the control transfer.
//2.  Control transfers with (IN) data stage: Status stage must complete within
//      50ms of sending the last IN data packet in fullfilment of the data stage.
//3.  Control transfers with (OUT) data stage: No specific status stage timing
//      requirement.  However, the total time of the entire control transfer (ex:
//      including the OUT data stage and IN status stage) must not exceed 5 seconds.
//
//Therefore, if the USB_ENABLE_STATUS_STAGE_TIMEOUTS feature is used, it is suggested
//to set the USB_STATUS_STAGE_TIMEOUT value to timeout in less than 50ms.  If the
//USB_ENABLE_STATUS_STAGE_TIMEOUTS feature is not enabled, then the USB_STATUS_STAGE_TIMEOUT
//parameter is not relevant.

#define USB_STATUS_STAGE_TIMEOUT     (uint8_t)45   //Approximate timeout in milliseconds, except when
                                                //USB_POLLING mode is used, and USBDeviceTasks() is called at < 1kHz
                                                //In this special case, the timeout becomes approximately:
//Timeout(in milliseconds) = ((1000 * (USB_STATUS_STAGE_TIMEOUT - 1)) / (USBDeviceTasks() polling frequency in Hz))
//------------------------------------------------------------------------------------------------------------------

#define USB_SUPPORT_DEVICE

#define USB_NUM_STRING_DESCRIPTORS 3  //Set this number to match the total number of string descriptors that are implemented in the usb_descriptors.c file

/*******************************************************************
 * Event disable options                                           
 *   Enable a definition to suppress a specific event.  By default 
 *   all events are sent.                                          
 *******************************************************************/
//#define USB_DISABLE_SUSPEND_HANDLER
//#define USB_DISABLE_WAKEUP_FROM_SUSPEND_HANDLER
//#define USB_DISABLE_SOF_HANDLER
//#define USB_DISABLE_TRANSFER_TERMINATED_HANDLER
//#define USB_DISABLE_ERROR_HANDLER 
//#define USB_DISABLE_NONSTANDARD_EP0_REQUEST_HANDLER 
//#define USB_DISABLE_SET_DESCRIPTOR_HANDLER 
//#define USB_DISABLE_SET_CONFIGURATION_HANDLER
//#define USB_DISABLE_TRANSFER_COMPLETE_HANDLER 

/** DEVICE CLASS USAGE *********************************************/
#define USB_USE_CDC

/** ENDPOINTS ALLOCATION *******************************************/
#define USB_MAX_EP_NUMBER	    2

/* CDC */
#define CDC_COMM_INTF_ID        0x0
#define CDC_COMM_EP              1
#define CDC_COMM_IN_EP_SIZE      10

#define CDC_DATA_INTF_ID        0x01
#define CDC_DATA_EP             2
#define CDC_DATA_OUT_EP_SIZE    64
#define CDC_DATA_IN_EP_SIZE     64

//#define USB_CDC_SUPPORT_ABSTRACT_CONTROL_MANAGEMENT_CAPABILITIES_D2 //Send_Break command
#define USB_CDC_SUPPORT_ABSTRACT_CONTROL_MANAGEMENT_CAPABILITIES_D1 //Set_Line_Coding, Set_Control_Line_State, Get_Line_Coding, and Serial_State commands
/** DEFINITIONS ****************************************************/

#endif //USBCFG_H
