
#include "button.h"
#include <miosix.h>
#include <miosix/kernel/scheduler/scheduler.h>

using namespace miosix;

typedef Gpio<GPIOA_BASE,0> button;

bool waiting = true;

void EXTI0_IRQHandler()
{
    //printf("Button pressed\r\n");
    EXTI->PR=EXTI_PR_PR0;
    waiting = false;
}

void configureButtonInterrupt()
{
    button::mode(Mode::INPUT_PULL_DOWN);
    EXTI->IMR |= EXTI_IMR_MR0;
    EXTI->RTSR |= EXTI_RTSR_TR0;
    NVIC_EnableIRQ(EXTI0_IRQn);
    NVIC_SetPriority(EXTI0_IRQn,15); //Low priority
}

void waitForButton()
{
	waiting = true;
    while(waiting);
}
