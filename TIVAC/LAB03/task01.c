//Enrique Saldana
//CpE 403
//Lab 3 Task 01
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

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
		//Cycle through R, B, G, R, B, G ...
		if(ui8PinData==8) {ui8PinData=2;} else {ui8PinData=ui8PinData*2;}
	}
}


