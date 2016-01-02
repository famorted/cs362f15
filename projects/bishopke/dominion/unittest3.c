// Keenan Bishop
// unittest3.c
// scoreFor() test
// (from template)

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

// the scoreFor function consists of 3 loops
// hand, discard, and deck
// each checks:
// curse: -1 points
// estate: +1 points
// duchy: +3 points
// province : +6 points
// great hall: +1 points
// gardens: +1 for every 10 cards in deck

//so this test will fill some decks with hands of known values and check them

void test_scoreFor(){
	int seed = 1000;
	int numPlayer = 2; //2 players
	int r; 
	//set kindom cards to a normalish set
	int k[10] = {adventurer, council_room, feast, gardens, mine,
			 remodel, smithy, village, baron, great_hall};
	struct gameState G;

	printf ("TESTING scoreFor():\n");

	// initialize a new game for testing
	r = initializeGame(numPlayer, k, seed, &G);
	// insert hands for player
	// this first set of hand, deck, discard contains one of each, value = 10 (no garden bonus)
	int one_of_each_hand[MAX_HAND] = 	{curse, estate, duchy, province, great_hall};
	int one_of_each_discard[MAX_DECK] =	{curse, estate, duchy, province, great_hall, gardens};
	int one_of_each_deck[MAX_DECK] =	{curse, estate, duchy, province, great_hall, gardens};
	// total value = 30
	// insert into player 1 (0) hand and calculate score
	// also insert counts into hand, discard, deck count
	G.handCount[0] = 5;
	G.discardCount[0] = 6;
	G.deckCount[0] = 6;
	// use memcopy to insert sample decks into gamestate
	memcpy(G.hand[0], one_of_each_hand, sizeof(int)*MAX_HAND);
	memcpy(G.discard[0], one_of_each_discard, sizeof(int)*MAX_DECK);
	memcpy(G.deck[0], one_of_each_deck, sizeof(int)*MAX_DECK);
	// calculate sore
	int test_score_1 = scoreFor(0, &G);
	if(test_score_1 == 30){
		printf("PASS: scoreFor: one_of_each returned 30 points\n");
	}
	else{
		printf("FAIL: scoreFor: one_of_each returned %d instead of 10 points\n", test_score_1);
	}


	// empty test
	// everything empty, should return 0;	
	memset(&G, 0, sizeof(struct gameState));
	r = initializeGame(numPlayer, k, seed, &G);
	int empty_hand[MAX_HAND] = {};
	int empty_deck[MAX_HAND] = {};
	// fill values
	G.handCount[0] = 0;
	G.discardCount[0] = 0;
	G.deckCount[0] = 0;
	// use memcopy to insert sample decks into gamestate
	memcpy(G.hand[0], empty_hand, sizeof(int)*MAX_HAND);
	memcpy(G.discard[0], empty_deck, sizeof(int)*MAX_DECK);
	memcpy(G.deck[0], empty_deck, sizeof(int)*MAX_DECK);
	// calculate score
	int test_score_2 = scoreFor(0, &G);
	if(test_score_2 == 0){
		printf("PASS: scoreFor: empty hand, discard, deck returned 0 points\n");
	}
	else{
		printf("FAIL: scoreFor: empty hand, discard, deck returned %d points\n", test_score_2);
	}


	//gardens test
	//reset again
	memset(&G, 0, sizeof(struct gameState));
	r = initializeGame(numPlayer, k, seed, &G);
	//fill with 17 dead cards + 3 gardens, should be 3 points
	int gardens_hand[MAX_HAND] = 	{copper, copper, copper, copper, gardens};
	int gardens_discard[MAX_DECK] =	{silver, gold, silver, gold, copper, copper, copper, gardens};
	int gardens_deck[MAX_DECK] =	{copper, copper, copper, copper, copper, copper, gardens};
	// total value = 2 points
	// insert into player 1 (0) hand and calculate score
	// also insert counts into hand, discard, deck count
	G.handCount[0] = 5;
	G.discardCount[0] = 8;
	G.deckCount[0] = 7;
	// use memcopy to insert sample decks into gamestate
	memcpy(G.hand[0], gardens_hand, sizeof(int)*MAX_HAND);
	memcpy(G.discard[0], gardens_discard, sizeof(int)*MAX_DECK);
	memcpy(G.deck[0], gardens_deck, sizeof(int)*MAX_DECK);
	// calculate sore
	int test_score_3 = scoreFor(0, &G);
	if(test_score_3 == 3){
		printf("PASS: scoreFor: one_of_each returned 3 points\n");
	}
	else{
		printf("FAIL: scoreFor: one_of_each returned %d instead of 3 points\n", test_score_3);
	}
}

int main(){
	test_scoreFor();
	return 0;
}
