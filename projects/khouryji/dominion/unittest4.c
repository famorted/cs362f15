supplyCount[supplyPos] should stay same if already < 1 or should decrease. 
we can add to discard, deck, or hand
check everything

int gainCard(int supplyPos, struct gameState *state, int toFlag, int player)
{
  //Note: supplyPos is enum of choosen card
	
  //check if supply pile is empty (0) or card is not used in game (-1)
  if ( supplyCount(supplyPos, state) < 1 )
    {
      return -1;
    }
	
  //added card for [whoseTurn] current player:
  // toFlag = 0 : add to discard
  // toFlag = 1 : add to deck
  // toFlag = 2 : add to hand

  if (toFlag == 1)
    {
      state->deck[ player ][ state->deckCount[player] ] = supplyPos;
      state->deckCount[player]++;
    }
  else if (toFlag == 2)
    {
      state->hand[ player ][ state->handCount[player] ] = supplyPos;
      state->handCount[player]++;
    }
  else
    {
      state->discard[player][ state->discardCount[player] ] = supplyPos;
      state->discardCount[player]++;
    }
	
  //decrease number in supply pile
  state->supplyCount[supplyPos]--;
	 
  return 0;
}