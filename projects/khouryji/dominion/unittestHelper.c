#include "unittestHelper.h"

struct gameState * makeCopyState(struct gameState *original, struct gameState *copyState)
{
	int i;
	copyState->numPlayers = original->numPlayers;

	memmove(copyState->supplyCount, original->supplyCount, treasure_map+1);
	
	memmove(copyState->embargoTokens, original->embargoTokens,treasure_map+1);

	copyState->outpostPlayed= original->outpostPlayed;

	copyState->outpostTurn= original->outpostTurn;

	copyState->whoseTurn= original->whoseTurn;

	copyState->phase= original->phase;

	copyState->numActions= original->numActions;

	copyState->coins= original->coins; 
	
	copyState->numBuys= original->numBuys; 

	for(i=0; i<MAX_PLAYERS; i++)
	{
		memmove(copyState->hand[i],original->hand[i], MAX_HAND);
	}
	
	memmove(copyState->handCount, original->handCount, MAX_PLAYERS);

	for(i=0; i<MAX_PLAYERS; i++)
	{
		memmove(copyState->deck[i], original->deck[i], MAX_DECK);
	}

	memmove(copyState->deckCount, original->deckCount, MAX_PLAYERS);

	for(i=0; i<MAX_PLAYERS; i++)
	{
		memmove(copyState->discard[i], original->discard[i], MAX_DECK);
	}

	memmove(copyState->discardCount, original->discardCount, MAX_PLAYERS);

	memmove(copyState->playedCards, original->playedCards, MAX_DECK);

	copyState->playedCardCount= original->playedCardCount;
}

//------------------------------------------------------------

//------------------------------------------------------------
struct aChangeReturnVals aChange(struct gameState *copyState, struct gameState *newState)
{
	int i,j;
	struct aChangeReturnVals r;
	r.stateChange= -1;
	r.indexI= -1;
	r.indexJ= -1;

	if(copyState->numPlayers != newState->numPlayers)
	{ 
		r.stateChange= E_numPlayers;
		return r;
	}

	for(i=0; i<treasure_map+1; i++)
	{
		if(copyState->supplyCount[i] != newState->supplyCount[i])
		{
			r.stateChange= E_supplyCount;
			return r;
		}
	}
	
	for(i=0; i<treasure_map+1; i++)
	{
		if(copyState->embargoTokens[i] != newState->embargoTokens[i])
		{
			r.stateChange= E_embargoTokens;
			r.indexI= i;
			return r;
		}
	}

	if(copyState->outpostPlayed != newState->outpostPlayed)
	{
		r.stateChange= E_outpostPlayed;
		return r;
	}

	if(copyState->outpostTurn != newState->outpostTurn)
	{
		r.stateChange= E_outpostTurn;
		return r;
	}

	if(copyState->whoseTurn != newState->whoseTurn)
	{
		r.stateChange= E_whoseTurn;
		return r;
	}

	if(copyState->phase != newState->phase)
	{
		r.stateChange= E_phase;
		return r;
	}

	if(copyState->numActions != newState->numActions)
	{
		r.stateChange= E_numActions;
		return r;
	}

	if(copyState->coins != newState->coins)
	{
		r.stateChange= E_coins;
		return r;
	} 

	if(copyState->numBuys != newState->numBuys)
	{
		r.stateChange= E_numBuys;
		return r;
	}

	for(i=0; i<MAX_PLAYERS; i++)
	{
		for(j=0; j<MAX_HAND; j++)
		{
			if(copyState->hand[i][j] != newState->hand[i][j])
			{
				r.stateChange= E_hand;
				r.indexI= i;
				r.indexJ= j;
				return r;
			}
		}
	}

	for(i=0; i<MAX_PLAYERS; i++)
	{
		if(copyState->handCount[i] != newState[i])
		{
			r.stateChange= E_handCount;
			r.indexI= i;
			return r;
		}
	}

	for(i=0; i<MAX_PLAYERS; i++)
	{
		for(j=0; j<MAX_DECK; j++)
		{
			if(copyState->deck[i][j] != newState->deck[i][j])
			{
				r.stateChange= E_deck;
				r.indexI= i;
				r.indexJ= j;
				return r;
			}
		}
	}

	for(i=0; i<MAX_PLAYERS; i++)
	{
		if(copyState->deckCount[i] != newState->deckCount[i])
		{
			r.stateChange= E_deckCount;
			r.indexI= i;
			return r;
		}
	}

