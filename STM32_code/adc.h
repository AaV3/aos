//#include "registers.h"

#ifndef ADC_H
#define ADC_H

class Adc
{
public:
	Adc();
	uint16_t convert();
	void enableWatchdogAndWait();
	void disableWatchdog();
private:

};

#endif //ADC_H
