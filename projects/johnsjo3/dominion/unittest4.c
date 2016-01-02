/*
* UNIT TEST 4
* -----------
* This unit test tests the functionality of the scoreFor() function in
* dominion.c.
*
* scoreFor() calculates a player's score given the player's number and a gameState.
*
* INPUTS: The gameState and player number.  The player number will be randomized from 2 to
* MAX_PLAYERS.  The gameState will be fuzzed, then assigned more specific randomized numbers to
* for its cards (within the range of selectable cards).
*
* OUTPUT: The gameState will be compared before and after the function to assert that
* no changes were made to the state.  The scores will also be compared to a calculation to make
* sure the function matches the desired outcome.
*/

#include "dominion.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

void fuzzState(struct gameState *);
int randomNumber(int, int);
int percentChanceIsOne(int);
int calcScore(int playerNum, struct gameState * gs);
int getCardScore(int c, int cardsInDeck);

main(int argc, char * argv[]) {
	int unit4_test_trials = 10000;
	
	if (argc > 1) {
		unit4_test_trials = atoi(argv[1]);
		if (unit4_test_trials < 1) {
			printf("Usage: unittest3 <trials>\r\n");
			exit(1);
		}
	}
	
	srand(time(NULL));
	
	//new gameState
	struct gameState * gs = malloc(sizeof(struct gameState));
	struct gameState * stateCopy = malloc(sizeof(struct gameState));
	
	int i;
	int trial;
	int returnValue;
	int numberOfErrors = 0;
	int playerNum;
	
	printf("Unit test 4\r\n");
	printf("Conducting %d random trials.\r\n", unit4_test_trials);
	
	for (trial = 0; trial < unit4_test_trials; trial++) {
		fuzzState(gs);

		//semi-randomize inputs (within reason)
		playerNum = randomNumber(2,MAX_PLAYERS);
		gs->deckCount[playerNum] = randomNumber(0,MAX_DECK);
		gs->handCount[playerNum] = randomNumber(0,MAX_HAND);
		gs->discardCount[playerNum] = randomNumber(0,MAX_DECK);
		
		for (i = 0; i < gs->deckCount[playerNum]; i++) {
			gs->deck[playerNum][i] = randomNumber(0, treasure_map);
		}
		
		for (i = 0; i < gs->handCount[playerNum]; i++) {
			gs->hand[playerNum][i] = randomNumber(0, treasure_map);
		}
		
		for (i = 0; i < gs->discardCount[playerNum]; i++) {
			gs->discard[playerNum][i] = randomNumber(0, treasure_map);
		}
		
		
		//for later comparison
		memcpy(stateCopy, gs, sizeof(struct gameState));
		
		//perform function
		returnValue = scoreFor(playerNum, gs);

		//compare states
		if (memcmp( gs, stateCopy, sizeof(struct gameState)) != 0) {
			printf("Modification detected in state!\r\n");
			numberOfErrors++;
		} else if (returnValue != -9999) {
		// Run check
			if (calcScore(playerNum, gs) != returnValue) {
				printf("Mismatch in score calculations.  scoreFor(): %d, Expected: %d\r\n", returnValue, calcScore(playerNum, gs));
				numberOfErrors++;
			}
		}
	}	
	
	printf("Unit Test 4 Complete\r\n");
	printf("Number of errors found: %d\r\n", numberOfErrors);
	

	free(gs);
	free(stateCopy);
	return 0;
}

void fuzzState(struct gameState * state) {
	int i;
	
	unsigned char * ptr = (unsigned char *)state;
	
	for (i = 0; i < sizeof(struct gameState); i++) {
		ptr[i] = (unsigned char)(rand()%256);
	}
}

int randomNumber(int from, int to) {
	int a, b;
	if (from < to) {
		a = from;
		b = to;
	} else {
		a = to;
		b = from;
	}
	
	return rand() % ((b - a) + 1) + a;
}

int percentChanceIsOne(int probability) {
	if ( probability > (rand() % 100)) {
		return 1;
	} else {
		return 0;
	}
}

int calcScore(int p, struct gameState * gs) {
	int i;
	int totalScore = 0;		//total score
	int cardsInDeck = gs->deckCount[p] + gs->handCount[p] + gs->discardCount[p]; 
	
	//Deck
	for (i = 0; i < gs->deckCount[p]; i++) {
		totalScore += getCardScore(gs->deck[p][i], cardsInDeck);
	}
	
	//Hand
	for (i = 0; i < gs->handCount[p]; i++) {
		totalScore += getCardScore(gs->hand[p][i], cardsInDeck);
	}
	
	//Discard
	for (i = 0; i < gs->discardCount[p]; i++) {
		totalScore += getCardScore(gs->discard[p][i], cardsInDeck);
	}
	
	return totalScore;
}

int getCardScore(int c, int cardsInDeck) {
	switch(c) {
		case curse: return -1; break;
		case estate: return 1; break;
		case duchy: return 3; break;
		case province: return 6; break;
		case great_hall: return 1; break;
		case gardens: return cardsInDeck / 10;
	}
	
	//no score
	return 0;
}
