//#include "registers.h"
#include <miosix.h>

#ifndef ADC_H
#define ADC_H

class Adc
{
public:
	Adc();
	uint16_t convert();
	void enableWatchdogAndCheck();
private:

};

#endif //ADC_H
