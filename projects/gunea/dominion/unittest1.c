#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int unittest1()
{
	int seed = 2500;
	int players = 2;
	int maxBonus = 20;
	int c, i, j, k;
	int failedtests = 0;
	int hand[10] = { adventurer, embargo, steward, cutpurse, outpost
		, mine, smithy, remodel, great_hall, feast };
	struct gameState testState;
	int maxHandCount = 5;
	// arrays of all coppers, silvers, and golds
	int coppers[MAX_HAND];
	int silvers[MAX_HAND];
	int golds[MAX_HAND];
	for (c = 0; c < MAX_HAND; c++)
	{
		coppers[c] = copper;
		silvers[c] = silver;
		golds[c] = gold;
	}
	printf("Testing updateCoins(): \n");

	printf("-----------------------------------------\n");
	printf("Testing with a hand full of the same treasure cards\n");
	for (i = 0; i < players; i++)
	{
		for (j = 0; j < maxHandCount; j++)
		{
			for (k = 0; k < maxBonus; k++)
			{
				printf("Player: %d | Treasures in hand: %d | Bonus: %d\n", i, j, k);

				memset(&testState, 23, sizeof(struct gameState));
				//Initialize the game
				initializeGame(players, hand, seed, &testState);

				//set the hand count
				testState.handCount[i] = j;

				printf("Testing coppers\n");
				//set all cards to coppers
				memcpy(testState.hand[i], coppers, (sizeof(int)*j));

				//call the function
				updateCoins(i, &testState, k);
				
				//Print results
				if (testState.coins == (j * 1 + k))
					printf("PASS: ");
				else {
					printf("FAIL: ");
					failedtests++;
				}
				printf("Expected = %d | Actual = %d\n", j * 1 + k, testState.coins);


				printf("Testing silvers\n");
				//set all cards to silvers
				memcpy(testState.hand[i], silvers, (sizeof(int)*j));

				//call the function
				updateCoins(i, &testState, k);

				//Print results
				if (testState.coins == (j * 2 + k))
					printf("PASS: ");
				else {
					printf("FAIL: ");
					failedtests++;
				}
				printf("Expected = %d | Actual = %d\n", j * 2 + k, testState.coins);

				printf("Testing golds\n");
				//set all cards to golds
				memcpy(testState.hand[i], golds, (sizeof(int)*j));

				//call the function
				updateCoins(i, &testState, k);

				//Print results
				if (testState.coins == (j * 3 + k))
					printf("PASS: ");
				else {
					printf("FAIL: ");
					failedtests++;
				}
				printf("Expected = %d | Actual = %d\n", j * 3 + k, testState.coins);
			}
		}
	}

	printf("\n");
	printf("Failed tests: %d", failedtests);
	printf("\n");
	printf("-----------------------------------------\n");
	printf("\n");










	return 0;
}