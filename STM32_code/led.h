#ifndef LED_H
#define LED_H

#include <cstdio>
#include <miosix.h>

using namespace miosix;

typedef Gpio<GPIOD_BASE,12> greenLed;
typedef Gpio<GPIOD_BASE,13> orangeLed;
typedef Gpio<GPIOD_BASE,14> redLed;
typedef Gpio<GPIOD_BASE,15> blueLed;

enum LedMode { allFour, start };

class Led
{	
	public:
		Led();
		void initLed();
		void initTimer();
		void enableTimerInterrupt();
		void startLedTimer(LedMode, uint16_t intervalInMs);
		void stopLedTimer();
};

#endif //LED_H
