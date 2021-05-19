/*
Copyright (c) [2012-2020] Microchip Technology Inc.  

    All rights reserved.

    You are permitted to use the accompanying software and its derivatives 
    with Microchip products. See the Microchip license agreement accompanying 
    this software, if any, for additional info regarding your rights and 
    obligations.
    
    MICROCHIP SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT 
    WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT 
    LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT 
    AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP OR ITS
    LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT 
    LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE 
    THEORY FOR ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT 
    LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, 
    OR OTHER SIMILAR COSTS. 
    
    To the fullest extend allowed by law, Microchip and its licensors 
    liability will not exceed the amount of fees, if any, that you paid 
    directly to Microchip to use this software. 
    
    THIRD PARTY SOFTWARE:  Notwithstanding anything to the contrary, any 
    third party software accompanying this software is subject to the terms 
    and conditions of the third party's license agreement.  To the extent 
    required by third party licenses covering such third party software, 
    the terms of such license will apply in lieu of the terms provided in 
    this notice or applicable license.  To the extent the terms of such 
    third party licenses prohibit any of the restrictions described here, 
    such restrictions will not apply to such third party software.
*/
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
    //STEP 1 - The system is initialized
    SYSTEM_Initialize();

    //STEP 2 - The LED_PIN is set HIGH which turns off the LED
    LED_PIN_LAT = HIGH; 

    //STEP 3 - The "LED_PIN_ISR" function is called in the 
    //"Timer0_OverflowCallbackRegister()" function.  This allows for the 
    //"LED_PIN_ISR" function to be called whenever the timer overflows.
    Timer0_OverflowCallbackRegister(LED_PIN_ISR);
    
    //STEP 4 - turn on interrupts
    INTERRUPT_GlobalInterruptEnable(); 
    while(1){
                     
    }    
}