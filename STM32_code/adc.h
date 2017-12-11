//#include "registers.h"

#ifndef ADC_H
#define ADC_H

	void initAdc();
	uint16_t convert();
	void enableWatchdogAndWait();
	void disableWatchdog();
	void calibrateThreshold();


#endif //ADC_H
