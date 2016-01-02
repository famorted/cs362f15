// Name: Billy Kerns
// Assignment 3
// unittest4.c
// Testing the updateCoins() function

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
	int OGCoins;
	int n;
	int errorCount = 0;
	int copperCoins;
	int silverCoins;
	int goldCoins;
	int postCopperCoins;
	int postSilverCoins;
	int postGoldCoins;
	int r;
	int i;
	int p;
	int bonus;
	enum CARD randomCard[27] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens,
							mine,remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse,
							embargo, outpost, salvager, sea_hag, treasure_map};
	srand(time(NULL));
	struct gameState G;
	
	printf("Testing updateCoins():\n");
	for(n = 0; n < 1000; n++){
		copperCoins = 0;
		silverCoins = 0;
		goldCoins = 0;
		postCopperCoins = 0;
		postSilverCoins = 0;
		postGoldCoins = 0;

		for(i = 0; i < sizeof(struct gameState); i++){
			((char*)&G)[i] = (rand() % (256));//fill gameState with junk
		}
		p = (rand() % (2));//players between 0 and 1
		
		G.handCount[p] = (rand() % (MAX_HAND));
		G.coins = 0;
		OGCoins = 0;
		for(r = 0; r < G.handCount[p]; r++){
			int randomInt = (rand() % (26));
			G.hand[p][r] = randomCard[randomInt];
			if(randomCard[randomInt] == copper){//if random card added to hand = copper
				OGCoins++;//increment local coin variable
				G.coins++;//increment gameState coins
				copperCoins++;//increment copperCoins
			}
			else if(randomCard[randomInt] == silver){
				OGCoins += 2;
				G.coins += 2;
				silverCoins++;
			}
			else if(randomCard[randomInt] == gold){
				OGCoins += 3;
				G.coins += 3;
				goldCoins++;
			}
		}
		bonus = (rand() % (10));//random bonus
		struct gameState post;
		memcpy (&post, &G, sizeof(struct gameState));

		updateCoins(p, &post, bonus);
		G.coins += bonus;
		OGCoins += bonus;

		for(r = 0; r < post.handCount[p]; r++){//count coins in hand after function
			if(post.hand[p][r] == copper){
				postCopperCoins++;
			}
			else if(post.hand[p][r] == silver){
				postSilverCoins++;
			}
			else if(post.hand[p][r] == gold){
				postGoldCoins++;
			}
		}
		if(G.coins != post.coins){//Test 1: Coins in both states should be even
			#if(NOISY_TEST == 1)
			printf("Test #%d Failed.\n", n);
			printf("GameState coin counts are not equal.\n");
			#endif
			errorCount++;
		}
		if(post.coins != OGCoins){//Test 2: post.coins should equal local coin variable OGCoins
			#if(NOISY_TEST == 1)
			printf("Test #%d Failed.\n", n);
			printf("Coins after updateCoins() does not equal local coin holder variable.\n");
			#endif
			errorCount++;
		}
		if(copperCoins != postCopperCoins){//coins before and after function should be equal
			#if(NOISY_TEST == 1)
			printf("Test #%d Failed.\n", n);
			printf("Incorrect amount of copper coins.\n");
			#endif
			errorCount++;
		}
		if(silverCoins != postSilverCoins){
			#if(NOISY_TEST == 1)
			printf("Test #%d Failed.\n", n);
			printf("Incorrect amound of silver coins.\n");
			#endif
			errorCount++;
		}
		if(goldCoins != postGoldCoins){
			#if(NOISY_TEST == 1)
			printf("Test #%d Failed.\n", n);
			printf("Incorrect amount of gold coins.\n");
			#endif
			errorCount++;
		}
		if(memcmp(&G, &post, sizeof(struct gameState)) != 0){//Test 3: GameStates should be identical
			#if(NOISY_TEST == 1)
			printf("Test #%d Failed.\n", n);
			printf("Memcmp failed\n");
			#endif
			errorCount++;
		}
		#if(NOISY_TEST == 1)
		printf("Expected value of coins: %d	Actual value of coins: %d\n", G.coins, post.coins);
		printf("Expected: %d Copper coins	Actual: %d Copper coins\n", copperCoins, postCopperCoins);
		printf("Expected: %d Silver coins	Actual: %d Silver coins\n", silverCoins, postSilverCoins);
		printf("Expected: %d Gold coins		Actual: %d Gold coins\n", goldCoins, postGoldCoins);
		printf("Bonus: %d\n", bonus);
		printf("\n");
		#endif
	}
	if(errorCount == 0){
		printf("All tests passed\n");
	}
	else{
		#if(NOISY_TEST != 1)
		printf("At least one failed test.  Set NOISY_TEST to 1 for more information\n");
		#endif
	}
	return 0;
}