	for(i=0; i<MAX_PLAYERS; i++)
	{
		for(j=0; j<MAX_DECK; j++)
		{
			if(copyState->discard[i][j] != newState->discard[i][j])
			{
				r.stateChange= E_discard;
				r.indexI= i;
				r.indexJ= j;
				return r;		
			}
		}
	}

	for(i=0; i<MAX_PLAYERS; i++)
	{
		if(copyState->discardCount[i] != newState->discardCount[i])
		{
				r.stateChange= E_discardCount;
				r.indexI= i;
				return r;
		}
	}

	for(i=0; i<MAX_DECK; i++)
	{
		if(copyState->playedCards[i] != newState->playedCards[i])
		{
				r.stateChange= E_playedCards;
				r.indexI= i;
				return r;
		}
	}

	if(copyState->playedCardCount != newState->playedCardCount)
	{
				r.stateChange= E_playedCardCount;
				return r;
	}
}

int printBadDiffs(struct gameState *copyState, struct gameState *afterCopy, int tests[])
{
	int i;
	struct aChangeReturnVals aDiff= (aChangeReturnVals){-1,-1,-1};

	do
	{
		//compare game state before endTurn is called, to after the call
		aDiff= aChange(afterCopy, copyState);

		switch(aDiff.stateChange)
		{
			case E_numPlayers:
				if(tests[E_numPlayers]==1)  
				{
					printf("Error: numPlayers changed.\n"); 
					printf("numPlayers Before: %d\n", copyState->numPlayers);
					printf("numPlayers After: %d\n\n", afterCopy->numPlayers);				
				}
				afterCopy->numPlayers= copyState->numPlayers;
				break;

			case E_supplyCount: 
				if(tests[E_supplyCount]==1)  
				{
					printf("Error: supplyCount changed.\n"); 
					printf("supplyCount of card#%d Before: %d\n", r.indexI, copyState->supplyCount[r.indexI]);
					printf("supplyCount of card#%d After: %d\n\n", r.indexI, afterCopy->supplyCount[r.indexI]);
				}
				afterCopy->supplyCount[r.indexI]= copyState->supplyCount[r.indexI];
				break;

			case E_embargoTokens: 
				if(tests[E_embargoTokens]==1)  
				{
					printf("Error: embargoTokens changed.\n"); 
					printf("embargoTokens of card#%d Before: %d\n", r.indexI, copyState->embargoTokens[r.indexI]);
					printf("embargoTokens of card#%d After: %d\n\n", r.indexI, afterCopy->embargoTokens[r.indexI]);
				}
				afterCopy->embargoTokens[r.indexI]= copyState->embargoTokens[r.indexI];
				break;

			case E_outpostPlayed: 				
				if(tests[E_outpostPlayed]==1)  
				{
					printf("Error: outpostPlayed changed.\n"); 
					printf("outpostPlayed Before: %d\n", copyState->outpostPlayed);
					printf("outpostPlayed After: %d\n\n", afterCopy->outpostPlayed);
				}
				afterCopy->outpostPlayed= copyState->outpostPlayed;
				break;

			case E_outpostTurn: 
				if(tests[E_outpostTurn]==1)  
				{
					printf("Error: outpostTurn changed.\n"); 
					printf("outpostTurn Before: %d\n", copyState->outpostTurn);
					printf("outpostTurn After: %d\n\n", afterCopy->outpostTurn);
				}
				afterCopy->outpostTurn= copyState->outpostTurn;
				break;

			case E_whoseTurn: 
				if(tests[E_whoseTurn]==1)  
				{
					printf("Error: whoseTurn changed.\n"); 
					printf("whoseTurn Before: %d\n", copyState->whoseTurn);
					printf("whoseTurn After: %d\n\n", afterCopy->whoseTurn);
				}
				afterCopy->whoseTurn= copyState->whoseTurn;
				break;

			case E_phase:
				if(tests[E_phase]==1)  
				{
					printf("Error: phase changed.\n"); 
					printf("phase Before: %d\n", copyState->phase);
					printf("phase After: %d\n\n", afterCopy->phase);
				}
				afterCopy->phase= copyState->phase;
				break;

			case E_numActions: 
				if(tests[E_numActions]==1)  
				{
					printf("Error: numActions changed.\n"); 
					printf("numActions Before: %d\n", copyState->numActions);
					printf("numActions After: %d\n\n", afterCopy->numActions);
				}
				afterCopy->numActions= copyState->numActions;
				break;

			case E_coins: 
				if(tests[E_coins]==1)  
				{
					printf("Error: coins changed.\n"); 
					printf("coins Before: %d\n", copyState->coins);
					printf("coins After: %d\n\n", afterCopy->coins);
				}
				afterCopy->coins= copyState->coins;
				break;

			case E_numBuys: 
				if(tests[E_numBuys]==1)  
				{
					printf("Error: numBuys changed.\n"); 
					printf("numBuys Before: %d\n", copyState->numBuys);
					printf("numBuys After: %d\n\n", afterCopy->numBuys);
				}
				afterCopy->numBuys= copyState->numBuys;
				break;

			case E_hand: 
				if(tests[E_hand]==1)  
				{
					printf("Error: hand changed.\n"); 
					printf("Player#%d hand position#%d Before: %d\n", r.indexI, r.indexJ, copyState->hand[r.indexI][r.indexJ]);
					printf("Player#%d hand position#%d After: %d\n\n", r.indexI, r.indexJ, afterCopy->hand[r.indexI][r.indexJ]);
				}
				afterCopy->hand[r.indexI][r.indexJ]= copyState->hand[r.indexI][r.indexJ];
				break;

			case E_handCount: 
				if(tests[E_handCount]==1)  
				{
					printf("Error: handCount changed.\n"); 
					printf("Player#%d handCount Before: %d\n", r.indexI, copyState->handCount[r.indexI]);
					printf("Player#%d handCount After: %d\n\n", r.indexI, afterCopy->handCount[r.indexI]);
				}
				afterCopy->handCount[r.indexI]= copyState->handCount[r.indexI];
				break;

			case E_deck: 
				if(tests[E_deck]==1)  
				{
					printf("Error: deck changed.\n"); 
					printf("Player#%d deck position#%d Before: %d\n", r.indexI, r.indexJ, copyState->deck[r.indexI][r.indexJ]);
					printf("Player#%d deck position#%d After: %d\n\n", r.indexI, r.indexJ, afterCopy->deck[r.indexI][r.indexJ]);
				}
				afterCopy->deck[r.indexI][r.indexJ]= copyState->deck[r.indexI][r.indexJ];
				break;

			case E_deckCount:
				if(tests[E_deckCount]==1)  
				{
					printf("Error: deckCount changed.\n"); 
					printf("Player#%d deckCount Before: %d\n", r.indexI, copyState->deckCount[r.indexI]);
					printf("Player#%d deckCount After: %d\n\n", r.indexI, afterCopy->deckCount[r.indexI]);
				}
				afterCopy->deckCount[r.indexI]= copyState->deckCount[r.indexI];
				break;

			case E_discard: 
				if(tests[E_discard]==1)  
				{
					printf("Error: discard changed.\n"); 
					printf("Player#%d discard position#%d Before: %d\n", r.indexI, r.indexJ, copyState->deck[r.indexI][r.indexJ]));
					printf("Player#%d discard position#%d After: %d\n\n", r.indexI, r.indexJ, afterCopy->deck[r.indexI][r.indexJ]));
				}
				afterCopy->discard[r.indexI][r.indexJ]= copyState->discard[r.indexI][r.indexJ];
				break;

			case E_discardCount: 
				if(tests[E_discardCount]==1)  
				{
					printf("Error: discardCount changed.\n"); 
					printf("Player#%d discardCount Before: %d\n", r.indexI, copyState->discardCount[r.indexI]);
					printf("Player#%d discardCount After: %d\n\n", r.indexI, afterCopy->discardCount[r.indexI]);
				}
				afterCopy->discardCount[r.indexI]= copyState->discardCount[r.indexI];
				break;

			case E_playedCards: 
				if(tests[E_playedCards]==1)  
				{
					printf("Error: playedCards changed.\n"); 
					printf("playedCard#%d Before: %d\n", r.indexI, copyState->playedCards[r.indexI]);
					printf("playedCard#%d After: %d\n\n", r.indexI, afterCopy->playedCards[r.indexI]);
				}
				afterCopy->playedCards[r.indexI]= copyState->playedCards[r.indexI];
				break;

			case E_playedCardCount: 
				if(tests[E_playedCardCount]==1)  
				{
					printf("Error: playedCardCount changed.\n"); 
					printf("playedCardCount Before: %d\n", copyState->playedCardCount);
					printf("playedCardCount After: %d\n\n", afterCopy->playedCardCount);
				}
				afterCopy->playedCardCount= copyState->playedCardCount;
				break;
		}		
	}
	while(r.stateChange >= 0);
}