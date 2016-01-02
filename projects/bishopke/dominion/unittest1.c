//Keenan Bishop unittest1.c
//updateCoins() test
//from template



#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
//#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 0

void test_updateCoins(){
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p; //player
    int r; 
    int handCount;
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

    printf ("TESTING updateCoins():\n");
    for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
            for (bonus = 0; bonus <= maxBonus; bonus++)
            {
#if (NOISY_TEST == 1)
                printf("Test player %d with %d treasure card(s) and %d bonus.\n", p, handCount, bonus);
#endif
                memset(&G, 0, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand
                memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper
                updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
                printf("G.coins = %d, expected = %d\n", G.coins, handCount * 1 + bonus);
#endif
		
                if(G.coins == handCount * 1 + bonus){ // check if the number of coins is correct
			printf("PASS: updateCoins(), copper\n"); 
		}
		else{
			printf("FAIL: updateCoins(), copper\n"); 
		}

                memcpy(G.hand[p], silvers, sizeof(int) * handCount); // set all the cards to silver
                updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
                printf("G.coins = %d, expected = %d\n", G.coins, handCount * 2 + bonus);
#endif

                if(G.coins == handCount * 2 + bonus){ // check if the number of coins is correct
			printf("PASS: updateCoins(), silver\n"); 
		}
		else{
			printf("FAIL: updateCoins(), silver\n"); 
		}



                memcpy(G.hand[p], golds, sizeof(int) * handCount); // set all the cards to gold
                updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
                printf("G.coins = %d, expected = %d\n", G.coins, handCount * 3 + bonus);
#endif
                if(G.coins == handCount * 3 + bonus){ // check if the number of coins is correct
			printf("PASS: updateCoins(), gold\n"); 
		}
		else{
			printf("FAIL: updateCoins(), gold\n"); 
		}

            }
        }
    }

    //printf("All tests passed!\n");

    //return 0;
}

int main(){
	test_updateCoins();
	return 0;
}
