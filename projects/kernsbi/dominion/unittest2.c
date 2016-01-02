// Name: Billy Kerns
// Assignment 3
// unittest2.c
// Testing the fullDeckCount() function

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>

#define NOISY_TEST 0

int main(){
	struct gameState G;
	int n;
	int i;
	int p;
	int r;
	int errorCount = 0;
	int newCount;
	int count;
	srand(time(NULL));
	enum CARD randomCard[27] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens,
							mine,remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse,
							embargo, outpost, salvager, sea_hag, treasure_map};
	printf("Testing fullDeckCount():\n");
	for(n = 0; n < 1000; n++){
		count = 0;
		for(i = 0; i < sizeof(struct gameState); i++){//fill gameState with junk
			((char*)&G)[i] = (rand() % (256));
		}
		p = (rand() % (2));
		int randomCardToPick = (rand() % (26));//random card to count
		int countArray[p];
		memset(countArray,0,sizeof(countArray));
		G.deckCount[p] = (rand() % (MAX_DECK+1));//player deckCount = to random between 0 and MAX_DECK
		G.discardCount[p] = (rand() % (MAX_DECK+1));//player discardCount = to random between 0 and MAX_DECK
		G.handCount[p] = (rand() % (MAX_HAND+1));//player handCount = to random between 0 and MAX_HAND
		for(r = 0; r < G.deckCount[p]; r++){
			int randomInt = (rand() % (26));
			G.deck[p][r] = randomCard[randomInt];//player deck = random card
			if(randomInt == (randomCardToPick)){//increment local count of card if it equals randomCardToPick for comparison to fullDeckCount()
				count++;
			}
		}
		for(r = 0; r < G.discardCount[p]; r++){
			int randomInt = (rand() % (26));
			G.discard[p][r] = randomCard[randomInt];//player discard = random card
			if(randomInt == (randomCardToPick)){//increment local count of card if it equals randomCardToPick for comparison to fullDeckCount()
				count++;
			}
		}
		for(r = 0; r < G.handCount[p]; r++){
			int randomInt = (rand() % (26));
			G.hand[p][r] = randomCard[randomInt];//player hand = random card
			if(randomInt == (randomCardToPick)){//increment local count of card if it equals randomCardToPick for comparison to fullDeckCount()
				count++;
			}
		}
		
		struct gameState post;
		memcpy (&post, &G, sizeof(struct gameState));
		newCount = fullDeckCount(p, randomCardToPick, &post);
		if(newCount != count){//check local count against count returned by fullDeckCount()
			#if(NOISY_TEST == 1)
			printf("Test #:	%d failed\n", n);
			#endif
			errorCount++;
		}
		else if(memcmp(&post, &G, sizeof(struct gameState)) != 0){//Compare everything else
			#if(NOISY_TEST == 1)
			printf("Test #:	%d failed", n);
			printf("Memcmp failed");
			#endif
			errorCount++;
		}
		#if(NOISY_TEST == 1)
		printf("%d:	Expected count: %d	Actual count: %d\n", n, count, newCount);
		#endif
	}
	
	if(errorCount == 0){
		printf("All tests passed\n");
	}
	else{
		#if(NOISY_TEST != 1)
		printf("At least 1 test failed.  Set NOISY_TEST to 1 for more information.\n");
		#endif
	}
	return 0;
}
