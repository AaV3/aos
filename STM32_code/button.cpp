#include <miosix.h>
#include "button.h"

typedef miosix::Gpio<GPIOA_BASE, 0> button;

bool waiting = true;

/*
 * Interrupt handler called when button is pressed
 */
void EXTI0_IRQHandler() {
	EXTI->PR = EXTI_PR_PR0;
	waiting = false;
}

/*
 * Enable interrupts for button detection
 */
void configureButtonInterrupt() {
	button::mode(miosix::Mode::INPUT_PULL_DOWN);
	EXTI->IMR |= EXTI_IMR_MR0;
	EXTI->RTSR |= EXTI_RTSR_TR0;
	NVIC_EnableIRQ (EXTI0_IRQn);
	NVIC_SetPriority(EXTI0_IRQn, 15); //Low priority
}

/*
 * This function blocks until the button is pressed
 */
void waitForButton() {
	waiting = true;
	while (waiting);
}
