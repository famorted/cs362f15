#include <stdio.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "unittest_helpers.h"
#include "rngs.h"


// Test the feast card
//
// NOTE: YOU ADDED A BUG: gainCard() should add the card to the discard
// pile, but now it adds it to the hand.
//
// From the Dominion Card Game Wiki (dominioncg.wikia.com):
//
// Trash this card, gain a card costing up to 5 coins.
//
// The gained card goes in your discard pile, not in your hand. 
//
// You can only gain cards from the supply pile.
//
// TO TEST:
//
// - Card came from supply pile.
// - Card went to discard pile.
// - Card is valued <= 5 (getCost() will tell you this)
//
int testFeastCard(struct gameState *state, int currentPlayer, int choice)
{
    struct gameState *origState;  // copy of game state

    // Make a copy of the original game state
    //
    origState = copyState(state);

    feastCard(choice, state);

    // Is the gained card valued at <= 5 coins?
    //
    if(getCost(choice) <= 5)
    {
        printf("feastCard: PASS gained card is valued at <= 5 coins\n");
    }
    else
    {
        printf("feastCard: FAIL gained card is valued at > 5 coins\n");
    }

    // Did the gained card come from the supply pile?
    //
    if(state->supplyCount[choice] == origState->supplyCount[choice]-1)
    {
        printf("feastCard: PASS gained card taken from supply pile\n");
    }
    else
    {
        printf("feastCard: FAIL gained card not taken from supply pile\n");
    }
    
    // Was the gained card added to the discard pile?
    //
    if(state->discard[currentPlayer][origState->discardCount[currentPlayer]] == choice)
    {
        printf("feastCard: PASS gained card added to discard pile\n");
    }
    else
    {
        printf("feastCard: FAIL gained card not added to discard pile\n");
    }

    // Was the discard pile count incremented?
    //
    if(state->discardCount[currentPlayer] == origState->discardCount[currentPlayer]+1)
    {
        printf("feastCard: PASS discard count incremented\n");
    }
    else
    {
        printf("feastCard: FAIL discard count not incremented\n");
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
    int choice;
    int currentPlayer;
    int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, cutpurse, sea_hag, tribute, smithy, feast};
    int randomSeed = 100;
    struct gameState *state;

    // New game
    //
    state = newGame();
    initializeGame(numPlayers, kingdomCards, randomSeed, state);

    printf("\n");

    printf(">>> TESTING: feast card...\n");

    // Set up arguments to cardEffect().
    //
    // Cards worth up to 5 coins (for choice):
    //
    // 5: council room, festival, laboratory, library, market, mine, witch
    //
    // 4: bureaucrat, feast, gardens, militia, moneylender, remodel,
    // smithy, spy, thief, throne room
    //
    // 3: chancellor, village, woodcutter, workshop
    //
    // 2: cellar, chapel, moat
    //
    // Be sure to have the card in kingdomCards[] above! You control this,
    // don't try to be tricky.
    //
    currentPlayer = 0;
    choice = smithy;
    testFeastCard(state, currentPlayer, choice);

    return 0;
}

