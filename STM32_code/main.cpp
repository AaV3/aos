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
	int rndTime = (int) ((rnd32 / (double) 4294967296 * 4 + 2)*1000);
	//printf("random: %d\n",rndTime);
	
	tim.start();
	m = fourth;
	startLedTimer(m, rndTime);
	

	//usleep(10400000);
	adc.disableWatchdog();
	adc.enableWatchdogAndWait();
	stopLedTimer();	
	tim.stop();
	int scoredTime = tim.interval() - rndTime;
	playerTimes[playerNr-1] = (scoredTime < 120) ? 9000 : scoredTime;
	tim.clear();
}

void decideWinner()
{
	for(int i = 0; i < MAX_PLAYERS; ++i){
		if(playerTimes[i] == 9000) printf("\nScore of player %d: CHEATER!!!", i+1);
		
		else printf("\nScore of player %d: %d ms", i+1, playerTimes[i]);		
	}
	int winner = std::min_element(playerTimes,playerTimes+MAX_PLAYERS)-&playerTimes[0];
	
	printf("\n\nPlayer %d has won this game!!!\n", winner+1);	
}

int main()
{
	initLedTimer();
	configureButtonInterrupt();
	
	
	for(;;)
	{
		for(playerNr = 1; playerNr <= MAX_PLAYERS; ++playerNr){
			oneGameRound();
		}
		decideWinner();
		printf("\nPress button to start a new game\n");		
		waitForButton();
		

		printf("New game starts in\n");
		for( int i = 3; i >= 1; --i) {
			usleep(500000);
			printf("      %d\n",i);
		}
		
	}
	/*uint16_t value = adc.convert();
		printf("%u\r\n",value);
		usleep(500000);*/
}
		
		




