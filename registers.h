#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

/*
 * Reset and Clock Control. This peripheral is used to turn on the other peripherals
 */

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t PLLCFGR;
  volatile uint32_t CFGR;
  volatile uint32_t CIR;
  volatile uint32_t AHB1RSTR;
  volatile uint32_t AHB2RSTR;
  volatile uint32_t AHB3RSTR;
  uint32_t          RESERVED0;
  volatile uint32_t APB1RSTR;
  volatile uint32_t APB2RSTR;
  uint32_t          RESERVED1[2];
  volatile uint32_t AHB1ENR;
  volatile uint32_t AHB2ENR;
  volatile uint32_t AHB3ENR;
  uint32_t          RESERVED2;
  volatile uint32_t APB1ENR;
  volatile uint32_t APB2ENR;
} RCC_TypeDef;

#define RCC ((RCC_TypeDef *)0x40023800)

//Enable GPIO B-register clock
#define RCC_AHB1ENR_GPIOBEN (0x00000002)

//Enable ADC 1 and 2
#define RCC_APB2ENR_ADC1  (0x)




/*
 * GPIOB. This peripheral controls port B of the GPIOs
 */

typedef struct
{
  volatile uint32_t MODER;
  volatile uint32_t OTYPER;
  volatile uint32_t OSPEEDR;
  volatile uint32_t PUPDR;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t LCKR;
  volatile uint32_t AFR[2];
 } GPIO_TypeDef;

//Page 65 datasheet
#define GPIOB ((GPIO_TypeDef *)0x40020400)

//Analog to Digital converter pheripheral

typedef struct
{
  volatile uint32_t ADC_CR1;
  volatile uint32_t ADC_CR2;
  volatile uint32_t ADC_SMPR1;
  volatile uint32_t ADC_SMPR2;
  volatile uint32_t ADC_JOFR1; //figure out x, use 1 for start
  volatile uint32_t ADC_HTR;
  volatile uint32_t ADC_LTR;
  volatile uint32_t ADC_SQR1;
  volatile uint32_t ADC_SQR2;
  volatile uint32_t ADC_SQR3;
  volatile uint32_t ADC_JSQR;
  volatile uint32_t ADC_JDR1; // figure out x, use 1 for start
  volatile uint32_t ADC_DR;
  volatile uint32_t AC_SR;
  volatile uint32_t ADC_CCR;
  volatile uint32_t ADC_CDR;
} ADC_TypeDef;

#define ADC ((ADC_TypeDef *)0x40012000)

//ADC_CR2_ADON used for turning on ADC clock
#define ADC_CR2_ADON (0x00000001)


//

#endif //REGISTERS_H
