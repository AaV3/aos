#include <cstdio>
#include <algorithm>    // std::min_element
#include <miosix.h>
#include "adc.h"
#include "led.h"
#include "button.h"

//Specify the number of players
#define MAX_PLAYERS	2
//Used to measure time
miosix::Timer tim;
//Current player
int playerNr;
//Array stores score for every player
int playerTimes[MAX_PLAYERS - 1];

/*
 * Sequential procedure of all necessary steps for a game round
 */
void oneGameRound() {
	printf("\n\n\nPress button to start round for player %d\n\n",playerNr);
	waitForButton();
	printf("Get ready, player %d!\n\n", playerNr);
	LedMode mode = allFour;
	startLedTimer(mode, 200);
	usleep(2000000);
	stopLedTimer();

	mode = firstThree;
	startLedTimer(mode, 1000);
	usleep(3000000);
	stopLedTimer();

	//Receive random 32 bit number
	uint32_t rnd32 = miosix::HardwareRng::instance().get();
	//Convert the 32 bit number to a time delay between 2 and 6 s
	//presented in ms
	// 4294967296 = max 32 bit number
	int rndTime = (int) ((rnd32 / (double) 4294967296 * 4 + 2) * 1000);
	//Start time measurement
	tim.start();
	mode = fourth;
	startLedTimer(mode, rndTime);
	//Clear the watchdog so it can be restarted again
	disableWatchdog();
	//Wait for user reaction
	enableWatchdogAndWait();
	stopLedTimer();
	tim.stop();
	//Analyse the needed user reaction time
	int scoredTime = tim.interval() - rndTime;
	//If the user reacted faster than the possible human reaction time
	//declare him/her as a cheater and store 9000ms as the needed time
	playerTimes[playerNr - 1] = (scoredTime < 120) ? 9000 : scoredTime;
	tim.clear();
}

/*
 * At the end of a round this function determines the winner
 * and prints the results
 */
void decideWinner() {
	for (int i = 0; i < MAX_PLAYERS; ++i) {
		if (playerTimes[i] == 9000)
			printf("\nScore of player %d: CHEATER!", i + 1);

		else
			printf("\nScore of player %d: %d ms", i + 1, playerTimes[i]);
	}
	//Returns the position in the array of the smallest time
	int winner = std::min_element(playerTimes, playerTimes + MAX_PLAYERS)
			- &playerTimes[0];

	printf("\n\nPlayer %d has won this game!!!\n", winner + 1);
}

int main() {
	initLedTimer();
	configureButtonInterrupt();
	initAdc();

	for (;;) {
		calibrateThreshold();
		for (playerNr = 1; playerNr <= MAX_PLAYERS; ++playerNr) {
			oneGameRound();
		}
		decideWinner();
		printf("\nPress button to start a new game\n");
		waitForButton();

		printf("New game starts in\n");
		for (int i = 3; i >= 1; --i) {
			usleep(500000);
			printf("    %d\n", i);
		}

	}
	//This can be used for debugging purposes
	//it prints the actual sensor values
	/*uint16_t value = convert();
	 printf("%u\r\n",value);
	 usleep(500000);*/
}
