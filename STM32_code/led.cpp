#include <miosix.h>
#include <cstdio>
#include "led.h"

using namespace miosix;

LedMode currentMode;

Led::Led(){
	initLed();
	initTimer();
	enableTimerInterrupt();
}

// Function for configuring the GPIO
void Led::initLed() {
	greenLed::mode(Mode::OUTPUT);
	blueLed::mode(Mode::OUTPUT);
	redLed::mode(Mode::OUTPUT);
	orangeLed::mode(Mode::OUTPUT);
}

// Function for initializing and configuring the timer
void Led::initTimer() {
	// 1. Enable the peripheral clock of Timer 2 (Timer 2 is on APB1)
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	// 2. Configure Timer prescaler to realize 100kHz counter
	// --> 168 MHz / 100kHz = 1680
	
	// 3. Configure timer auto reload to realize an overflow each 1s
	TIM3->ARR = 9999;
	// 4. Configure upcounting
	// Update event = is 0 by default and thus activated
	// ARPE = Auto-reload preload enable (buffers value of ARR register)
	// URS = Update request source
	TIM3->CR1 = TIM_CR1_ARPE | TIM_CR1_URS;
}

void Led::enableTimerInterrupt() {
	//Enable update interrupt for the timer
	TIM3->DIER = TIM_DIER_UIE;
	// Set priority for the interrupt
	NVIC_SetPriority(TIM3_IRQn, 1);
	// Enable interrupt for timer 2
	NVIC_EnableIRQ(TIM3_IRQn);
}

void Led::startLedTimer(LedMode mode, uint16_t intervalInMs){
	currentMode = mode;
	// presc = Systick*desiredIntervall/ARR/4
	uint16_t prescaler = 168000*intervalInMs/10000/4;
	printf("Ja: %u\n",prescaler);
	TIM3->PSC = prescaler;
	//Activate the timer
	TIM3->CR1 |= TIM_CR1_CEN;
}

void Led::stopLedTimer(){
	TIM3->CR1 &= ~TIM_CR1_CEN;
}

//Function for toggling the LED, called by interrupt
void toggleAllLed() {
	static bool led_on = false;
	if (led_on) {
		greenLed::low();
		blueLed::low();
		redLed::low();
		orangeLed::low();
		led_on = false;
	} else {
		greenLed::high();
		blueLed::high();
		redLed::high();
		orangeLed::high();
		led_on = true;
	}
}

// Handler for Timer2 overflow interrupt
void TIM3_IRQHandler(){
	//printf("in interrupt\r\n");
	if(TIM3->SR & TIM_SR_UIF) {
		//Reset the update interrupt flag bit
		TIM3->SR ^= TIM_SR_UIF;
		if(currentMode == allFour){
			//Toggle the LED
			toggleAllLed();
		}
	}
}
