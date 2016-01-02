#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int unittest2()
{

	int seed = 2500;
	int players = 2;
	int result;
	int i, j, k;
	int whichCard;
	int failedtests = 0;
	int hand[10] = { adventurer, embargo, steward, cutpurse, outpost
		, mine, smithy, remodel, great_hall, feast };
	struct gameState testState;
	memset(&testState, 23, sizeof(struct gameState));
	//Initialize the game
	initializeGame(players, hand, seed, &testState);
	
	printf("Testing buyCard(): \n");

	printf("-----------------------------------------\n");
	printf("Testing when no buys are left\n");
	//test when no buys left
	for (i = 0; i < players; i++)
	{
		/*memset(&testState, 23, sizeof(struct gameState));
		//Initialize the game
		initializeGame(players, hand, seed, &testState);*/
		testState.numBuys = 0;

		//set number of coins beyond what it would take to buy every card
		testState.coins = 1000;
		printf("\nPlayer: %d | Coins available: %d | Buys available: %d\n", i, testState.coins, testState.numBuys);
		printf("\n");

		for (whichCard = curse; whichCard < treasure_map; whichCard++)
		{
			printf("\nHand before buy: ");
			for (j = 0; j < numHandCards(&testState); j++)
				printf("%d, ", handCard(j, &testState));
			
			printf("\nBuying %d\n", whichCard);
			result = buyCard(whichCard, &testState);
			if (result < 0)
			{
				printf("PASS: Not enough buys available\n");
			}
			else
			{
				printf("FAIL: Bought card %d\n", whichCard);
				failedtests++;
			}
			printf("Hand after buy: ");
			for (j = 0; j < numHandCards(&testState); j++)
				printf("%d, ", handCard(j, &testState));
			printf("\n");
		}
	}


	printf("\n");
	printf("-----------------------------------------\n");
	printf("\n");
	printf("\n");
	printf("-----------------------------------------\n");
	printf("Testing when no coins are left\n");
	//test when no coins left
	for (i = 0; i < players; i++)
	{
		/*memset(&testState, 23, sizeof(struct gameState));
		//Initialize the game
		initializeGame(players, hand, seed, &testState);*/
		//set number of buys beyond what it would take to buy every card
		testState.numBuys = 50;

		//set number of coins to -1 (because some cards cost 0)
		testState.coins = -1;
		printf("\nPlayer: %d | Coins available: %d | Buys available: %d\n", i, testState.coins, testState.numBuys);
		printf("\n");

		for (whichCard = curse; whichCard < treasure_map; whichCard++)
		{
			printf("\nHand before buy: ");
			for (j = 0; j < numHandCards(&testState); j++)
				printf("%d, ", handCard(j, &testState));

			printf("\nBuying %d\n", whichCard);
			result = buyCard(whichCard, &testState);
			if (result < 0)
			{
				printf("PASS: Not enough coins available\n");
			}
			else
			{
				printf("FAIL: Bought card %d\n", whichCard);
				failedtests++;
			}
			printf("Hand after buy: ");
			for (j = 0; j < numHandCards(&testState); j++)
				printf("%d, ", handCard(j, &testState));
			printf("\n");
		}
	}
	printf("\n");
	printf("-----------------------------------------\n");
	printf("\n");
	printf("\n");
	printf("-----------------------------------------\n");
	printf("Testing when not enough of that card are left\n");
	//test when not enough cards left
	for (i = 0; i < players; i++)
	{
		/*memset(&testState, 23, sizeof(struct gameState));
		//Initialize the game
		initializeGame(players, hand, seed, &testState);*/
		//set number of buys beyond what it would take to buy every card
		testState.numBuys = 50;

		//set number of coins to -1 (because some cards cost 0)
		testState.coins = 5000;

		//set number of each card to be zero
		for(whichCard = curse; whichCard < treasure_map; whichCard++)
		{
			testState.supplyCount[whichCard] = 0;
		}
		printf("\nPlayer: %d | Coins available: %d | Buys available: %d\n", i, testState.coins, testState.numBuys);
		printf("\n");

		for (whichCard = curse; whichCard < treasure_map; whichCard++)
		{
			
			printf("\nAmount of Card #%d available: %d\n", whichCard, supplyCount(whichCard, &testState));
			printf("Hand before buy: ");
			for (j = 0; j < numHandCards(&testState); j++)
				printf("%d, ", handCard(j, &testState));

			printf("\nBuying %d\n", whichCard);
			result = buyCard(whichCard, &testState);
			if (result < 0)
			{
				printf("PASS: Not enough of Card #%d available\n", whichCard);
			}
			else
			{
				printf("FAIL: Bought card %d\n", whichCard);
				failedtests++;
			}
			printf("Hand after buy: ");
			for (j = 0; j < numHandCards(&testState); j++)
				printf("%d, ", handCard(j, &testState));
			printf("\n");
		}
	}

	printf("-----------------------------------------\n");
	printf("\n");
	printf("\n");
	printf("-----------------------------------------\n");
	printf("Testing else condition - successful buys\n");

	
	for (i = 0; i < players; i++)
	{
		
		//set number of buys beyond what it would take to buy every card
		testState.numBuys = 50;

		//set number of coins to -1 (because some cards cost 0)
		testState.coins = 5000;

		//set number of each card to be zero
		for (whichCard = curse; whichCard < treasure_map; whichCard++)
			testState.supplyCount[whichCard] = 20;
	
		//discard all cards
		for (k = 0; numHandCards(&testState); k++) {
			discardCard(k, 0, &testState, 0);
			discardCard(k, 1, &testState, 0);
		}
		printf("\n");
		printf("\nPlayer: %d | Coins available: %d | Buys available: %d\n", i, testState.coins, testState.numBuys);
	
		for (whichCard = curse; whichCard < treasure_map; whichCard++)
		{

			printf("\nAmount of Card #%d available: %d\n", whichCard, supplyCount(whichCard, &testState));
			printf("Hand before buy: ");
			for (j = 0; j < numHandCards(&testState); j++)
				printf("%d, ", handCard(j, &testState));

			printf("\nBuying %d\n", whichCard);
			result = buyCard(whichCard, &testState);
			if (result == 0)
			{
				printf("PASS: Bought card #%d\n", whichCard);
			}
			else
			{
				printf("FAIL: Did not buy card #%d\n", whichCard);
				failedtests++;
			}
			printf("Hand after buy: ");
			for (j = 0; j < numHandCards(&testState); j++)
				printf("%d, ", handCard(j, &testState));
			printf("\nAmount of Card #%d available after buy: %d\n", whichCard, supplyCount(whichCard, &testState));
			printf("\n");

		}
	}

	printf("-----------------------------------------\n");

	printf("Failed tests: %d\n", failedtests);
	printf("\n");
	return 0;
}