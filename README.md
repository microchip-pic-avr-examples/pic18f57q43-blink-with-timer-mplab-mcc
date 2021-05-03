<!-- Please do not change this logo with link -->
[![MCHP](images/microchip.png)](https://www.microchip.com)

# Blink with Timer

This example shows how to configure an LED to blink periodically using drivers in MPLAB Code Configurator (MCC). The example uses the Pin Manager to configure the pin and generate an API with which the pin is later interfaced. Also, the timer driver is used to implement periodic interrupt between each time the pin output is toggled.

## Related Documentation

- [MPLAB Code Configurator](https://www.microchip.com/en-us/development-tools-tools-and-software/embedded-software-center/mplab-code-configurator)
- [PIC18F57Q47 Data Sheet](https://ww1.microchip.com/downloads/en/DeviceDoc/PIC18F27-47-57Q43-Data-Sheet-DS40002147E.pdf)
- [PIC18F57Q47 Family Product Page](https://www.microchip.com/wwwproducts/en/PIC18F57Q43)

## Software Used

- [MPLAB® X IDE](http://www.microchip.com/mplab/mplab-x-ide) **5.45** or newer
- [MPLAB® XC8](http://www.microchip.com/mplab/compilers) **2.31** or a newer compiler 
- [MPLAB® Code Configurator (MCC)](https://www.microchip.com/mplab/mplab-code-configurator) **4.1.0** or newer 
- [MPLAB® Melody Library](https://www.microchip.com/en-us/development-tools-tools-and-software/embedded-software-center/mplab-code-configurator) **1.37.25** or newer
- [Microchip PIC18F-Q Series Device Support pack](https://packs.download.microchip.com/) **1.9.175** or newer Device Pack

## Hardware Used
- [Microchip PIC18F47Q57 Curiosity Nano Evaluation Kit](https://www.microchip.com/Developmenttools/ProductDetails/DM164150)

## Setup

<!-- Explain how to connect hardware and set up software. Depending on complexity, step-by-step instructions and/or tables and/or images can be used -->
<!--
Device Resources-> Drivers -> Timer-> TMR0:
include timer0 into code

Note: include a picture of what the Builder tab looks like

Within Timer 0 configuration window:
Clock prescaler 1:1024 (determines the upper and lower bounds of the 'Requested Period(s) line)
Timer Mode: 8-bit
Clock Source: FOSC/4
Requested Period: 0.5 (this gives a range of possible wait times)
Turn 'TMR Interrupt' on (circle on right, blue in switch)

In Interrupt Manager Tab:
Make sure that the 'Enable Isngle ISR Execution per entry' is on, everything else is off
TMR0 is included in the Interrupt Table and has the Enable box checked

Click on System-> Pins
In Pin grid view click on 'GPIO-output' for pin RF3
In Pins tab:
add a label to pin RF3, call it "LED_PIN" (in custon name column), make sure it does not have 'Start High, Week Pullup, or Open Drain' selected, also make sure that it has 'Analog, Slew Rate, and Input Level Control' selected.

Click on Generate

All of the necessary APIs should be created at this point except for one.

Above the main(void) line in the main.c code, add in the following function.
"void LED_PIN_ISR(void){ 
    LED_PIN_Toggle();
    }


----------------------------------------------------------------------------------------------



INTERNAL (working code):
START CoDe:
#include "mcc_generated_files/system/system.h"

/*
    Main application
*/
/*
 Creating an empty function for the Timer0 to call on when an interrupt occurs.
 */
void LED_PIN_ISR(void){ 
    LED_PIN_Toggle(); //Turns the pin called 'LED_PIN' on or off depending on
                      //the current state of the pin. 
                      //see pins.h for exact function code
}
int main(void)
{
    SYSTEM_Initialize();
    LED_PIN_LAT = HIGH; //Turns LED off before running rest of code
    while(1)
    {
        INTERRUPT_GlobalInterruptEnable(); //turn on interrupts
        //When the registers TMR0L/H overflow, the function 'LED_PIN_ISR' gets executed
        Timer0_OverflowCallbackRegister(LED_PIN_ISR); 
        INTERRUPT_GlobalInterruptDisable(); //turn off interrupts
    }    
}

END CODE

-----------------------------------------------------------------------------------------------

-->

## Operation

<!-- Explain how to operate the example. Depending on complexity, step-by-step instructions and/or tables and/or images can be used -->

## Summary

<!-- Summarize what the example has shown -->
