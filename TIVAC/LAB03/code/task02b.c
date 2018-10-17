//Enrique Saldana
//CpE 403
//Lab 3 Part B
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

//Integer Variable used in LED's
uint8_t ui8PinData=2;

int main(void)
{
    //Set clock to 4.7 MHz
    SysCtlClockSet(SYSCTL_SYSDIV_42_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    //Enable clock for peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    //Configure LED's as outputs
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

    while(1)
    {
        //Turn on LED
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, ui8PinData);
        SysCtlDelay(2000000);
        //Turn off LED
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x00);
        SysCtlDelay(2000000);
        //Cycle through R, G, B, RG, RB, GB, RGB...
        if(ui8PinData==2) {ui8PinData=8;}
        else if (ui8PinData==8) {ui8PinData=4;}
            else if (ui8PinData==4) {ui8PinData=10;}
                else if (ui8PinData==10) {ui8PinData=6;}
                    else if (ui8PinData==6) {ui8PinData=12;}
                        else if (ui8PinData==12) {ui8PinData=14;}
                            else {ui8PinData=2;}
    }
}
