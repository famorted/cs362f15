#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "unittest_helpers.h"


// Test the gainCard() function.
//
// gainCard():
// Checks for an ample supply of cards first, and if one exists, adds a
// specific card to a player's hand, deck, or trash.
//
// supplyPos - enumerated card
// state     - holds the game state
// toFlag    - where to put the card (0 = discard, 1 = deck, 2 = hand)
// player    - who to give the card to
//
// Returns -1 if not enough supply or 0 on success
//
int testUpdateCoins(int player, struct gameState *state, int bonus)
{
    struct gameState *origState;  // copy of game state
    int coinCount = 0;
    int i;

    // Make a copy of the original game state
    //
    origState = copyState(state);

    // Run updateCoins()
    //
    updateCoins(player, state, bonus);

    for (i = 0; i < state->handCount[player]; i++)
    {
        if (state->hand[player][i] == copper)
        {
            coinCount += 1;
        }
        else if (state->hand[player][i] == silver)
        {
            coinCount += 2;
        }
        else if (state->hand[player][i] == gold)
        {
            coinCount += 3;
        }       
    }   
    
    coinCount += bonus;

    if(state->coins == coinCount)
    {
        printf("updateCoins: PASS game state holds correct number of coins.\n");
    }
    else
    {
        printf("updateCoins: FAIL game state holds incorrect number of coins.\n");
    }

    //printf("\nupdateCoins: Changes to game state:\n----------------------------------------\n");
    whatChanged(origState, state);

    printf("\n");

    return 0;
}


int main(int argc, char *argv[])
{
    int player;
    int bonus;
    int numPlayers = 2;
    int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    int randomSeed = 100;
    struct gameState *state;

    // New game
    //
    state = newGame();
    initializeGame(numPlayers, kingdomCards, randomSeed, state);

    printf("\n");

    // Discard a trashed card
    printf(">>> TESTING: updateCoins(), player 0 coins, 5 bonus...\n");
    player = 0;
    bonus = 5;
    testUpdateCoins(player, state, bonus);

    printf("\n");

    // New game
    //
    state = newGame();
    initializeGame(numPlayers, kingdomCards, randomSeed, state);

    // Discard a non-trashed card
    printf(">>> TESTING: updateCoins(), player 1 coins, 3 bonus...\n");
    player = 0;
    bonus = 5;
    testUpdateCoins(player, state, bonus);

    return 0;
}



