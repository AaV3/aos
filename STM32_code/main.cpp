//#include "registers.h"
#include <cstdio>
#include <algorithm>    // std::min_element
#include <miosix.h>
#include "adc.h"
#include "led.h"
#include "button.h"
using namespace miosix;


#define MAX_PLAYERS	2
Adc adc;
Timer tim;
int playerNr;
int playerTimes[MAX_PLAYERS-1];

int place = 243;

void oneGameRound()
{
	printf("\n\n\nPress button to start round for player %d\n\n", playerNr);	
	waitForButton();
	printf("Get ready, player %d!\n\n", playerNr);
	LedMode m = allFour;
    startLedTimer(m, 200);
	usleep(2000000);
	stopLedTimer();
	
	m = firstThree;
	startLedTimer(m, 1000);
	usleep(3000000); // LED off
	stopLedTimer();
	
	uint32_t rnd32 = HardwareRng::instance().get();
	// get time delays between 1 and 10 sec converted to ms
	int rndTime = (int) ((rnd32 / (double) 4294967296 * 8 + 2)*1000);
	
	m = fourth;
	startLedTimer(m, rndTime);
	
	tim.start();	
	usleep(10000000);
	//adc.enableWatchdogAndWait();
	tim.stop();
	playerTimes[playerNr-1] = place++;//tim.interval();
}

void decideWinner()
{
	for(int i = 0; i < MAX_PLAYERS; ++i){
		printf("\nScore of player %d: %d ms", i+1, playerTimes[i]);		
	}
	int winner = std::min_element(playerTimes,playerTimes+MAX_PLAYERS)-&playerTimes[0];
	
	printf("\n\nPlayer %d has won this game!!!\n", winner+1);	
}

int main()
{
	initLedTimer();
	configureButtonInterrupt();
	for(playerNr = 1; playerNr <= MAX_PLAYERS; ++playerNr){
		oneGameRound();
	}
	decideWinner();
	
	for(;;)
	{
		/*uint16_t value = adc.convert();
		printf("%u\r\n",value);*/
		usleep(500000);
	}
}
		
		




