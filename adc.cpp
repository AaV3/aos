#include "adc.h"
#include "registers.h"

ADC::ADC()
{
  //TODO:
  //Enable analog mode, set GPIOB_MODER0 to 11
  GPIOB->MODER |= (1<<0 | 1 << 1);
  //conenct PBO to adc register (ADC12_IN8)
  //Set ADC clock
  //set ADC speed (prescale and sample time)
  //set measurement mode

}
  //make function to turn on ADC (set ADON in register ADC_CR2)
  //and to turn off
