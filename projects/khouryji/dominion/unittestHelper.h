#include "dominion.h"

struct aChangeReturnVals
{
	int stateChange;
	int indexI;
	int indexJ;
};

enum stateChange
{
  E_numPlayers= 0,
  E_supplyCount,
  E_embargoTokens,
  E_outpostPlayed,
  E_outpostTurn,
  E_whoseTurn,
  E_phase,
  E_numActions,
  E_coins,
  E_numBuys,
  E_hand,
  E_handCount,
  E_deck,
  E_deckCount,
  E_discard,
  E_discardCount,
  E_playedCards,
  E_playedCardCount
};

struct gameState * makeCopyState(struct gameState *original, struct gameState *copyState);

struct aChangeReturnVals aChange(struct gameState *copyState, struct gameState *newState);

int printBadDiffs(struct gameState *copyState, struct gameState *afterCopy);
