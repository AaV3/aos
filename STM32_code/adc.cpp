#include <miosix.h>
#include <cstdio>
#include "adc.h"

//Variable used to store sensor threshold value
int thresholdValue = 0;

void initAdc() {
	//Enable port b clock GPIOBEN
	RCC->AHB1ENR |= (1 << 1);
	//Enable analog input mode, set GPIOB_MODER of PB0
	GPIOB->MODER |= (0b11 << 0);
	//Set ADC1 clock
	RCC->APB2ENR |= (1 << 8);
	//Set ADC resolution RES to 12bit
	ADC1->CR1 |= (0b00 << 24);
	//Set ADC speed (prescaler) ADCPRE to PCLK2/8
	ADC->CCR |= (0b11 << 16);
	//Set sampling time of channel8 (SMP8) to 84 cycles
	ADC1->SMPR2 |= (0b100 << 24);
	//Right data alignment and continuous conversion mode
	ADC1->CR2 |= (0 << 11) + (1 << 1);
	//Select channel8 for the 1st conversion (SQ1)
	// By default one conversion per group
	ADC1->SQR3 |= (8 << 0);
	//Turn ADC on (ADON)
	ADC1->CR2 |= (1 << 0);
	//Start continuous conversion (SWSTART)
	ADC1->CR2 |= (1 << 30);
}

/*
 * Convert one sample of the photodiode input
 */
uint16_t convert() {
	//Wait for end of one conversion
	while ((ADC1->SR & ADC_SR_EOC) == 0);

	return (uint16_t) ADC1->DR & ADC_DR_DATA;
}

void disableWatchdog() {
	ADC1->SR &= ~ADC_SR_AWD;
}

/*
 * This analog watchdog becomes active if the adc channel
 * falls below a defined threshold
 */
void enableWatchdogAndWait() {
	//Set watchdog channel select bits AWDCH to 8
	ADC1->CR1 |= (8 << 0);
	//Set lower treshold
	ADC1->LTR = thresholdValue;
	//Enable watchdog
	ADC1->CR1 |= ADC_CR1_AWDEN + ADC_CR1_AWDSGL;
	//Wait until watchdog activates
	while ((ADC1->SR & ADC_SR_AWD) == 0);
}

/*
 * At the beginning of every game new ambient light changes
 * are taken into account to derive a new threshold
 * for the touch detection
 */
void calibrateThreshold() {
	int temp = 0;
	for (int i = 0; i < 20; ++i) {
		temp += convert();
	}
	temp /= 20;
	thresholdValue = temp - 30;
}
