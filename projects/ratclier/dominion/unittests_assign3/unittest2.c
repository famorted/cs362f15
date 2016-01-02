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
int testGainCard(int supplyPos, struct gameState *state, int toFlag, int player)
{
    struct gameState *origState;  // copy of game state
    int supplyCountRet = 0;
    
    // Make a copy of the original game state
    //
    origState = copyState(state);

    // Run gainCard()
    //
    // Consider changing the supply deck to have insufficient cards to
    // test the exit error or set supplyPos to -1, which indicates the card is
    // not used in the game. Do that in state before calling this function.
    // Within gainCard(), the supplyCount() function checks these conditions by
    // returning state->supplyCount[supplyPos] which will be 0 if empty or -1 if 
    // the card is not used in the game. We're not testing supplyCount() here,
    // just gainCard().
    //
    supplyCountRet = gainCard(supplyPos, state, toFlag, player);
    if(supplyCountRet >= 1)
    {
        // Enough cards exist. Continue with testing card movement
        // results.

        if(toFlag == 1)
        {
            /*
            state->deck[ player ][ state->deckCount[player] ] = supplyPos;
            state->deckCount[player]++;
            */
            if(state->deck[player][origState->deckCount[player]] == supplyPos)
            {
                printf("gainCard: PASS card added to player deck\n");
            }
            else
            {
                printf("gainCard FAIL card not added to player deck\n");
            }

            if(state->deckCount[player] == origState->deckCount[player]+1)
            {
                printf("gainCard: PASS player deck count incremented\n");
            }
            else
            {
                printf("gainCard: FAIL player deck count not incremented\n");
            }
        }
        else if(toFlag == 2)
        {
            /*
            state->hand[ player ][ state->handCount[player] ] = supplyPos;
            state->handCount[player]++;
            */
            if(state->hand[player][origState->handCount[player]] == supplyPos)
            {
                printf("gainCard: PASS card added to player hand\n");
            }
            else
            {
                printf("gainCard FAIL card not added to player hand\n");
            }

            if(state->handCount[player] == origState->handCount[player]+1)
            {
                printf("gainCard: PASS player hand count incremented\n");
            }
            else
            {
                printf("gainCard: FAIL player hand count not incremented\n");
            }
        }
        else if(toFlag == 0)
        {
            /*
            state->discard[player][ state->discardCount[player] ] = supplyPos;
            state->discardCount[player]++;
            */
            if(state->discard[player][origState->discardCount[player]] == supplyPos)
            {
                printf("gainCard: PASS card added to player discard\n");
            }
            else
            {
                printf("gainCard FAIL card not added to player discard\n");
            }

            if(state->discardCount[player] == origState->discardCount[player]+1)
            {
                printf("gainCard: PASS player discard count incremented\n");
            }
            else
            {
                printf("gainCard: FAIL player discard count not incremented\n");
            }
        }

        // See if the supplyCount was decremented
        //
        if(state->supplyCount[supplyPos] == origState->supplyCount[supplyPos]-1)
        {
            printf("gainCard: PASS supply count decremented\n");
        }
        else
        {
            printf("gainCard: FAIL supply count not decremented\n");
        }
    }
    else  // Exited because of insufficient cards (0) or card is not used (-1)
    {
        if(origState->supplyCount[supplyPos] < 1)
        {
            printf("gainCard: PASS exited %s\n", (origState->supplyCount[supplyPos] == 0 ? "with insufficient cards (0)\n" : "because the card is not used (-1)\n"));
        }
        else
        {
            printf("gainCard: FAIL exited in spite of having sufficient cards and the card being used in the game\n");
        }
    }
    
    // Report what, if anything, changed in the game state
    //
    whatChanged(origState, state);
    printf("\n");

    return 0;
}


int main(int argc, char *argv[])
{
    int numPlayers = 2;
    int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    int randomSeed = 10;
    int supplyPos = feast; // Just a placeholder, can be changed later
    int toFlag;            // Where to put the card (0 = discard, 1 = deck, 2 = hand)
    int player = 0;        // Just a placeholder, can be changed later
    struct gameState *state;

    // New game
    //
    state = newGame();
    initializeGame(numPlayers, kingdomCards, randomSeed, state);

    printf("\n");

    // Gain a card w/ an ample supply deck
    //
    printf(">>> TESTING: gainCard(), sufficient supply deck...\n");
    toFlag = 1;
    state->supplyCount[supplyPos] = 2;
    testGainCard(supplyPos, state, toFlag, player);

    printf("\n");

    // New game
    //
    state = newGame();
    initializeGame(numPlayers, kingdomCards, randomSeed, state);

    // Gain a card w/ an empty or insufficient supply deck
    //
    printf(">>> TESTING: gainCard(), insufficient supply deck...\n");
    toFlag = 1;
    state->supplyCount[supplyPos] = 0;
    testGainCard(supplyPos, state, toFlag, player);

    // Gain a card w/ a card that is not used in the game
    //
    printf(">>> TESTING: gainCard(), card not used in the game...\n");
    toFlag = 1;
    state->supplyCount[supplyPos] = -1;
    testGainCard(supplyPos, state, toFlag, player);


    return 0;
}



