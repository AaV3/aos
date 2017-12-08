//#include "registers.h"
#include <cstdio>
#include <miosix.h>
#include "adc.h"
#include "led.h"
#include "button.h"
using namespace miosix;

Adc adc;
Timer tim;

int main()
{
	printf("\n\n\nPress Button to Start Game...\n\n");	
	configureButtonInterrupt();
	waitForButton();
	printf("Get Ready, Player 1!\n\n");
	initLedTimer();
	LedMode m = allFour;
    startLedTimer(m, 200);
	usleep(2000000);
	stopLedTimer();
	
	m = firstThree;
	startLedTimer(m, 1000);
	usleep(3000000);
	stopLedTimer();
	
	uint32_t rnd32 = HardwareRng::instance().get();
	// get time delays between 1 and 10 sec converted to ms
	int rndTime = (int) ((rnd32 / (double) 4294967296 * 9 + 1)*1000);
	
	m = fourth;
	startLedTimer(m, rndTime);
	
	tim.start();
	adc.enableWatchdogAndWait();
	tim.stop();
	printf("Time passed: %u\n", tim.interval());
	
	
	
    for(;;)
	{
		/*uint16_t value = adc.convert();
		printf("%u\r\n",value);*/
		usleep(500000);
		
	}
}
