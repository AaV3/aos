#include "adc.h"
#include "registers.h"

ADC::ADC()
{
  //TODO:
  //Enable analog mode, set GPIOB_MODER0 to 11
  GPIOB_MODER0 |= 3;
  //conenct PBO to adc register (ADC12_IN8)

  //Enable port b clock
  RCC-> AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

  //Set ADC clocks
  RCC-> APB2ENR |= RCC_APB2ENR_ADC1;
  RCC-> APB2ENR |= RCC_APB2ENR_ADC2;

  //set ADC speed (prescale and sample time)
  ADC_CCR |= (1 << 16);  //set measurement mode

RCC -> ADC_CR1 |= (0<<24);
}
  //make function to turn on ADC (set ADON in register ADC_CR2)
  //and to turn off
