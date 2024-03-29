<!-- Please do not change this logo with link -->
[![MCHP](images/microchip.png)](https://www.microchip.com)

# Blink with Timer

This example shows how to configure an LED to blink periodically using a timer.  The drivers for the timer are generated using the MPLAB Code Configurator (MCC).

## Related Documentation

- [MPLAB Code Configurator](https://www.microchip.com/en-us/development-tools-tools-and-software/embedded-software-center/mplab-code-configurator)
- [PIC18F57Q43 Data Sheet](https://ww1.microchip.com/downloads/en/DeviceDoc/PIC18F27-47-57Q43-Data-Sheet-DS40002147E.pdf)
- [PIC18F57Q43 Family Product Page](https://www.microchip.com/wwwproducts/en/PIC18F57Q43)

## Software Used

- [MPLAB® X IDE](http://www.microchip.com/mplab/mplab-x-ide) **5.45** or newer
- [MPLAB® Xpress IDE](https://www.microchip.com/en-us/development-tools-tools-and-software/mplab-xpress) (alternative to MPLAB® X IDE)
- [MPLAB® XC8](http://www.microchip.com/mplab/compilers) **2.31** or a newer compiler 
- [MPLAB® Code Configurator (MCC)](https://www.microchip.com/mplab/mplab-code-configurator) **4.1.0** or newer 
- [MPLAB® Melody Library](https://www.microchip.com/en-us/development-tools-tools-and-software/embedded-software-center/mplab-code-configurator) **1.37.25** or newer
- [Microchip PIC18F-Q Series Device Support pack](https://packs.download.microchip.com/) **1.9.175** or newer Device Pack

## Hardware Used
- [Microchip PIC18F57Q43 Curiosity Nano Evaluation Kit](https://www.microchip.com/Developmenttools/ProductDetails/DM164150)

## Setup
MCC with Melody library was used to implement this example as shown in the following sections.

### Timer Driver
The Timer Driver is added to the project by locating it in the Device Resources pane on the left side in MCC. Within the Drivers menu (expand if needed, red box in image below)timer menu (expand if needed, green box in image below), click on the green plus next to where it says TMR0 (blue box in image below)

*Device Resources*

![MCC - Adding Timer Driver](images/MCC_add_timer_driver.PNG)


When the Timer Driver is added, it is shown in the Project Resources and in the Builder view as seen below.  

*Project Resources - TMR0*

![MCC - Project Resources with Timer](images/MCC_project_resources_tmr_added.PNG)

*Builder*

![MCC - Builder with Timer](images/MCC_builder_tmr_added.PNG)

If you click the '+' button at the top of the System Firmware box, it will expand to show what is in the above image.  From here, clicking the 'Pins' box will open the Pins Grid View.  To utilize that view, see the "Pin Configuration" section below.

### Timer Configuration
The Timer needs to be configured properly in order to generate the correct driver.  There are a few possibilities of what you will see on your screen.  Feel free to skip ahead to the image that matches what you see on your screen.

There should be a tab on the right side that says "TMR0", click it (red box, see image below).

*TMR0 tab is vertical on the right*

![MCC - Nav to Tmr Config 1](images/MCC_nav_to_tmr_config_1.PNG)


Next click on the little black solid circle in the upper right of the screen (red box, see image below).

*TMR0 tab is selected, menu is behind builder tab*

![MCC - Nav to Tmr Config 2](images/MCC_nav_to_tmr_config_2.PNG)

The changes are highlighted by the red boxes (see image below):
- **Clock Prescaler** needs to change to 1:1024 (this will change the upper and lower bounds of the **Requested Period(s)** section)
- **Clock Source** needs to change to FOSC/4
- **Requested Period(s)** needs to change to 0.5 (this value represents the time between blinks, this number can be changed to any value within the provided bounds)
- **TMR Interrupt** is enabled (blue switch background)

*TMR0 Configuration tab*

![MCC - Tmr Config menu](images/MCC_tmr_config_menu.PNG)


### Interrupt Configuration
Just like the Timer Configuration skip ahead to the image that matches what you see on screen.

Click on the vertical Interrupt Manager tab on the right side (red box, see image below).

*Interrupt Manager tab is vertical on the right*

![MCC - Nav to Int menu](images/MCC_nav_to_int_menu_1.PNG)

NOTE: You may have the tab on the right in a different order

Now click on the little black solid circle in the upper right of the screen (red box, see image below).

*Interrupt Manager tab is selected, menu is behind TMR0 tab*

![MCC - Nav to Int Menu 2](images/MCC_nav_to_int_menu_2.PNG)


Now, the correct settings are selected in the configuration window.  There should not be any needed changes (see image below).

*Interrupt Manager tab*

![MCC - Int menu](images/MCC_Int_menu.PNG)


### Pin Configuration
The Pin controlling the onboard LED on the Curiosity Nano board was configured using the Pins Grid View.  The Pins Grid View is accessed by clicking on the Pins line in Project Resources.

*Project Resources - Pins*

![MCC - Open Pin Manager](images/MCC_project_resources_pins.PNG)


Then the pin connected to the LED, RF3, was selected as an output by clicking the corresponding padlock symbol (red box, see image below).

*Pins Grid View*

![MCC - Set Pin to Output](images/MCC_pins_grid_view.PNG)


The pin was also configured with a custom name to make the generated API more readable.  No other pin setting were modified.

*Custom Pin Name*

![MCC - Custom Pin Name](images/MCC_pins_custom_name.PNG)


### Code Implementation
Click Generate within the Project Resources Menu.

*Generate the code*

![MCC - Generate Code](images/MCC_generate_code.png)


First, the code needs an additional function to operate correctly.  This function uses the pin manager API to toggle the LED on and off.

```c
void LED_PIN_ISR(void){ 
    LED_PIN_Toggle();
    }
```
Then the pin manager and timer interrupt APIs are used to set the LED pin High (turns it off), and start a toggle sequence once the timer overflow interrupt is triggered.  Below are the specific steps in the code sequence:

```c
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
```
## Operation
After having flashed the application to the PIC18F57Q43 Curiosity Nano, the onboard LED is blinking on and off.

*Final Result - LED Blink*

![Curiosity Nano Onboard LED Blinking](images/Curiosity_Nano_LED_Blink_with_timer.gif)

## Summary

The example has shown how MCC can be used to configure the pins of the PIC18F57Q43 device.
