//Enrique Saldana
//CpE 403 Lab5 Task01
#include<stdint.h>
#include<stdbool.h>
#include"inc/hw_memmap.h"
#include"inc/hw_types.h"
#include"driverlib/debug.h"
#include"driverlib/sysctl.h"
#include"driverlib/adc.h"
#define TARGET_IS_BLIZZARD_RB1
#include "driverlib/rom.h"
#include "driverlib/gpio.h"

int main(void)
{
    //Sequencer 2 FIFO depth of 4
    uint32_t ui32ADC0Value[4];

    //Variable used to calculate average temperature
    //Variables used to store the temperature values in Celsius and Fahrenheit
    volatile uint32_t ui32TempAvg;
    volatile uint32_t ui32TempValueC;
    volatile uint32_t ui32TempValueF;

    //Set system clock to run at 40MHz
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);

    //Enable ADC0 Peripheral
    //64 measurements being averaged
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    ROM_ADCHardwareOversampleConfigure(ADC0_BASE, 64);

    //Configure ADC Sequencer as Sequencer 2, triggered by processor and highest priority
    ROM_ADCSequenceConfigure(ADC0_BASE, 2, ADC_TRIGGER_PROCESSOR, 0);

    //Configure steps 0 -2 on sequencer 2 to sample the temperature sensor
    ROM_ADCSequenceStepConfigure(ADC0_BASE, 2, 0, ADC_CTL_TS);
    ROM_ADCSequenceStepConfigure(ADC0_BASE, 2, 1, ADC_CTL_TS);
    ROM_ADCSequenceStepConfigure(ADC0_BASE, 2, 2, ADC_CTL_TS);

    //Configure interrupt flag and tell ADC Logic that it is the last conversion on sequencer 2
    ROM_ADCSequenceStepConfigure(ADC0_BASE,2,3,ADC_CTL_TS|ADC_CTL_IE|ADC_CTL_END);

    //Enable ADC sequencer 2
    ROM_ADCSequenceEnable(ADC0_BASE, 2);

    //Enable clock for peripheral
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    //Configure PF2 LED as output
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_2);


    while(1)
    {

        //Clear ADC interrupt status flag
        //Trigger ADC conversion
        ROM_ADCIntClear(ADC0_BASE, 2);
        ROM_ADCProcessorTrigger(ADC0_BASE, 2);

        //Wait for conversion to finish
        while(!ROM_ADCIntStatus(ADC0_BASE, 2, false))
        {

        }

        //Read ADC values
        //Calculate average temperature
        //Calculate Celsius value
        //Calculate Fahrenheit value
        ROM_ADCSequenceDataGet(ADC0_BASE, 2, ui32ADC0Value);
        ui32TempAvg = (ui32ADC0Value[0] + ui32ADC0Value[1] + ui32ADC0Value[2] + ui32ADC0Value[3] + 2)/4;
        ui32TempValueC = (1475 -((2475 * ui32TempAvg)) / 4096)/10;
        ui32TempValueF = ((ui32TempValueC * 9) + 160) / 5;
        //Turn PF2 LED on if temp value is greater than 72
        if(ui32TempValueF > 72)
        {
                ROM_GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2, 4);
                ROM_SysCtlDelay(2000000);
        }
        else
        {

            ROM_GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2, 0x00);
        }
    }
}

