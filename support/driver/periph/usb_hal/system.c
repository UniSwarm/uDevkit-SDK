#include <archi.h>
#include "system.h"
#include "usb.h"

void SYSTEM_Initialize( SYSTEM_STATE state )
{
    switch(state)
    {
        case SYSTEM_STATE_USB_START:

            // Start USB PLL

#ifdef ARCHI_dspic33ep
            ACLKCON3 = 0x24C1;
            ACLKDIV3 = 0x7;

            ACLKCON3bits.ENAPLL = 1;
            while(ACLKCON3bits.APLLCK != 1);
#endif

            break;

        case SYSTEM_STATE_USB_SUSPEND:
            //If developing a bus powered USB device that needs to be USB compliant,
            //insert code here to reduce the I/O pin and microcontroller power consumption,
            //so that the total current is <2.5mA from the USB host's VBUS supply.
            //If developing a self powered application (or a bus powered device where
            //official USB compliance isn't critical), nothing strictly needs
            //to be done during USB suspend.

            //USBSleepOnSuspend();
            break;

        case SYSTEM_STATE_USB_RESUME:
            //Here would be a good place to restore I/O pins and application states
            //back to their original values that may have been saved/changed at the 
            //start of the suspend event (ex: when the SYSTEM_Initialize(SYSTEM_STATE_USB_SUSPEND)
            //callback was called.
            
            //If you didn't change any I/O pin states prior to entry into suspend,
            //then nothing explicitly needs to be done here.  However, by the time
            //the firmware returns from this function, the full application should
            //be restored into effectively exactly the same state as the application
            //was in, prior to entering USB suspend.
            
            //Additionally, before returning from this function, make sure the microcontroller's
            //currently active clock settings are compatible with USB operation, including
            //taking into consideration all possible microcontroller features/effects
            //that can affect the oscillator settings (such as internal/external 
            //switchover (two speed start up), fail-safe clock monitor, PLL lock time,
            //external crystal/resonator startup time (if using a crystal/resonator),
            //etc.

            //Additionally, the official USB specifications dictate that USB devices
            //must become fully operational and ready for new host requests/normal 
            //USB communication after a 10ms "resume recovery interval" has elapsed.
            //In order to meet this timing requirement and avoid possible issues,
            //make sure that all necessary oscillator startup is complete and this
            //function has returned within less than this 10ms interval.

            break;

        default:
            break;
    }
}

#if defined(USB_INTERRUPT) && defined(ARCHI_pic32mm)
void __ISR(_USB_VECTOR, IPL4AUTO) USBInterrupt ()
{
    USBDeviceTasks();
}
#endif

#if defined(USB_INTERRUPT) && defined(ARCHI_dspic33ep)
void __attribute__((interrupt, auto_psv)) _USB1Interrupt()
{
    USBDeviceTasks();
}
#endif
