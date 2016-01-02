/* -----------------------------------------------------------------------
 * Unit Test for scoreFor()
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

    printf ("TESTING scoreFor():\n");
    for (p = 2; p >= numPlayer; p++){
        
    	memset(&G, 23, sizeof(struct gameState));   // clear the game state
    	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

        G.handCount[1] = 3;
        G.discardCount[1] = 0;
        G.deckCount[1] = 0;
    	G.hand[1][0] = province;
        G.hand[1][1] = estate;
        G.hand[1][2] = duchy;
        printf("Test score contains 10 points\n\n");

        int score = 0;
        score = scoreFor(1, &G);
        printf("Expected hand score = 10, Actual hand score = %d\n", score);
        if (score == 10) {
            printf("Hand score TEST PASSED\n\n");
        } else {
            printf("Hand score TEST FAILED\n\n");
        }

        G.handCount[1] = 0;
        G.discardCount[1] = 3;
        G.deckCount[1] = 0;
        G.discard[1][0] = estate;
        G.discard[1][1] = estate;
        G.discard[1][2] = estate;

        score = scoreFor(1, &G);
        printf("Expected discard score = 10, Actual discard score = %d\n", score);
        if (score == 10) {
            printf("Discard score TEST PASSED\n\n");
        } else {
            printf("Discard score TEST FAILED\n\n");
        }

        G.handCount[1] = 0;
        G.discardCount[1] = 0;
        G.deckCount[1] = 3;
        G.deck[1][0] = province;
        G.deck[1][1] = estate;
        G.deck[1][2] = duchy;

        score = scoreFor(1, &G);
        printf("Expected deck score = 10, Actual deck score = %d\n", score);
        if (score == 10) {
            printf("Deck score TEST PASSED\n\n");
        } else {
            printf("Deck score TEST FAILED\n\n");
        }

    	printf("All tests passed!\n");

    	return 0;
	}
}