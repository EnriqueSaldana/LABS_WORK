//Enrique Saldana
//CpE 403 Lab4 Task00
#include<stdint.h>
#include<stdbool.h>
#include"inc/hw_memmap.h"
#include"inc/hw_types.h"
#include"driverlib/debug.h"
#include"driverlib/sysctl.h"
#include"driverlib/adc.h"
#define TARGET_IS_BLIZZARD_RB1
#include "driverlib/rom.h"

int main(void)
{
    //Sequence 1 FIFO depth of 4
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

    //Configure ADC Sequencer as Sequencer 1, triggered by processor and highest priority
    ROM_ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);

    //Configure steps 0 -2 on sequencer 1 to sample the temperature sensor
    ROM_ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_TS);
    ROM_ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_TS);
    ROM_ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_TS);

    //Configure interrupt flag and tell ADC Logic that it is the last conversion on sequencer 1
    ROM_ADCSequenceStepConfigure(ADC0_BASE,1,3,ADC_CTL_TS|ADC_CTL_IE|ADC_CTL_END);

    //Enable ADC sequencer 1
    ROM_ADCSequenceEnable(ADC0_BASE, 1);

    while(1)
    {
        //Clear ADC interrupt status flag
        //Trigger ADC conversion
        ROM_ADCIntClear(ADC0_BASE, 1);
        ROM_ADCProcessorTrigger(ADC0_BASE, 1);

        //Wait for conversion to finish
        while(!ROM_ADCIntStatus(ADC0_BASE, 1, false))
        {

        }

        //Read ADC values
        //Calculate average temperature
        //Calculate Celsius value
        //Calculate Fahrenheit value
        ROM_ADCSequenceDataGet(ADC0_BASE, 1, ui32ADC0Value);
        ui32TempAvg = (ui32ADC0Value[0] + ui32ADC0Value[1] + ui32ADC0Value[2] + ui32ADC0Value[3] + 2)/4;
        ui32TempValueC = (1475 -((2475 * ui32TempAvg)) / 4096)/10;
        ui32TempValueF = ((ui32TempValueC * 9) + 160) / 5;

    }
}

