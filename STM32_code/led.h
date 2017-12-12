#ifndef LED_H
#define LED_H

#include <miosix.h>

typedef miosix::Gpio<GPIOD_BASE,12> greenLed;
typedef miosix::Gpio<GPIOD_BASE,13> orangeLed;
typedef miosix::Gpio<GPIOD_BASE,14> redLed;
typedef miosix::Gpio<GPIOD_BASE,15> blueLed;

enum LedMode {
	allFour, firstThree, fourth
};

void initLedTimer();
void startLedTimer( LedMode, uint16_t intervalInMs);
void stopLedTimer();

#endif //LED_H
