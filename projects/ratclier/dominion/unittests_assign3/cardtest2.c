#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "unittest_helpers.h"

// Test the adventurer card
//
// NOTE: YOU ADDED A BUG: changed cardDrawn assignment to not place drawn
// card at the end of the hand.
//
// The Adventurer card draws cards from the player's deck until two
// Treasure (coin) cards are drawn. If the drawn card is not a Treasure
// card, it is added to a temporary hand; if it is a Treasure card, it is
// added to the player's hand. At the end of the process, whatever is in
// the temporary hand (which contains no Treasure cards) is discarded.
// 
// If the player's deck is empty when the Adventurer card is played, the
// player's discard pile is shuffled and becomes the player's deck. (This
// seems pointless as the drawCard() function does this already.)
//
// From the Dominion Card Game Wiki (dominioncg.wikia.com):
//
// Reveal cards from your deck until you reveal 2 treasure cards. Put
// those treasure cards in your hand and discard the other revealed cards.
//
// If you have to shuffle in the middle, shuffle. Don't shuffle in the
// revealed cards as these cards do not go to the discard pile until you
// have finished revealing cards. If you run out of cards after shuffling
// and still only have one treasure, you get just that one treasure.
//
//
int testAdventurerCard(struct gameState *state)
{
    struct gameState *origState;  // copy of game state
    int currentPlayer = state->whoseTurn;
    int passFlag = 1;
    int lastCard;
    int idx;
    int diffDeckCount;
    int diffDiscardCount;

    // Make a copy of the original game state
    //
    origState = copyState(state);

    adventurerCard(state);

    // See if handCount increased by two cards
    //
    if(state->handCount[currentPlayer] == origState->handCount[currentPlayer]+2)
    {
        printf("adventurerCard: PASS two new cards added to hand\n");

        // See if last two cards in hand are treasure cards (enum 4-6)
        //
        lastCard = state->handCount[currentPlayer];
        for(idx = 1; idx <=2; idx++)
        {
            if((state->hand[currentPlayer][lastCard-idx] <= copper) && (state->hand[currentPlayer][lastCard-idx] >= gold)) 
            {
                passFlag = 0;
            }
        }
        if(passFlag == 1)
        {
            printf("adventurerCard: PASS last two cards in hand are treasure cards\n");
        }
        else 
        {
            printf("adventurerCard: FAIL at least one of the last two cards in hand is not a treasure card\n");
        }
    }
    else 
    {
        printf("adventurerCard: FAIL two new cards not added to hand\n");
    }

    // See if the number of discarded cards is correct
    //
    diffDeckCount = origState->deckCount[currentPlayer] - state->deckCount[currentPlayer];
    diffDiscardCount = origState->discardCount[currentPlayer] - state->discardCount[currentPlayer];
    if(diffDiscardCount + 2 == diffDeckCount)
    {
        printf("adventurerCard: PASS correct number of cards discarded\n");
    }
    else 
    {
        printf("adventurerCard: FAIL incorrect number of cards discarded\n");
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
    int randomSeed = 1000;
    struct gameState *state;

    // New game
    //
    state = newGame();
    initializeGame(numPlayers, kingdomCards, randomSeed, state);

    printf("\n");

    // Test adventurer card for player 0
    //
    printf(">>> TESTING: adventurer card, player 0...\n");
    state->whoseTurn = 0;
    testAdventurerCard(state);

    return 0;
}


