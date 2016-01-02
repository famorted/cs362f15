// Name: Billy Kerns
// Assignment 3
// unittest3.c
// Testing the discardCard() function

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>

#define NOISY_TEST 0

int checkDiscard(int handPosition, int p, struct gameState *post, int trashFlag, int n);

int main(){
	int trashFlag;
	int handPosition;
	int errorCode = 0;
	struct gameState G;
	int n;
	int i;
	int r;
	int p;
	enum CARD randomCard[27] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens,
							mine,remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse,
							embargo, outpost, salvager, sea_hag, treasure_map};
	srand(time(NULL));
	printf("Testing discardCard():\n");
	for(n = 0; n < 1000; n++){
		for(i = 0; i < sizeof(struct gameState); i++){//fill gameState with junk
			((char*)&G)[i] = (rand() % (256));
		}
		trashFlag = (rand() % (2));
		p = (rand() % (2));
		G.deckCount[p] = (rand() % (MAX_DECK+1));//player deckCount = between 0 and MAX_DECK
		G.discardCount[p] = (rand() % (MAX_DECK+1));//player discardCount = between 0 and MAX_DECK
		G.playedCardCount = (rand() % (MAX_DECK));//played card count = between 0 and MAX_DECK - 1. -1 because it could be incremented after function
		G.handCount[p] = (rand() % (MAX_HAND))+1;//player handCount = between 0 and MAX_HAND
		handPosition = (rand() % (G.handCount[p]));
		for(r = 0; r < G.handCount[p]; r++){
			int randomInt = (rand() % (26));
			G.hand[p][r] = randomCard[randomInt];//player hand = random card
		}
		for(r = 0; r < G.playedCardCount; r++){
			int randomInt = (rand() % (26));
			G.playedCards[r] = randomCard[randomInt];//played card = random card
		}
		errorCode += checkDiscard(handPosition, p, &G, trashFlag, n);
	}
	if(errorCode == 0){
		printf("All tests passed\n");
	}
	else{
		#if(NOISY_TEST != 1)
		printf("At least one test failed.  Set NOISY_TEST to 1 for more information\n");
		#endif
	}
	return 0;
}

int checkDiscard(int handPosition, int p, struct gameState *post, int trashFlag, int n){
	struct gameState pre;
	int errorCount = 0;
	memcpy (&pre, post, sizeof(struct gameState));
	if(discardCard(handPosition, p, post, trashFlag) != 0){//Test 1: function returns correctly
		#if(NOISY_TEST == 1)
		printf("Test #%d failed.\n", n);
		printf("DiscardCard function failed\n");
		#endif
		errorCount++;
	}
	
	if(pre.handCount[p] > 1 && post->hand[p][post->handCount[p]] != -1){//pre handCount is greater than 1 so post hand should end with -1
		#if(NOISY_TEST == 1)
		printf("Test #%d failed.\n", n);
		printf("The player's hand does not end with -1.\n");
		#endif
		errorCount++;
	}
	if(post->handCount[p] != pre.handCount[p]-1){//post should be one less than pre since post has been decremented
		#if(NOISY_TEST == 1)
		printf("Test #%d failed.\n", n);
		printf("The player's hand count was not decremented.\n");
		#endif
		errorCount++;
	}
	if(trashFlag < 1 && post->playedCardCount != pre.playedCardCount + 1){//post should have one additional played card if trashFlag is less than one
		#if(NOISY_TEST == 1)
		printf("Test #%d failed.\n", n);
		printf("Played card count was not incremented\n");
		#endif
		errorCount++;
	}
	if(pre.discardCount[p] != post->discardCount[p] - 1){//discard count should have been decremented
		#if(NOISY_TEST == 1)
		printf("Test #%d failed.\n", n);
		printf("Discard count was not incremented\n");
		#endif
		errorCount++;
	}

	if (trashFlag < 1){
   		pre.playedCards[pre.playedCardCount] = pre.hand[p][handPosition]; 
    		pre.playedCardCount++;
    	}
	pre.hand[p][handPosition] = -1;

	if ( handPosition == (pre.handCount[p] - 1) ){
     		pre.handCount[p]--;
    	}
  	else if ( pre.handCount[p] == 1 ){// Never happens. Cannot happen. Don't waste your time
      		pre.handCount[p]--;
    	}
  	else{
     		pre.hand[p][handPosition] = pre.hand[p][ (pre.handCount[p] - 1)];
      		pre.hand[p][pre.handCount[p] - 1] = -1;
      		pre.handCount[p]--;
    	}

    	if(memcmp(&pre, post, sizeof(struct gameState)) != 0){//Test 5: Pre and post should be identical
		#if(NOISY_TEST == 1)
		printf("Test #%d failed.\n", n);
		printf("Memcmp failed\n");	
		#endif
		errorCount++;
	}
	return errorCount;
}
