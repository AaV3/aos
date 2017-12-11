#include <miosix.h>
#include "adc.h"
#include <cstdio>
//#include "registers.h"

Adc::Adc()
{
	//Enable port b clock GPIOBEN
	RCC->AHB1ENR |= (1 << 1);
	
	//Enable analog mode, set GPIOB_MODER of PB0
	GPIOB->MODER |= (0b11 << 0);

	//Set ADC1 clock
	RCC->APB2ENR |= (1 << 8);
	//RCC->APB2ENR |= (1 << 9);
	
	//Set ADC resolution RES to 12bit
	ADC1->CR1 |= (0b00 << 24);

	//Set ADC speed (prescaler) ADCPRE to PCLK2 / 4
	ADC->CCR |= (0b11 << 16);
	
	//Set sampling time of channel8 (SMP8) to 112 cycles
	ADC1->SMPR2 |= (0b111 << 21);
	
	//Right alignment and Cont conver!!!
	ADC1->CR2 |= (0 << 11);
	ADC1->CR2 |= (1 << 1);
	
	//Select channel8 for the 1st conversion (SQ1)
	// By default one conversion per group
	ADC1->SQR3 |= (8 << 0);
	
	//Turn ADC on (ADON)
	ADC1->CR2 |= (1 << 0);
	
	//Start!!!
	ADC1->CR2 |= (1 << 30);
}

uint16_t Adc::convert(){
	//start conversion with SWSTART
	//ADC1->CR2 |= (1 << 30);
	while ((ADC1->SR & ADC_SR_EOC) == 0){
	} // wait for end of conversion*/
	return (uint16_t) ADC1->DR & ADC_DR_DATA;
}

void Adc::disableWatchdog(){
	ADC1->SR &= ~ADC_SR_AWD;
}

void Adc::enableWatchdogAndWait(){
	//Set watchdog channel select bits AWDCH to 8
	ADC1->CR1 |= (8 << 0);
	//Set lower treshold
	ADC1->LTR = 370;
	//Enable watchdog
	ADC1->CR1 |= ADC_CR1_AWDEN + ADC_CR1_AWDSGL;
	//Check if watchdog activates
	while((ADC1->SR & ADC_SR_AWD) == 0);

	// Shut down ADC
	//ADC1->CR2 &= ~ADC_CR2_ADON;
}
