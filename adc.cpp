#include "adc.h"
#include "registers.h"

Adc::Adc()
{

	//TODO:
	//Enable analog mode, set GPIOB_MODER of PB0
	GPIOB->MODER |= (0b11 << 0);

	//Enable port b clock GPIOBEN
	RCC->AHB1ENR |= (1 << 1);

	//Set ADC1 and ADC2 clocks
	RCC->APB2ENR |= (1 << 8);
	RCC->APB2ENR |= (1 << 9);
	
	//Set ADC resolution RES to 12bit
	ADC->ADC_CR1 |= (0b00 << 24);

	//Set ADC speed (prescaler) ADCPRE to PCLK2 / 4
	ADC->ADC_CCR |= (0b01 << 16);
	
	//Set sampling time of channel8 (SMP8) to 112 cycles
	ADC->ADC_SMPR2 |= (0b101 << 24);
	
	//Select channel8 for the 1st conversion (SQ1)
	// By default one conversion per group
	ADC->ADC_SQR2 |= (8 << 0);
	
	//Turn ADC on (ADON)
	ADC->ADC_CR2 |= (1 << 0);

	//Connect PBO to adc register (ADC12_IN8)
}
/*TODO:
start conversion with SWSTART in ADC_CR2

get values in ADC_DR:
– The EOC (end of conversion) flag is set (clear it afterwards?)
– An interrupt is generated if the EOCIE bit is set

think about single or continuous conversion mode
turn off / power down ADC with ADON to 0
  */
