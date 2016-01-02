// Name: Billy Kerns
// Assignment 3
// unittest1.c
// Testing the scoreFor() function
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>

#define NOISY_TEST 0

int checkScoreFor(int player, struct gameState *post, int *preScore, int *postScore);

int main(){
	struct gameState G;
	int n;
	int i;
	int p;
	int r;
	int errorFlag = 0;
	int checkResult;
	int preScore = 0;
	int postScore = 0;
	enum CARD randomCard[27] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens,
							mine,remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse,
							embargo, outpost, salvager, sea_hag, treasure_map};
	srand(time(NULL));
	
	printf("Testing scoreFor():\n");
	for(n = 0; n < 1000; n++){
		for(i = 0; i < sizeof(struct gameState); i++){//fill gameState with junk
			((char*)&G)[i] = (rand() % (256));
		}
		p = (rand() % (1));//players between 0 and 1
		G.deckCount[p] = (rand() % (MAX_DECK+1));//set deckCount at player = to number between 0 and MAX_DECK
		G.discardCount[p] = (rand() % (MAX_DECK+1));//set discardCount at player = to number between 0 and MAX_DECK
		G.handCount[p] = (rand() % (MAX_HAND+1));//set handCount at player = to number between 0 and MAX_HAND
		for(r = 0; r < G.deckCount[p]; r++){
			int randomInt = (rand() % (26));
			G.deck[p][r] = randomCard[randomInt];//player deck = to random card
		}
		for(r = 0; r < G.discardCount[p]; r++){
			int randomInt = (rand() % (26));
			G.discard[p][r] = randomCard[randomInt];//player discard = to random card
		}
		for(r = 0; r < G.handCount[p]; r++){
			int randomInt = (rand() % (26));
			G.hand[p][r] = randomCard[randomInt];//player hand = to random card
		}
		checkResult = checkScoreFor(p, &G, &preScore, &postScore);
		if(checkResult == -1){
			#if(NOISY_TEST == 1)
			printf("Failed on test #%d\n", n);
			#endif
			errorFlag++;
		}
		else if(checkResult == -2){
			#if(NOISY_TEST == 1)
			printf("Failed on test #%d\n", n);
			printf("Memcmp failed\n");
			#endif
			errorFlag++;
		}
		#if(NOISY_TEST == 1)
		printf("%d:	Expected: %d	Result:  %d\n", n, preScore, postScore);
		#endif
	}
	if(errorFlag == 0){
		printf("All tests passed\n");
	}
	else{
		#if(NOISY_TEST != 1)
		printf("At least one test failed.  Set NOISY_TEST to 1 for more info\n");
		#endif
	}
	return 0;
}
int checkScoreFor(int player, struct gameState *post, int *preScore, int *postScore){
	struct gameState pre;
	memcpy (&pre, post, sizeof(struct gameState));
	int r;
	*postScore = 0;
	*preScore = 0;
	
	*postScore += scoreFor(player, post);
	for(r = 0; r < pre.deckCount[player]; r++){//for each card in player's deck check for victory card. if found increment score accordingly
		if(pre.deck[player][r] == curse){
			*preScore += -1;
		}
		else if(pre.deck[player][r] == estate){
			*preScore += 1;
		}
		else if(pre.deck[player][r] == duchy){
			*preScore += 3;
		}
		else if(pre.deck[player][r] == province){
			*preScore += 6;
		}
		else if(pre.deck[player][r] == great_hall){
			*preScore += 1;
		}
		else if(pre.deck[player][r] == gardens){
			*preScore += fullDeckCount(player, 0, &pre) / 10;
		}
	}
	for(r = 0; r < pre.discardCount[player]; r++){//for each card in player's discard check for victory card. if found increment score accordingly
		if(pre.discard[player][r] == curse){
			*preScore += -1;
		}
		else if(pre.discard[player][r] == estate){
			*preScore += 1;
		}
		else if(pre.discard[player][r] == duchy){
			*preScore += 3;
		}
		else if(pre.discard[player][r] == province){
			*preScore += 6;
		}
		else if(pre.discard[player][r] == great_hall){
			*preScore += 1;
		}
		else if(pre.discard[player][r] == gardens){
			*preScore += fullDeckCount(player, 0, &pre) / 10;
		}
	}
	for(r = 0; r < pre.handCount[player]; r++){//for each card in player's hand check for victory card. if found increment score accordingly
		if(pre.hand[player][r] == curse){
			*preScore += -1;
		}
		else if(pre.hand[player][r] == estate){
			*preScore += 1;
		}
		else if(pre.hand[player][r] == duchy){
			*preScore += 3;
		}
		else if(pre.hand[player][r] == province){
			*preScore += 6;
		}
		else if(pre.hand[player][r] == great_hall){
			*preScore += 1;
		}
		else if(pre.hand[player][r] == gardens){
			*preScore += fullDeckCount(player, 0, &pre) / 10;
		}
	}
	if(*preScore != *postScore){//Check for equality
		return -1;
	}
 	else if(memcmp(&pre, post, sizeof(struct gameState)) != 0){//check everything else
		return -2;
	}
	else{
		return 0;
	}
}
