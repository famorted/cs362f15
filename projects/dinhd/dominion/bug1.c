Dustin Dinh
CS 362 Assignment 3

***********************************  Function Bugs  ***********************************

	1) 	There is a bug with isGameOver(). It goes through all the possible supply cards
		EXCEPT the last two, sea hag and treasure_map. So even if one of these cards 
		has zero supply and there are 2 other cards with zero supply, the game does 
		not end. 

	2) There is a bug with scoreFor(). When calculating the score for discard and 
		deck, the values are wrong because the for loop that iterates over the 
		deck only goes through the deck based on the number of cards in the discard 
		pile, not the actual deck. 

***********************************  Card Bugs  ***********************************
mineCard:

	1) 	The function that checks to see if the cost is affordable has the wrong operator
		It should be  if ( (getCost(state->hand[currentPlayer][choice1]) + 3) < getCost(choice2) )
		not  if ( (getCost(state->hand[currentPlayer][choice1]) + 3) > getCost(choice2) ).

	2) 	It does not check to see if the card being bought is a treasure card. It only checks to 
		see if the card exists. 

	3)	This bug was introduced by me. The input parameters for choice1 and choice2 were swapped. 

minionCard:

	1) 	No matter what the input parameters for choice1 and choice2, it will always give two 
		coins.

	2) 	There is a bug with minionCard. If choice1 is chosen, coins are not added to the state 
		because function minionCard is not able to modify the bonusCoin variable which resides 
		inside of the playcard function.


	3) 	There is a bug with minionCard that I introduced that I cannot test because it is masked 
		by another bug. The game does not store the other player's state (cards in hand, 
		discard etc) until it is that player's turn. As a result I cannot perform tests that 
		depend on the non-active player's state such as discard 

smithyCard:

	1) This bug was introduced by me. 3 cards are discarded instead of 1.

adventureCard: line 684: 1 more card gets discarded but doesn't get removed from the hand.