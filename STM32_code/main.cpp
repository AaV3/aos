//#include "registers.h"
#include <cstdio>
#include <miosix.h>
#include "adc.h"
#include "led.h"
using namespace miosix;

Adc adc;
Led led;

int main()
{
	printf("Game started\r\n");
	LedMode m = allFour;
	led.startLedTimer(m, 200);
	usleep(2000000);
	led.stopLedTimer();	
	//adc.enableWatchdogAndCheck();
	for(;;)
	{
		
		/*uint16_t value = adc.convert();
		printf("%u\r\n",value);
		*/
	}
}
