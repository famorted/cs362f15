// Name: Billy Kerns
// File: cardtest1.c
// smithy card

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>

#define NOISY_TEST 0

int checkSmithy(int p, struct gameState *pre, int turn, int handPos, int n);

int main(){
	struct gameState G;
	int n;
	int p;
	int r;
	int t;
	int u;
	int turn;
	int errorCount = 0;
	srand(time(NULL));
	enum CARD randomCard[27] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens,
							mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse,
							embargo, outpost, salvager, sea_hag, treasure_map};
	printf("Testing Smithy Card\n");
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	for(n = 0; n < 500; n++){
		p = (rand() % (MAX_PLAYERS-1));//players between 0 and MAX_PLAYERS
		initializeGame(p+1, k, 1000, &G);
		for(t = 0; t < sizeof(struct gameState); t++){//fill gameState with junk
			((char*)&G)[t] = (rand() % (256));
		}
		for(u = 0; u <= p; u++){//cycle through each player
			G.deckCount[u] = (rand() % (MAX_DECK-4)+5);//count between 5 and MA_DECK
			G.discardCount[u] = (rand() % (MAX_DECK-4)+5);
			G.handCount[u] = (rand() % (MAX_HAND-4)+5);

			for(r = 0; r < G.deckCount[u]; r++){
				int randomInt = (rand() % (25));//can't be treasure map
				G.deck[u][r] = randomCard[randomInt];
			}
			for(r = 0; r < G.discardCount[u]; r++){
				int randomInt = (rand() % (25));
				G.discard[u][r] = randomCard[randomInt];
			}
			for(r = 0; r < G.handCount[u]; r++){
				int randomInt = (rand() % (25));
				G.hand[u][r] = randomCard[randomInt];
			}
			G.hand[u][G.handCount[u]-1] = randomCard[13];//end of hand = smithy card
			G.hand[u][G.handCount[u]-((G.handCount[u]-1) / 2)] = baron;//middle of hand = baron
			G.deck[u][G.deckCount[u]-1] = randomCard[26];//last card in deck = treasure_map
		}
		G.playedCardCount = (rand() % (MAX_DECK-3));//random played card count
		G.numPlayers = p+1;
		turn =(rand() % (p+1));//set whose turn
		G.whoseTurn = turn;
		errorCount += checkSmithy(p, &G, turn, G.handCount[p]-1, n);
	}
	if(errorCount != 0){
		#if(NOISY_TEST != 1)
		printf("At least 1 test failed.  Define NOISY_TEST to 1 for more information\n");
		#endif
	}
	else{
		printf("All tests passed\n");
	}

	return 0;
}

int checkSmithy(int p, struct gameState *pre, int turn, int handPos, int n){
	struct gameState post;
	memcpy (&post, pre, sizeof(struct gameState));
	int errors = 0;	
	int foundIt;
	int d;
	int bonus;
	int i;
	int q;
	int postCount=0;
	bonus = 0;

	smithyCard(turn, &post, handPos);

	if(post.handCount[turn] != pre->handCount[turn] + 2){//hand count should be incremented 3 times and then decremented when smithy is discarded
		#if(NOISY_TEST == 1)
		printf("Test # %d failed. Hand count was not incremented 3 times\nExpected: handCount = %d	Actual: handCount = %d\n\n", n, pre->handCount[turn]+2, post.handCount[turn]);
		#endif
		errors++;
	}
	if(post.deckCount[turn] != pre->deckCount[turn] - 3 && pre->deckCount[turn] > 3){//deck count should be 3 less than pre unless deck had less than 3 to begin with
		#if(NOISY_TEST == 1)
		printf("Test # %d failed. Deck count was not decremented 3 times\nExpected: deckCount = %d	Actual: deckCount = %d\n\n", n, pre->deckCount[turn]-3, post.deckCount[turn]);
		#endif
		errors++;
	}

	for(i = 0; i < 3; i++){//Check to see if cards received are now in hand 
		foundIt=0;
		for(d = 0; d < pre->deckCount[turn]; d++){
			if(post.hand[turn][post.handCount[turn] - i-1] == pre->deck[turn][d]){
				foundIt++;
			}
		}
		for(d = 0; d < pre->discardCount[turn]; d++){
			if(post.hand[turn][post.handCount[turn] - i-1] == pre->discard[turn][d]){ 
				foundIt++;
			}
		}
		for(d = 0; d < pre->handCount[turn]; d++){
			if(post.hand[turn][post.handCount[turn] - i-1] == pre->hand[turn][d]){
				foundIt++;
			}
		}

		if(foundIt < 1 && post.hand[turn][post.handCount[turn] - i-1] != 13){//card was not found and last card in hand hasn't changed
			#if(NOISY_TEST == 1)
			printf("Test # %d failed. Card received was not in deck\n\n", n);
			#endif
			errors++;
		}
	}
	for(i = 0; i < pre->numPlayers; i++){//check that non current players' stuff has not been changed
		if(post.handCount[i] != pre->handCount[i]){
			if(i != turn){
				#if(NOISY_TEST == 1)
				printf("Test # %d failed. Other players hand counts were changed\nExpected: Player %d handCount = %d	Actual: Player %d handCount = %d\n\n", n, i, pre->handCount[i], i, post.handCount[i]);
				#endif
				errors++;
			}
		}
	}
	for(i = 0; i < pre->numPlayers; i++){
		if(post.discardCount[i] != pre->discardCount[i]){
			if(i != turn){
				#if(NOISY_TEST == 1)
				printf("Test # %d failed. Other players discard counts were changed\nExpected: Player %d discardCount = %d	Actual: Player %d discardCount = %d\n\n", n, i, pre->discardCount[i], i, post.discardCount[i]);
				#endif
				errors++;
			}
		}
	}
	for(i = 0; i < pre->numPlayers; i++){
		if(post.deckCount[i] != pre->deckCount[i]){
			if(i != turn){
				#if(NOISY_TEST == 1)
				printf("Test # %d failed. Other players deck counts were changed\nExpected: Player %d deckCount = %d	Acutal: Player %d deckCount = %d\n\n", n, i, pre->deckCount[i], i, post.deckCount[i]);
				#endif
				errors++;
			}
		}
	}
	for(i = 0; i < pre->numPlayers; i++){
		if(post.hand[i][post.handCount[i]-((post.handCount[i]-1) / 2)] != baron){//check for card manually put in hand
			if(i != turn){
				#if(NOISY_TEST == 1)
				printf("Test #: %d failed\n", n);
				printf("Expected: Hand of unused player to be the same	Actual: Hand of unused player is not the same\n");
				#endif
				errors++;
			}
		}
	}
	for(i = 0; i < pre->numPlayers; i++){//check for card manually put in deck
		postCount = 0;
		for(q = 0; q < post.deckCount[i]; q++){
			if(post.deck[i][q] == treasure_map){
				postCount++;
			}
		}
		if(1 != postCount){
			if(i != turn){
				#if(NOISY_TEST == 1)
				printf("Test #: %d failed\n", n);
				printf("Expected: Player %d treasure_map = 1	Actual: Player %d treasure_map = %d\n", i, i, postCount);
				#endif
				errors++;
			}
		}
	}
	if(post.playedCardCount != pre->playedCardCount + 1){
		#if(NOISY_TEST == 1)
		printf("Test # %d failed. Card was not added to played card count\nExpected: playedCardCount = %d	Actual: playedCardCount = %d\n\n", n, pre->playedCardCount+1, post.playedCardCount);
		#endif
		errors++;
	}
	return errors;	
}
