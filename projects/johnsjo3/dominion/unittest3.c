/*
* Unit Test 3
* ------------
* This unit test tests for isGameOver().  According to the rules, the game is over when
* 1. Province cards have been eliminated from game OR
* 2. Three supply cards have been exhausted
*
* INPUT: A random game state will be introduced.  Upon occasion, one of the two criteria will
* be introduced intentionally.
* 
* OUTPUT: The game state should not change.  Instead, 1 will be returned for when the criteria are met.
* If a 1 is returned and the criteria is not met, an error will be recorded.
*/

#include "dominion.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

void fuzzState(struct gameState *);
int randomNumber(int, int);
int percentChanceIsOne(int);
int depletedSupplies(struct gameState *);

main(int argc, char * argv[]) {
	int unit3_test_trials = 10000;
	
	if (argc > 1) {
		unit3_test_trials = atoi(argv[1]);
		if (unit3_test_trials < 1) {
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

	printf("Unit test 3\r\n");
	printf("Conducting %d random trials.\r\n", unit3_test_trials);	

	for (trial = 0; trial < unit3_test_trials; trial++) {
		fuzzState(gs);

		//semi-randomize inputs (within reason)
		int zeroSupplyProvince = percentChanceIsOne(5);
		int zeroSuppliesInThree = percentChanceIsOne(5);

		if (zeroSupplyProvince == 1){
			gs->supplyCount[province] = 0;
		}
		
		if (zeroSuppliesInThree == 1){
			for (i = 0; i < 3; i++) {
				gs->supplyCount[rand()%(treasure_map+1)] = 0;
			}
		}
		
		//for later comparison
		memcpy(stateCopy, gs, sizeof(struct gameState));
		
		//perform function
		returnValue = isGameOver(gs);

		//compare states
		if (memcmp( gs, stateCopy, sizeof(struct gameState)) != 0) {
			printf("Modification detected in state!\r\n");
			numberOfErrors++;
		} else {
			if ((returnValue != 1) && ((depletedSupplies(gs) >= 3) || (gs->supplyCount[province] == 0))) {
				printf("State meets criteria for game over, but game over not declared!\r\n");
				printf("returnValue = %d, depletedSupplies = %d, supplyCount[province] = %d\r\n", returnValue, depletedSupplies(gs), gs->supplyCount[province] );
				numberOfErrors++;
			}
			if ((returnValue == 1) && ((depletedSupplies(gs) < 3) && (gs->supplyCount[province] != 0))) {
				printf("Game over declared, but state does not meet criteria!\r\n");
				printf("returnValue = %d, depletedSupplies = %d, supplyCount[province] = %d\r\n", returnValue, depletedSupplies(gs), gs->supplyCount[province] );
				numberOfErrors++;
			}
		
		}
		

	}	
	printf("Unit Test 3 Complete\r\n");
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

int depletedSupplies(struct gameState * gs) {
	int i;
	int count = 0;
	for (i = 0; i <= treasure_map; i++) {
		if (gs->supplyCount[i] == 0) {
			count++;
		}
	}
	
	return count;
}
