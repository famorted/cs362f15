#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define CARD_COUNTING 0

int unittest3()
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
	
	printf("Testing gainCard(): \n");
	printf("-----------------------------------------\n");
	printf("Testing gains when they go to discard\n");
	//test when cards go to discard
	//set number of each card to be > zero
	for (whichCard = curse; whichCard < treasure_map; whichCard++)
	{
		if(supplyCount(whichCard, &testState) <= 0)
			testState.supplyCount[whichCard] += 5;
	}
	for (i = 0; i < players; i++)
	{

		printf("\nPlayer: %d\n", i);
		printf("\n");

		for (whichCard = curse; whichCard < treasure_map; whichCard++)
		{

			printf("Discard count before gainCard(): %d\n", testState.discardCount[i]);
#if CARD_COUNTING
			printf("Amount of Card #%d available: %d\n", whichCard, supplyCount(whichCard, &testState));
#endif
			printf("Calling gainCard() on card %d\n", whichCard);
			result = gainCard(whichCard, &testState, 0, i);
			printf("gainCard() returns %d\n", result);
			if (result == 0)
			{
				printf("PASS: Added to discard\n", whichCard);
			}
			else
			{
				printf("FAIL: Not added %d\n", whichCard);
				failedtests++;
			}
			printf("Discard count after gainCard(): %d\n", testState.discardCount[i]);
#if CARD_COUNTING
			printf("Amount of Card #%d available after call: %d\n", whichCard, supplyCount(whichCard, &testState));
#endif

			printf("\n");
		}
	}
	printf("-----------------------------------------\n");
	printf("\n");
	printf("\n");
	printf("-----------------------------------------\n");
	printf("Testing gains when they go to deck\n");
	//test when cards go to deck

	//set number of each card to be > zero
	for (whichCard = curse; whichCard < treasure_map; whichCard++)
	{
		if (supplyCount(whichCard, &testState) <= 0)
			testState.supplyCount[whichCard] += 5;
	}
	for (i = 0; i < players; i++)
	{

		printf("\nPlayer: %d\n", i);
		printf("\n");

		for (whichCard = curse; whichCard < treasure_map; whichCard++)
		{
			printf("Deck count before gainCard(): %d\n", testState.deckCount[i]);
#if CARD_COUNTING
			printf("Amount of Card #%d available: %d\n", whichCard, supplyCount(whichCard, &testState));
#endif
			printf("Calling gainCard() on card %d\n", whichCard);
			result = gainCard(whichCard, &testState, 1, i);
			printf("gainCard() returns %d\n", result);
			if (result == 0)
			{
				printf("PASS: Added to deck\n", whichCard);
			}
			else
			{
				printf("FAIL: Not added %d\n", whichCard);
				failedtests++;
			}
			printf("Deck count after gainCard(): %d\n", testState.deckCount[i]);
#if CARD_COUNTING
			printf("Amount of Card #%d available after call: %d\n", whichCard, supplyCount(whichCard, &testState));
#endif
			printf("\n");
		}
	}

	printf("-----------------------------------------\n");
	printf("\n");
	printf("\n");
	printf("-----------------------------------------\n");

	printf("Testing gains when they go to hand\n");
	//test when cards go to hand

	//set number of each card to be > zero
	for (whichCard = curse; whichCard < treasure_map; whichCard++)
	{
		if (supplyCount(whichCard, &testState) <= 0)
			testState.supplyCount[whichCard] += 5;
	}
	for (i = 0; i < players; i++)
	{

		printf("\nPlayer: %d\n", i);
		printf("\n");

		for (whichCard = curse; whichCard < treasure_map; whichCard++)
		{
			printf("Hand count before gainCard(): %d\n", testState.handCount[i]);
#if CARD_COUNTING
			printf("Amount of Card #%d available: %d\n", whichCard, supplyCount(whichCard, &testState));
#endif
			printf("Calling gainCard() on card %d\n", whichCard);
			result = gainCard(whichCard, &testState, 2, i);
			printf("gainCard() returns %d\n", result);
			if (result == 0)
			{
				printf("PASS: Added to deck\n", whichCard);
			}
			else
			{
				printf("FAIL: Not added %d\n", whichCard);
				failedtests++;
			}
			printf("Hand count after gainCard(): %d\n", testState.handCount[i]);
#if CARD_COUNTING
			printf("Amount of Card #%d available after call: %d\n", whichCard, supplyCount(whichCard, &testState));
#endif
			printf("\n");
		}
	}

	printf("-----------------------------------------\n");
	printf("\n");
	printf("\n");
	printf("-----------------------------------------\n");
	printf("Testing when not enough of that card are left\n");
	//set number of each card to be zero
	for (whichCard = curse; whichCard < treasure_map; whichCard++)
	{
		testState.supplyCount[whichCard] = 0;
	}
	//test when not enough cards left
	for (i = 0; i < players; i++)
	{

		printf("\nPlayer: %d\n", i);
		printf("\n");

		for (whichCard = curse; whichCard < treasure_map; whichCard++)
		{

			printf("\nAmount of Card #%d available: %d\n", whichCard, supplyCount(whichCard, &testState));
			printf("Hand before gainCard(): ");
			for (j = 0; j < numHandCards(&testState); j++)
				printf("%d, ", handCard(j, &testState));

			printf("\ncalling gainCard() on card %d\n", whichCard);
			result = gainCard(supplyCount(whichCard, &testState), &testState, 2, i);
			if (result < 0)
			{
				printf("PASS: Not enough of Card #%d available\n", whichCard);
			}
			else
			{
				printf("FAIL: Bought card %d\n", whichCard);
				failedtests++;
			}
			printf("Hand after gainCard(): ");
			for (j = 0; j < numHandCards(&testState); j++)
				printf("%d, ", handCard(j, &testState));
			printf("\n");
		}
	}

	printf("-----------------------------------------\n");
	printf("\n");

	printf("Failed tests: %d\n", failedtests);
	printf("\n");
	return 0;
}