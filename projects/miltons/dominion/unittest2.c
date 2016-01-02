// tests updateCoins() function
// adapted from example code `testUpdateCoins.c` provided by instructor for use as template

#include <stdio.h>  // for printf
#include <string.h> // for memcpy
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


/* this function runs a single test on the updateCoins() function. It mainly serves to reduce code redundancy. */
void testCoins(struct gameState* t, int coins[MAX_HAND], int handCount, int player, int bonus, int multiplier);


int main(int argc, char *argv[])
{
    int retVal;
    int player;
    int numPlayers = 2;
    int handCount;
    int maxHandCount = 5;
    int bonus;
    int maxBonus = 10;
    int seed = 9999; // seed for random number generator
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall}; // kingdom cards
    struct gameState testState;
    int i;
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];

    // create arrays of all copper, silver, and gold
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    // initialize a new game for testing purposes (only need to do this once)
    retVal = initializeGame(numPlayers, k, seed, &testState);

    if (retVal == 0)
    {
        printf("Game initialized successfully\n");
    }
    else
    {
        printf("Game failed to initialize.\n");
    }

    // vary the number of players (1 or 2)
    for (player = 1; player <= numPlayers; player++)
    {
        // test with differing numbers of treasure cards (1 to 5)
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
            // test with varying bonus amounts (0 to 10 coins)
            for (bonus = 0; bonus <= maxBonus; bonus++)
            {
                // reset coins to zero for each iteration
                testState.coins = 0;

                printf("Test player %d with %d treasure card(s) and %d bonus.\n", player, handCount, bonus);

                // set the number of cards in hand
                testState.handCount[player] = handCount;

                // call function to run test with copper coins
                testCoins(&testState, coppers, handCount, player, bonus, 1);

                // call function to run test with silver coins
                testCoins(&testState, silvers, handCount, player, bonus, 2);

                // call function to run test with gold coins
                testCoins(&testState, golds, handCount, player, bonus, 3);
            }
        }
    }

    return 0;
}



void testCoins(struct gameState* t, int coins[MAX_HAND], int handCount, int player, int bonus, int multiplier)
{
    // change all the cards in hand to treasure cards of type handed to function (copper, silver, or gold)
    memcpy(t->hand[player], coins, sizeof(int) * handCount);

    // update the current player's coins to test the function
    updateCoins(player, t, bonus);

    // display results
    printf("testState.coins = %d, expected = %d\n", t->coins, handCount * multiplier + bonus);

    // check if the number of coins is correct - use if / else statement instead of assert
    // in order to allow execution to continue despite failing tests
    if (t->coins == handCount * multiplier + bonus)
    {
        printf("PASS\n");
    }
    else
    {
        printf("FAIL\n");
    }
    return;
}
