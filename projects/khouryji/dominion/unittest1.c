#include "dominion.h"
#include <cstring>
#include "unittestHelper.h"



//Test function endTurn()
unittest1(struct *gameState state)
{
	int i, b, tests[E_playedCardCount+1]= {0};
	struct gameState copyState, afterCopy;

	//These are state attributes that are expected to change
	//This array will let the change spotter know to ignore changes to these
	//attributes
	test[E_playedCardCount]= 1;
	test[E_hand]= 1;
	test[E_handCount]= 1;
	test[E_deck]= 1;
	test[E_deckCount]= 1;
	test[E_discard]= 1;
	test[E_discardCount]= 1;
	test[E_numBuys]= 1;
	test[E_numActions]= 1;
	test[E_phase]= 1;
	test[E_whoseTurn]= 1;
	test[E_outpostPlayed]= 1;
	test[E_coins]= 1;	
	
	//snapshot of state BEFORE
	makeCopyState(state, &copyState);

	endTurn(state);

	//snapshot of state AFTER
	makeCopyState(state, &afterCopy);
	
	//---------------------------------------
	// Checks all post conditions
	//---------------------------------------

	//playedCard count should be reset to 0
	if(afterCopy.playedCardCount == 0)
		{printf("Test playedCardCount: PASSED\n");}
	else
	{	
		printf("Test playedCardCount: FAILED\n");
		printf("playedCardCount Before: %d\n", copyState.playedCardCount);
		printf("playedCardCount After: %d\n\n", afterCopy.playedCardCount);
	}

	//previous players hand should now be empty
	if(afterCopy.handCount[copyState.whoseTurn] == 0)
		{printf("Test handCount: PASSED\n");}
	else
	{	
		printf("Test handCount: FAILED\n");
		printf("handCount Before: %d\n", copyState.handCount[copyState.whoseTurn]);
		printf("handCount After: %d\n\n", afterCopy.handCount[copyState.whoseTurn]);
	}

	//numBuys should be reset to 1
	if(afterCopy.numBuys == 1)
		{printf("Test numBuys: PASSED\n");}
	else
	{	
		printf("Test numBuys: FAILED\n");
		printf("numBuys Before: %d\n", copyState.numBuys);
		printf("numBuys After: %d\n\n", afterCopy.numBuys);
	}

	//numActions should be reset to 1
	if(afterCopy.numActions == 1)
		{printf("Test numActions: PASSED\n");}
	else
	{	
		printf("Test numActions: FAILED\n");
		printf("numActions Before: %d\n", copyState.numActions);
		printf("numActions After: %d\n\n", afterCopy.numActions);
	}

	//phase should be reset to 0
	if(afterCopy.phase == 0)
		{printf("Test phase: PASSED\n");}
	else
	{	
		printf("Test phase: FAILED\n");
		printf("phase Before: %d\n", copyState.phase);
		printf("phase After: %d\n\n", afterCopy.phase);
	}

	//whoseTurn should be previous whoseTurn +1, or 0 if previous whoseTurn was max index
	if(copyState.whoseTurn == numPlayers-1
	&& afterCopy.whoseTurn == 0)
	{
		printf("Test whoseTurn: PASSED\n");					
	}
	else if(afterCopy.whoseTurn == copyState.whoseTurn + 1)
	{
		printf("Test whoseTurn: PASSED\n");	
	}
	else
	{
		printf("Test whoseTurn: Failed\n");
		printf("whoseTurn Before: %d\n", copyState.whoseTurn);
		printf("whoseTurn After: %d\n\n", afterCopy.whoseTurn);
	}

	//outpostPlayed should be reset to 0
	if(afterCopy.outpostPlayed == 0)
		{printf("Test outpostPlayed: PASSED\n");}
	else
	{	
		printf("Test outpostPlayed: FAILED\n");
		printf("outpostPlayed Before: %d\n", copyState.outpostPlayed);
		printf("outpostPlayed After: %d\n\n", afterCopy.outpostPlayed);
	}

	//discard count of previous whoseTurn should be increased by previous whoseTurn hand count 
	if(afterCopy.discardCount[copyState.whoseTurn] == copyState.discardCount[copyState.whoseTurn] + copyState.handCount[copyState.whoseTurn])
	{
		printf("Test discardCount: PASSED\n");
	}	
	else
	{
		printf("Test discardCount: FAILED\n");
		printf("discardCount Before: %d\n");
		printf("discardCount After: %d\n\n");
	}

	//discard pile of the previous whoseTurn should include the cards from previous whoseTurn hand, in order
	b=0;
	for(i=0; i<copyState.handCount[copyState.whoseTurn]; i++)
	{
		if(afterCopy.discard[copyState.whoseTurn][copyState.discardCount+i] != copyState.hand[copyState.whoseTurn][i])
		{
			printf("Test discard: FAILED");
			printf("Error: last user's hand was not properly put into the discard pile.\n");
			printf("Card#%d expected in player#%d's discard pile position#%d\n", copyState.hand[copyState.whoseTurn][i], copyState.whoseTurn, copyState.discardCount+i);
			b= 1;
		}
	}
	if(!b)
	{
		printf("Test discard: PASSED\n");
	}
	
	//current whoseTurn handCount should be 5
	if(afterCopy.handCount[afterCopy.whoseTurn] == 5)
	{
		printf("Test handCount current player: Passed\n");
	}
	else
	{
		printf("Error: current player should have a handCount of 5.\n");
		printf("Actual handCount: %d\n", afterCopy.handCount[afterCopy.whoseTurn]);
	}

	//previous whoseTurn handCount should be 0
	if(afterCopy.handCount[copyState.whoseTurn] == 0)
	{
		printf("Test handCount previous player: Passed\n");
	}
	else
	{
		printf("Error: previous player should have a handCount of 0.\n");
		printf("Actual handCount: %d\n", afterCopy.handCount[copyState.whoseTurn]);
	}

	//Find all changes to gamestate and print errors if changes were not expected
	int printBadDiffs(&copyState, &afterCopy);	
		

}


