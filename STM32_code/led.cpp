#include <miosix.h>
#include <cstdio>
#include "led.h"

using namespace miosix;

//The LED mode determines which blinking sequence is active
LedMode currentMode;
//LedsOn indicates the status of all LEDs
bool ledsOn;
//The first timer interrupt is called too fast, so we ignore it once
bool skipFirstInterrupt;

/*
 * Function for configuring the GPIO
 */
void initLed() {
	greenLed::mode(Mode::OUTPUT);
	blueLed::mode(Mode::OUTPUT);
	redLed::mode(Mode::OUTPUT);
	orangeLed::mode(Mode::OUTPUT);
}

/*
 * Function for initializing and configuring the timer
 */
void initTimer() {
	//Enable the peripheral clock of timer 3
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	//Configure timer auto reload to realize periodic overflows
	TIM3->ARR = 9999;
	//ARPE = Auto-reload preload enable (buffers value of ARR register)
	//URS = Update request source
	TIM3->CR1 = TIM_CR1_ARPE | TIM_CR1_URS;
}

void enableTimerInterrupt() {
	//Enable update interrupt for the timer
	TIM3->DIER = TIM_DIER_UIE;
	//Set priority for the interrupt
	NVIC_SetPriority(TIM3_IRQn, 15);
	//Enable interrupt for timer 3
	NVIC_EnableIRQ(TIM3_IRQn);
}

void initLedTimer() {
	initLed();
	initTimer();
	enableTimerInterrupt();
}

/*
 * Timer 3 is started to generate interrupts in desired timer intervals
 * A specific LED blinking mode is associated with this timer
 */
void startLedTimer(LedMode mode, uint16_t intervalInMs) {
	currentMode = mode;
	ledsOn = false;
	skipFirstInterrupt = false;
	greenLed::low();
	blueLed::low();
	redLed::low();
	orangeLed::low();
	//Configure timer prescaler
	//Systick: 168MHz/4
	//Prescaler = Systick*desiredInterval/(ARR+1)
	uint16_t prescaler = 168000 * intervalInMs / 10000 / 4;
	TIM3->PSC = prescaler;
	//Activate the timer
	TIM3->CR1 |= TIM_CR1_CEN;
}

void stopLedTimer() {
	TIM3->CR1 &= ~TIM_CR1_CEN;
}

/*
 * Function for fast toggling all LEDs, called by interrupt
 */
void toggleAllLed() {
	if (ledsOn) {
		greenLed::low();
		blueLed::low();
		redLed::low();
		orangeLed::low();
		ledsOn = false;
	} else {
		greenLed::high();
		blueLed::high();
		redLed::high();
		orangeLed::high();
		ledsOn = true;
	}
}

/*
 * Function for the LED game starting sequence, called by interrupt
 */
void toggleOneAfterOther() {
	if (ledsOn) {
		greenLed::low();
		blueLed::low();
		redLed::low();
		orangeLed::low();
		ledsOn = false;
	} else {
		//Internal state used for the LED sequence
		static int count = 1;

		switch (count) { //No "break" here
		case 3:
			greenLed::high();
		case 2:
			blueLed::high();
		case 1:
			redLed::high();

		}
		ledsOn = true;
		//Increment count until 3, then start again at 1
		count = (count == 3) ? count = 1 : ++count;
	}
}

/*
 * Function for flashing all LEDs once after the random time
 * Called by interrupt
 */
void toggleLast() {
	//Check if it is the first time this function is called
	//If yes, do not blink, just wait for the second interrupt
	if (!skipFirstInterrupt) {
		skipFirstInterrupt = true;
		return;
	}
	//LedsOn logic is inversed on purpose
	if (ledsOn) {
		greenLed::high();
		blueLed::high();
		redLed::high();
		orangeLed::high();
		ledsOn = false;
	} else {
		greenLed::low();
		blueLed::low();
		redLed::low();
		orangeLed::low();
		ledsOn = true;
	}
}

/*
 * Handler for timer 3 overflow interrupt
 */
void TIM3_IRQHandler() {
	//Check if it is an update interrupt of timer 3
	if (TIM3->SR & TIM_SR_UIF) {
		//Reset the update interrupt flag bit
		TIM3->SR ^= TIM_SR_UIF;
		//Choose corresponding function for the different LED modes
		if (currentMode == allFour)
			toggleAllLed();
		else if (currentMode == firstThree)
			toggleOneAfterOther();
		else if (currentMode == fourth)
			toggleLast();
	}
}
