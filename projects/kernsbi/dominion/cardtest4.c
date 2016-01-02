// Name: Billy Kerns
// File: cardtest4.c
// great hall

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>

#define NOISY_TEST 0 

int checkGreatHall(struct gameState *pre, int currentPlayer, int handPos, int n);

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
	printf("Testing Great Hall Card\n");
	for(n = 0; n < 10000; n++){
		p = (rand() % (MAX_PLAYERS-1));
		initializeGame(p+1, k, 1000, &G);
		for(t = 0; t < sizeof(struct gameState); t++){//fill gameState with junk
			((char*)&G)[t] = (rand() % (256));
		}
		for(u = 0; u <= p; u++){//Fill each player with relevant data
			G.deckCount[u] = (rand() % (MAX_DECK-4)+5);//player deckCount = random number bewtween 5 and MAX_DECK
			G.discardCount[u] = (rand() % (MAX_DECK-4)+5);
			G.handCount[u] = (rand() % (MAX_HAND-4)+5);

			for(r = 0; r < G.deckCount[u]; r++){
				int randomInt = (rand() % (25));
				G.deck[u][r] = randomCard[randomInt];//player deck = random card not including treasure_map
			}
			for(r = 0; r < G.discardCount[u]; r++){
				int randomInt = (rand() % (25));
				G.discard[u][r] = randomCard[randomInt];
			}
			for(r = 0; r < G.handCount[u]; r++){
				int randomInt = (rand() % (25));
				G.hand[u][r] = randomCard[randomInt];
			}
			G.hand[u][G.handCount[u]-1] = randomCard[16];//last card in hand = great_hall
			G.hand[u][G.handCount[u]-((G.handCount[u]-1) / 2)] = baron;//card in middle of hand = barron.  For testing that other player's hand hasn't changed
			G.deck[u][G.deckCount[u]-1] = randomCard[26];//card at end of deck = treasure_map. For testing that other player's deck hasn't changed.
		}
		G.playedCardCount = (rand() % (MAX_DECK-3));
		G.numActions = 1;
		G.numPlayers = p + 1;
		turn = (rand() % (p+1));
		G.whoseTurn = turn;
		errorCount += checkGreatHall(&G, turn, G.handCount[turn]-1, n);
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

int checkGreatHall(struct gameState *pre, int currentPlayer, int handPos, int n){
	struct gameState post;
	memcpy (&post, pre, sizeof(struct gameState));
	int t;
	int q;
	int postCount;
	int funErrors = 0;
	greatHallCard(currentPlayer, &post, handPos);;
	if(pre->handCount[currentPlayer] != post.handCount[currentPlayer]){//should gain card but also lose great_hall to discard
		#if(NOISY_TEST == 1)
		printf("Test #:%d failed\n", n);
		printf("Expected: cardCount = %d	Actual: cardCount = %d\n", pre->handCount[currentPlayer], post.handCount[currentPlayer]);
		#endif
		funErrors++;
	}
	if(pre->numActions + 1 != post.numActions){//numActions should be incremented by one
		#if(NOISY_TEST == 1)
		printf("Test #:%d failed\n", n);
		printf("Expected: numActions = %d	Actual: numActionst = %d\n", pre->numActions + 1, post.numActions);
		#endif
		funErrors++;
	}
	if(post.hand[currentPlayer][pre->handCount[currentPlayer]-1] == great_hall){//great_hall card should be removed from hand
		#if(NOISY_TEST == 1)
		printf("Test #:%d failed\n", n);
		printf("Expected: Played great_hall card to be removed	Actual: Played great_hall card was not removed\n");
		#endif
		funErrors++;
	}

	if(pre->discardCount[currentPlayer] + 1 != post.discardCount[currentPlayer]){//discard count should have went up by one
		#if(NOISY_TEST == 1)
		printf("Test #: %d failed\n", n);
		printf("Expected: discardCount = %d	Actual: discardCount = %d\n", pre->discardCount[currentPlayer] + 1, post.discardCount[currentPlayer]);
		#endif
		funErrors++;
	}
	for (t=0; t < pre->numPlayers; t++){//Test other players' stuff
		if(pre->handCount[t] != post.handCount[t]){
			if(t != currentPlayer){//if current player it probably will be different
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
		if(post.hand[t][post.handCount[t]-((post.handCount[t]-1) / 2)] != baron){//make sure baron stayed in non current players' hand
			if(t != currentPlayer){
				#if(NOISY_TEST == 1)
				printf("Test #: %d failed\n", n);
				printf("Expected: Hand of unused player to be the same	Actual: Hand of unused player is not the same\n");
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
		if(1 != postCount){//Make sure treasure_map stayed in non current players' deck
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

