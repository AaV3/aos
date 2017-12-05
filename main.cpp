//#include "registers.h"
//#include "adc.h"
#include <cstdio>
#include <miosix.h>
using namespace miosix;

//PD14: red led
typedef Gpio<GPIOD_BASE,12> greenLed;
typedef Gpio<GPIOD_BASE,13> orangeLed;
typedef Gpio<GPIOD_BASE,14> redLed;
typedef Gpio<GPIOD_BASE,15> blueLed;

int main()
{
	greenLed::mode(Mode::OUTPUT);
	blueLed::mode(Mode::OUTPUT);
	redLed::mode(Mode::OUTPUT);
	orangeLed::mode(Mode::OUTPUT);
	
	for(;;)
	{
		printf("Hello world\r\n");
		usleep(500000);
		blueLed::high();
		usleep(500000);
		blueLed::low();
	}
}
