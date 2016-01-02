/* -----------------------------------------------------------------------
 * Unit Test for isGameOver()
 *
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
 *      gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

		
int checkProvinces(struct gameState *state) {
	int gameOverCheck = isGameOver(state);
	if(state->supplyCount[province] > 0) {
    	if(gameOverCheck == 0) {
        	printf("isGameOver(): NO, TEST PASSED: gameOverCheck=%d, expected=%d\n", isGameOver(state), 0);
    	} else{
       		printf("isGameOver(): YES, TEST FAILED: gameOverCheck=%d, expected=%d\n", isGameOver(state), 0);   
        }
    } else if(state->supplyCount[province] == 0) {
       	if(gameOverCheck == 1) {
       		printf("isGameOver(): YES, TEST PASSED: gameOverCheck=%d, expected=%d\n", isGameOver(state), 1);
        } else{
         		printf("isGameOver(): NO, TEST FAILED: gameOverCheck=%d, expected=%d\n", isGameOver(state), 1);   
        }            
   	}
}

int checkSupplyCount(struct gameState *state) {
	int gameOverCheck = isGameOver(state);
	int j = 0;
	int i = 0;
    for (i = 0; i < treasure_map + 1; i++) {
    	if (state->supplyCount[i] == 0) {
    		j++;
		}
   	}
   	printf("j = %d\n", j);
   	if (j >= 3) {
   	    if(gameOverCheck == 1) {
       		printf("isGameOver(): YES, TEST PASSED: gameOverCheck=%d, expected=%d\n", isGameOver(state), 1);
        } else{
       		printf("isGameOver(): NO, TEST FAILED: gameOverCheck=%d, expected=%d\n", isGameOver(state), 1);   
   		} 
    } else if(j < 3) {
		if(gameOverCheck == 0) {
    		printf("isGameOver(): NO, TEST PASSED: gameOverCheck=%d, expected=%d\n", isGameOver(state), 0);
		} else{
   			printf("isGameOver(): YES, TEST FAILED: gameOverCheck=%d, expected=%d\n", isGameOver(state), 0);   
    	}
	}
}   		

int main() {
    int i;
    int seed = 1000;
    int numPlayer =2;
    int maxBonus = 10;
    int p, r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    printf ("TESTING isGameOver():\n");
    for (p = 2; p >= numPlayer; p++){
        
    	memset(&G, 23, sizeof(struct gameState));   // clear the game state
    	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

    	G.supplyCount[province] = 8;
    	printf("supplyCount[province] = %d\n",  G.supplyCount[province]);
    	checkProvinces(&G);

    	G.supplyCount[province] = 5;
    	printf("supplyCount[province] = %d\n",  G.supplyCount[province]);
    	checkProvinces(&G);

    	G.supplyCount[province] = 0;
    	printf("supplyCount[province] = %d\n",  G.supplyCount[province]);
    	checkProvinces(&G);
    	G.supplyCount[province] = 8;  //reset so all piles are full

    	//No pile empty
    	printf("Testing supplyCount");
    	checkSupplyCount(&G);

    	//One pile empty
    	G.supplyCount[estate] = 0;
    	checkSupplyCount(&G);

    	//Three piles empty, also set as the last two cards
    	G.supplyCount[sea_hag] = 0;
    	G.supplyCount[treasure_map] = 0;
    	checkSupplyCount(&G);

    	//Six piles empty
    	G.supplyCount[copper] = 0;
    	G.supplyCount[baron] = 0;
    	G.supplyCount[province] = 0;
    	checkSupplyCount(&G);

    	//All piles empty
    	int i;
    	for(i = 0; i < treasure_map+1; i++){
    		G.supplyCount[i] = 0;
    	}
    	checkSupplyCount(&G);

    	printf("All tests passed!\n");

    	return 0;
	}
}