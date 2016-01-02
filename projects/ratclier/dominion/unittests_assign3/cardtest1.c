#include <stdio.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "unittest_helpers.h"
#include "rngs.h"


// Test the smithy card
//
// NOTE: YOU ADDED A BUG: changed the trashFlag in the call to discardCard
// from 0 to 1 (sets the card as trashed).
//
// The Smithy card draws 3 cards from the player's deck and adds them to
// the player's hand. Once that is done, the Smithy card itself is
// discarded.
//
// Order of operations: cardEffect()    [switch(smithy)]
//                      drawCard()      [draw 3 cards]
//                      discardCard()   [discard a card from hand]
//
// TO TEST:
//
// - 3 cards are drawn from the deck and added to hand.
// - Discarded smithy card goes in the played pile. (See your bug above)
//
int testSmithyCard(int currentPlayer, struct gameState *state, int handPos)
{
    struct gameState *origState;  // copy of game state

    // Make a copy of the original game state
    //
    origState = copyState(state);

    smithyCard(state, handPos);

    // Have three cards been drawn from the deck?
    //
    if(state->deckCount[currentPlayer] == origState->deckCount[currentPlayer]-3)
    {
        printf("smithyCard: PASS three cards removed from deck\n");
    }
    else
    {
        printf("smithyCard: FAIL three cards not removed from deck\n");
    }

    // Have three cards been added to the hand? (If 3 were added and 1
    // discarded, we should end up with 2 more than we had at the
    // beginning.)
    //
    if(state->handCount[currentPlayer] == origState->handCount[currentPlayer]+2)
    {
        printf("smithyCard: PASS three cards added to hand (and one discarded)\n");
    }
    else
    {
        printf("smithyCard: FAIL three cards not added to hand\n");
    }

    // Did the smithy card end up on the played pile? The only test we can
    // reliably make is on the count of cards on the played pile.
    // Comparing actual cards between state and origState won't work
    // because more than one of a specific cards could exist in a hand.
    //
    if(state->playedCardCount == origState->playedCardCount+1)
    {
        printf("smithyCard: PASS discarded card added to played pile (count incremented)\n");
    }
    else 
    {
        printf("smithyCard: FAIL discarded card did not end up on played pile (not incremented)\n");
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
    int currentPlayer;
    int handPos;
    int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    int randomSeed = 100;
    struct gameState *state;

    // New game
    //
    state = newGame();
    initializeGame(numPlayers, kingdomCards, randomSeed, state);

    printf("\n");

    // Test smithy card for player 0
    //
    printf(">>> TESTING: smithy card, player 0...\n");
    //currentPlayer = whoseTurn(state);
    currentPlayer = 0;
    handPos = floor(Random() * state->handCount[currentPlayer]);
    testSmithyCard(currentPlayer, state, handPos);

    // Test smithy card for player 1
    //
    printf(">>> TESTING: smithy card, player 1...\n");
    //currentPlayer = whoseTurn(state);
    currentPlayer = 1;
    handPos = floor(Random() * state->handCount[currentPlayer]);
    testSmithyCard(currentPlayer, state, handPos);

    return 0;
}

