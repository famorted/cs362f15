#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

//=================
//TEST VILLAGE CARD
//=================
int main(int argc, char **argv){
	
	printf("\n\nVillage Card Test \n\n");
	printf("Creating new gameState... \n");
	struct gameState *s = newGame();
	int numCards;
	assert(s != NULL);
	printf("gameState created\n\n");
	int k[10] = {outpost, smithy, embargo, baron, adventurer, village, gardens, mine, great_hall, feast};
	printf("Initializing Game...\n");
	initializeGame(2,k,21,s);
	numCards = s->handCount[s->whoseTurn];
	assert(s->outpostPlayed == 0);
	assert(s->phase == 0);
	assert(s->numActions == 1);
	assert(s->numBuys == 1);
	assert(s->playedCardCount == 0);
	assert(s->whoseTurn ==0);
	assert(s->handCount[s->whoseTurn] == numCards);
	printf("Game initialized\n\n");
	int r = cardEffect(village, 0, 0, 0, s, 0, 0);
	printf("Checking if card count correctly decreased...");
	assert(s->handCount[s->whoseTurn] == (numCards));
	printf(" Success!\n");
	printf("Checking return value...");
	assert(r == 0);
	printf(" Success!\n");
	printf("Checking if numActions increased...");
	assert(s->numActions == 3);
	printf(" Success!\n");
	printf("\n\nVillage Card Test Successful!\n\n");
	
	return 0;
	
}