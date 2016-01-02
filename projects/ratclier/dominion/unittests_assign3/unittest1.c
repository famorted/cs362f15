#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "unittest_helpers.h"


// Test the discardCard() function
//
// discardCard():
// Removes card from player's hand and either puts it in the played pile
// (if not trashed) or not (if trashed).
//
// handPos       - enumerated card
// currentPlayer - the index of the current player
// state         - holds the game state
// trashFlag     - determines whether the card is trashed (>= 1) or not (< 1)
//
// Always returns 0.
//
int testDiscardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag)
{
    struct gameState *origState;  // copy of game state

    // Make a copy of the original game state
    //
    origState = copyState(state);

    // Run discardCard()
    //
    discardCard(handPos, currentPlayer, state, trashFlag);

    // If the card was trashed, the card should not be added to the played
    // card pile and played card count should not increment. Otherwise,
    // add the card to the played card pile and increment the count.
    //
    if(trashFlag >= 1)
    {
        if(state->playedCardCount == origState->playedCardCount)
        {
            printf("discardCard: PASS trashed card did not increment playedCardCount\n");
        }
        else
        {
            printf("discardCard: FAIL trashed card incremented playedCardCount\n");
        }
    }
    else
    {
        // If the card was NOT trashed, the card SHOULD be added to the played
        // card pile and played card count SHOULD increment
        //
        if(state->playedCardCount == origState->playedCardCount + 1)
        {
            printf("discardCard: PASS non-trashed card incremented playedCardCount\n");
        }
        else
        {
            printf("discardCard: FAIL non-trashed card did not incremenet playedCardCount\n");
        }

        if(state->playedCards[state->playedCardCount-1] == origState->hand[currentPlayer][handPos])
        {
            printf("discardCard: PASS non-trashed card added to played card pile\n");
        }
        else
        {
            printf("discardCard: FAIL non-trashed card not added to played card pile\n");
        }
    }

    // Remove the card from the player's hand
    //
    if(handPos == origState->handCount[currentPlayer] - 1)
    {
        if(state->handCount[currentPlayer] == origState->handCount[currentPlayer] - 1)
        {
            printf("discardCard: PASS card removal decremented current player handcount\n");
        }
        else
        {
            printf("discardCard: FAIL card removal did not decrement current player handcount\n");
        }
    }
    else if(origState->handCount[currentPlayer] == 1)
    {
        if(state->handCount[currentPlayer] == origState->handCount[currentPlayer] - 1)
        {
            printf("discardCard: PASS card removal decremented current player handcount\n");
        }
        else
        {
            printf("discardCard: FAIL card removal did not decrement current player handcount\n");
        }
    }
    else
    {
        // Check if discarded card was replaced with last card in hand
        //
        if(state->hand[currentPlayer][handPos] == origState->hand[currentPlayer][(origState->handCount[currentPlayer] - 1)])
        {
            printf("discardCard: PASS discarded card was replaced with last card in hand\n");
        }
        else
        {
            printf("discardCard: FAIL discarded card was not replaced with last card in hand\n");
        }

        // Check if last card was set to -1
        //
        if(state->hand[currentPlayer][origState->handCount[currentPlayer] - 1] == -1)
        {
            printf("discardCard: PASS last card set to -1\n");
        }
        else
        {
            printf("discardCard: FAIL last card not set to -1\n");
        }

        // Check if the number of cards in hand was reduced
        //
        if(state->handCount[currentPlayer] == origState->handCount[currentPlayer] - 1)
        {
            printf("discardCard: PASS card removal decremented current player handcount\n");
        }
        else
        {
            printf("discardCard: FAIL card removal did not decrement current player handcount\n");
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
    int handPos = 3;
    int currentPlayer = 0;
    int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    int randomSeed = 100;
    int trashFlag;
    struct gameState *state;

    // New game
    //
    state = newGame();
    initializeGame(numPlayers, kingdomCards, randomSeed, state);

    printf("\n");

    // Discard a trashed card
    printf(">>> TESTING: discardCard(), trashed card...\n");
    trashFlag     = 1;   // trashed
    testDiscardCard(handPos, currentPlayer, state, trashFlag);

    //printf("\n");

    // New game
    //
    state = newGame();
    initializeGame(numPlayers, kingdomCards, randomSeed, state);

    // Discard a non-trashed card
    printf(">>> TESTING: discardCard(), non-trashed card...\n");
    trashFlag     = 0;   // not trashed
    testDiscardCard(handPos, currentPlayer, state, trashFlag);

    return 0;
}



