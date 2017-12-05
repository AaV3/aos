//#include "registers.h"
#include <cstdio>
#include <miosix.h>
#include "adc.h"
using namespace miosix;

//PD14: red led
typedef Gpio<GPIOD_BASE,12> greenLed;
typedef Gpio<GPIOD_BASE,13> orangeLed;
typedef Gpio<GPIOD_BASE,14> redLed;
typedef Gpio<GPIOD_BASE,15> blueLed;

Adc adc;

int main()
{
	greenLed::mode(Mode::OUTPUT);
	blueLed::mode(Mode::OUTPUT);
	redLed::mode(Mode::OUTPUT);
	orangeLed::mode(Mode::OUTPUT);
	
	for(;;)
	{
		uint16_t value = adc.convert();
		printf("%u\r\n",value);
		usleep(10000000);
		/*blueLed::high();
		usleep(100);
		blueLed::low();*/
	}
}
