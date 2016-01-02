// Name: Billy Kerns
// File: cardtest2.c
// adventurer

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>

#define NOISY_TEST 0

int checkAdventure(struct gameState *pre, int currentPlayer, int tempHand[MAX_HAND], int z, int cardDrawn, int n);

int main(){
	struct gameState G;
	int n;
	int p;
	int r;
	int t;
	int cardDrawn;
	int u;
	int tempHand[MAX_HAND];
	int turn;
	int errorCount = 0;
	cardDrawn = -1;
	srand(time(NULL));
	enum CARD randomCard[27] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens,
							mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse,
							embargo, outpost, salvager, sea_hag, treasure_map};
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	printf("Testing Adventurer Card\n");
	for(n = 0; n < 10000; n++){
		p = (rand() % (MAX_PLAYERS-1));
		initializeGame(p+1, k, 1000, &G);
		for(t = 0; t < sizeof(struct gameState); t++){//fill gameState with junk
			((char*)&G)[t] = (rand() % (256));
		}
		for(u = 0; u <= p; u++){
			G.deckCount[u] = (rand() % (MAX_DECK-4)+5);//player deckCount = between 5 and MAX_DECK
			G.discardCount[u] = (rand() % (MAX_DECK-4)+5);//player discardCount = between 5 and MAX_DECK
			G.handCount[u] = (rand() % (MAX_HAND-4)+5);

			for(r = 0; r < G.deckCount[u]; r++){
				int randomInt = (rand() % (25));
				G.deck[u][r] = randomCard[randomInt];//player deck = random card excluding treasure_map
			}
			for(r = 0; r < G.discardCount[u]; r++){
				int randomInt = (rand() % (25));
				G.discard[u][r] = randomCard[randomInt];
			}
			for(r = 0; r < G.handCount[u]; r++){
				int randomInt = (rand() % (25));
				G.hand[u][r] = randomCard[randomInt];
			}
			G.hand[u][G.handCount[u]-1] = randomCard[7];//last card in hand is adventurer
			G.deck[u][G.deckCount[u]-1] = randomCard[26];//last card in deck = treasure_map.  For testing that other players deck's were not changed

		}
		G.numPlayers = p + 1;
		turn = (rand() % (p+1));
		G.whoseTurn = turn;
		errorCount += checkAdventure(&G, turn, tempHand, 0, cardDrawn, n);
	}
	if(errorCount != 0){
		#if(NOISY_TEST != 1)
		printf("At least 1 test failed.  Define NOISY_TEST to 1 for more information\n");
		#endif
	}
	else {
		printf("All tests passed\n");
	}
	return 0;
}
int checkAdventure(struct gameState *pre, int currentPlayer, int tempHand[MAX_HAND], int z, int cardDrawn, int n){	
	struct gameState post;
	memcpy (&post, pre, sizeof(struct gameState));
	int i;
	int postCount;
	int t;
	int q;
	int funErrors = 0;
	int treasure = 0;
	int postTreasure = 0;
	int deckPreTreasure = 0;
	adventureCard(0, &post, currentPlayer, tempHand, z, cardDrawn);	

	for(i = 0; i < pre->handCount[currentPlayer]; i++){
		if(pre->hand[currentPlayer][i]==copper || pre->hand[currentPlayer][i]==gold || pre->hand[currentPlayer][i]==silver){
			treasure++;//get orriginal amount of treasure in hand
		}
	}

	for(i = 0; i < post.handCount[currentPlayer]; i++){
		if(post.hand[currentPlayer][i]==copper || post.hand[currentPlayer][i]==gold || post.hand[currentPlayer][i]==silver){
			postTreasure++;//get amount of treasure after adventure card has been played
		}
	}
	
	for (t=0; t < pre->numPlayers; t++){//check other players' stats to make sure they haven't changed
		if(pre->handCount[t] != post.handCount[t]){
			if(t != currentPlayer){//if it's current player their stuff is probably different
				#if(NOISY_TEST == 1)
				printf("Test #: %d failed\n", n);
				printf("Expected: Player %d handCount = %d	Actual: Player %d handCount = %d\n", t, pre->handCount[t], t, post.handCount[t]);
				#endif
				funErrors++;
			}
		}
		if(pre->discardCount[t] != post.discardCount[t]){
			if(t != currentPlayer){
				#if(NOISY_TEST == 1)
				printf("Test #: %d failed\n", n);
				printf("Expected: Player %d discardCount = %d	Actual: Player %d discardCount = %d\n", t, pre->discardCount[t], t, post.discardCount[t]);
				#endif
				funErrors++;
			}
		}
		if(pre->deckCount[t] != post.deckCount[t]){
			if(t != currentPlayer){
				#if(NOISY_TEST == 1)
				printf("Test #: %d failed\n", n);
				printf("Expected: Player %d deckCount = %d	Actual: Player %d deckCount = %d\n", t, pre->deckCount[t], t, post.deckCount[t]);
				#endif
				funErrors++;
			}
		}
		postCount = 0;
		for(q = 0; q < post.deckCount[t]; q++){
			if(post.deck[t][q] == treasure_map){
				postCount++;
			}
		}
		if(1 != postCount){
			if(t != currentPlayer){
				#if(NOISY_TEST == 1)
				printf("Test #: %d failed\n", n);
				printf("Expected: Player %d treasure_map = 1	Actual: Player %d treasure_map = %d\n", t, t, postCount);
				#endif
				funErrors++;
			}
		}
	}
	if(treasure+2 != postTreasure){//possibly not 2 treasure cards in player's deck or discard
		for(i=0; i < pre->deckCount[currentPlayer]; i++){
			if(pre->deck[currentPlayer][i]==copper || pre->deck[currentPlayer][i]==silver || pre->deck[currentPlayer][i]==gold){
				deckPreTreasure++;//check to see how many treasure cards are in deck
			}
		}
		for(i=0; i < pre->discardCount[currentPlayer]; i++){
			if(pre->discard[currentPlayer][i]==copper || pre->discard[currentPlayer][i]==silver || pre->discard[currentPlayer][i]==gold){
				deckPreTreasure++;//check to see how many treasure cards are in discard
			}
		}
		if(deckPreTreasure >= 2){//if we found more than two treasure then we have an error
			if(post.handCount[currentPlayer] != pre->handCount[currentPlayer]+2){
				#if(NOISY_TEST == 1)
				printf("Test #: %d failed\n", n);
				printf("Expected: handCount = %d	Actual: handCount = %d\n", pre->handCount[currentPlayer]+2, post.handCount[currentPlayer]);
				#endif
				funErrors++;
			}
		}
		else if(deckPreTreasure == 1){//if only one treasure is found then player hand count should go up by one
			if(post.handCount[currentPlayer] != pre->handCount[currentPlayer]+1){
				#if(NOISY_TEST == 1)
				printf("Test #: %d failed\n", n);
				printf("Expected: handCount = %d	Actual: handCount = %d\n", pre->handCount[currentPlayer]+1, post.handCount[currentPlayer]);
				#endif
				funErrors++;
			}
		}
		else if(deckPreTreasure !=0){//else something went wrong
			#if(NOISY_TEST == 1)
			printf("Test #: %d failed\n", n);
			printf("Expected: Post treasure = %d	Actual: Post treasure = %d\n", treasure+2, postTreasure);
			#endif
			funErrors++;
		}
	}
	return funErrors;
}
