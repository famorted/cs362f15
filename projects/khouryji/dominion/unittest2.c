#include "dominion.h"
#include <cstring>
#include "unittestHelper.h"

int i;
  struct gameState copyState, afterCopy;
  struct aChangeReturnVals aDiff= (aChangeReturnVals){-1,-1,-1};

  makeCopyState(state, &copyState);

  endTurn(state);

  makeCopyState(state, &afterCopy);
  
  do
	{
		//compare game state before endTurn is called, to after the call
		aDiff= aChange(afterCopy, copyState);

		switch(aDiff.stateChange)
		{
			case E_numPlayers:  
				printf("Error: numPlayers changed.\n"); 
				printf("numPlayers Before: %d\n", copyState.numPlayers);
				printf("numPlayers After: %d\n\n", afterCopy.numPlayers);
				//The line below removes this cases difference in order to allow
				//the change finding function to find the next difference in states
				afterCopy.numPlayers= copyState.numPlayers;
				break;

			case E_supplyCount: 
				printf("Error: supplyCount changed.\n"); 
				printf("supplyCount of card#%d Before: %d\n", r.indexI, copyState.supplyCount[r.indexI]);
				printf("supplyCount of card#%d After: %d\n\n", r.indexI, afterCopy.supplyCount[r.indexI]);
				afterCopy.supplyCount[r.indexI]= copyState.supplyCount[r.indexI];
				break;
			case E_embargoTokens: 
				printf("Error: embargoTokens changed.\n"); 
				printf("embargoTokens of card#%d Before: %d\n", r.indexI, copyState.embargoTokens[r.indexI]);
				printf("embargoTokens of card#%d After: %d\n\n", r.indexI, afterCopy.embargoTokens[r.indexI]);
				afterCopy.embargoTokens[r.indexI]= copyState.embargoTokens[r.indexI];
				break;

			case E_outpostPlayed: 
				
				afterCopy.outpostPlayed= copyState.outpostPlayed;
				break;

			case E_outpostTurn: 
				printf("Error: outpostTurn changed.\n"); 
				printf("outpostTurn Before: %d\n", copyState.outpostTurn);
				printf("outpostTurn After: %d\n\n", afterCopy.outpostTurn);
				afterCopy.outpostTurn= copyState.outpostTurn;
				break;

			case E_whoseTurn: 
				
				afterCopy.whoseTurn= copyState.whoseTurn;
				break;

			case E_phase:
				
				afterCopy.phase= copyState.phase;
				break;

			case E_numActions: 
				
				afterCopy.numActions= copyState.numActions;
				break;

			case E_coins: 
				
				afterCopy.coins= copyState.coins;
				break;

			case E_numBuys: 
				
				afterCopy.numBuys= copyState.numBuys;
				break;

			case E_hand: 
				printf("Error: hand changed.\n"); 
				printf("Player#%d hand position#%d Before: %d\n", r.indexI, r.indexJ, copyState.hand[r.indexI][r.indexJ]);
				printf("Player#%d hand position#%d After: %d\n\n", r.indexI, r.indexJ, afterCopy.hand[r.indexI][r.indexJ]);
				afterCopy.hand[r.indexI][r.indexJ]= copyState.hand[r.indexI][r.indexJ];
				break;

			case E_handCount: 
				
				afterCopy.handCount= copyState.handCount;
				break;

			case E_deck: 
				printf("Error: deck changed.\n"); 
				printf("Player#%d deck position#%d Before: %d\n", r.indexI, r.indexJ, copyState.deck[r.indexI][r.indexJ]);
				printf("Player#%d deck position#%d After: %d\n\n", r.indexI, r.indexJ, afterCopy.deck[r.indexI][r.indexJ]);
				afterCopy.deck[r.indexI][r.indexJ]= copyState.deck[r.indexI][r.indexJ];
				break;

			case E_deckCount:
				printf("Error: deckCount changed.\n"); 
				printf("Player#%d deckCount Before: %d\n", r.indexI, copyState.deckCount[r.indexI]);
				printf("Player#%d deckCount After: %d\n\n", r.indexI, afterCopy.deckCount[r.indexI]);
				afterCopy.deckCount[r.indexI]= copyState.deckCount[r.indexI];
				break;

			case E_discard: 
				printf("Error: discard changed.\n"); 
				printf("Player#%d discard position#%d Before: %d\n", r.indexI, r.indexJ, copyState.deck[r.indexI][r.indexJ]));
				printf("Player#%d discard position#%d After: %d\n\n", r.indexI, r.indexJ, afterCopy.deck[r.indexI][r.indexJ]));
				afterCopy.discard[r.indexI][r.indexJ]= copyState.discard[r.indexI][r.indexJ];
				break;

			case E_discardCount: 
				
				afterCopy.discardCount= copyState.discardCount;
				break;

			case E_playedCards: 
				printf("Error: playedCards changed.\n"); 
				printf("playedCard#%d Before: %d\n", r.indexI, copyState.playedCards[r.indexI]);
				printf("playedCard#%d After: %d\n\n", r.indexI, afterCopy.playedCards[r.indexI]);
				afterCopy.playedCards[r.indexI]= copyState.playedCards[r.indexI];
				break;

			case E_playedCardCount: 
				afterCopy.playedCardCount= copyState.playedCardCount;
				break;
		}		
	}
	while(r.stateChange > 0);



  
check if deck is empty, if it is, new deckCount should be same as discardCount
discardCount should go to 0
shuffle should change the order from the discard array
deckCount
handCount
check everyone elses hands

int drawCard(int player, struct gameState *state)
{	int count;
  int deckCounter;
  if (state->deckCount[player] <= 0){//Deck is empty
    
    //Step 1 Shuffle the discard pile back into a deck
    int i;
    //Move discard to deck
    for (i = 0; i < state->discardCount[player];i++){
      state->deck[player][i] = state->discard[player][i];
      state->discard[player][i] = -1;
    }

    state->deckCount[player] = state->discardCount[player];
    state->discardCount[player] = 0;//Reset discard

    //Shufffle the deck
    shuffle(player, state);//Shuffle the deck up and make it so that we can draw
   
    if (DEBUG){//Debug statements
      printf("Deck count now: %d\n", state->deckCount[player]);
    }
    
    state->discardCount[player] = 0;

    //Step 2 Draw Card
    count = state->handCount[player];//Get current player's hand count
    
    if (DEBUG){//Debug statements
      printf("Current hand count: %d\n", count);
    }
    
    deckCounter = state->deckCount[player];//Create a holder for the deck count

    if (deckCounter == 0)
      return -1;

    state->hand[player][count] = state->deck[player][deckCounter - 1];//Add card to hand
    state->deckCount[player]--;
    state->handCount[player]++;//Increment hand count
  }

  else{
    int count = state->handCount[player];//Get current hand count for player
    int deckCounter;
    if (DEBUG){//Debug statements
      printf("Current hand count: %d\n", count);
    }

    deckCounter = state->deckCount[player];//Create holder for the deck count
    state->hand[player][count] = state->deck[player][deckCounter - 1];//Add card to the hand
    state->deckCount[player]--;
    state->handCount[player]++;//Increment hand count
  }

  return 0;
}