// Name: Billy Kerns
// File: cardtest3.c
// village

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>

#define NOISY_TEST 0

int checkVillage(struct gameState *pre, int currentPlayer, int handPos, int n);

int main(){
	struct gameState G;
	int n;
	int p;
	int r;
	int t;
	int cardDrawn;
	int u;
	int turn;
	int errorCount = 0;
	cardDrawn = -1;
	srand(time(NULL));
	enum CARD randomCard[27] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens,
							mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse,
							embargo, outpost, salvager, sea_hag, treasure_map};
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	printf("Testing Village Card\n");
	for(n = 0; n < 10000; n++){
		p = (rand() % (MAX_PLAYERS-1));
		initializeGame(p+1, k, 1000, &G);
		for(t = 0; t < sizeof(struct gameState); t++){//fill gameState with junk
			((char*)&G)[t] = (rand() % (256));
		}
		for(u = 0; u <= p; u++){//fill each player
			G.deckCount[u] = (rand() % (MAX_DECK-4)+5);//deck count = between 5 and MAX_DECK
			G.discardCount[u] = (rand() % (MAX_DECK-4)+5);
			G.handCount[u] = (rand() % (MAX_HAND-4)+5);

			for(r = 0; r < G.deckCount[u]; r++){
				int randomInt = (rand() % (25));
				G.deck[u][r] = randomCard[randomInt];//player deck = rand card not including treasure_map
			}
			for(r = 0; r < G.discardCount[u]; r++){
				int randomInt = (rand() % (25));
				G.discard[u][r] = randomCard[randomInt];
			}
			for(r = 0; r < G.handCount[u]; r++){
				int randomInt = (rand() % (25));
				G.hand[u][r] = randomCard[randomInt];
			}
			G.hand[u][G.handCount[u]-1] = randomCard[14];//last card in hand = village
			G.deck[u][G.deckCount[u]-1] = randomCard[26];
		}
		G.playedCardCount = (rand() % (MAX_DECK-3));
		G.numActions = 1;
		G.numPlayers = p + 1;
		turn = (rand() % (p+1));
		G.whoseTurn = turn;
		errorCount += checkVillage(&G, turn, G.handCount[turn]-1, n);
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

int checkVillage(struct gameState *pre, int currentPlayer, int handPos, int n){
	struct gameState post;
	memcpy (&post, pre, sizeof(struct gameState));
	int bonus = 0;
	int t;
	int q;
	int postCount;
	int funErrors = 0;
	cardEffect(village, -1, -1, -1, &post, handPos, &bonus);
	if(pre->handCount[currentPlayer] != post.handCount[currentPlayer]){//gain one card but should lose the village card 
		#if(NOISY_TEST == 1)
		printf("Test #:%d failed\n", n);
		printf("Expected: cardCount = %d	Actual: cardCount = %d\n", pre->handCount[currentPlayer], post.handCount[currentPlayer]);
		#endif
		funErrors++;
	}
	if(pre->numActions + 2 != post.numActions){//Should have 2 more actions than original
		#if(NOISY_TEST == 1)
		printf("Test #:%d failed\n", n);
		printf("Expected: numActions = %d	Actual: numActionst = %d\n", pre->numActions + 2, post.numActions);
		#endif
		funErrors++;
	}
	if(pre->discardCount[currentPlayer] + 1 != post.discardCount[currentPlayer]){//discardCount should be incremented
		#if(NOISY_TEST == 1)
		printf("Test #: %d failed\n", n);
		printf("Expected: discardCount = %d	Actual: discardCount = %d\n", pre->discardCount[currentPlayer] + 1, post.discardCount[currentPlayer]);
		#endif
		funErrors++;
	}
	for (t=0; t < pre->numPlayers; t++){//check other players' stuff
		if(pre->handCount[t] != post.handCount[t]){
			if(t != currentPlayer){//if current player then it's probably different
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
	return funErrors;
}
