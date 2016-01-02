/*	Unit tests for the Smithy card
		Tests if the player has the correct number of cards after using smithy
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include "interface.h"

/*Smithy card unit tests*/
int testSmithyCard(){
	int numPlayer = 2; //players in the game 2-4
	int player = 0; //current player
	int handCount = 5; //Number of cards player starts with
	int i; //counting index for loops
	int hasSmithy = 0; //Determines if Smithy card is in player's hand or not.
	char cardName[20]; //name of card
	
	/*Kingdom cards in this game*/
	int k[10] = {adventurer, council_room, feast, gardens, mine
				, remodel, smithy, village, baron, great_hall};
			   
	/*starts new game*/
	struct gameState state;
	
	/*create hand*/
	int hand[handCount];
	hand[0] = copper;
	hand[1] = silver;
	hand[2] = gold;
	hand[3] = estate;
	hand[4] = smithy;
	
	printf ("Testing smithyEffect():\n");

	initializeGame(numPlayer, k, 1000, &state); //initialize a new game
	state.handCount[player] = handCount; //set the number of cards in hand
	memcpy(state.hand[player], hand, sizeof(int) * handCount); //give hand to player

	/*checks if smithy is in player's hand*/
	for(i = 0; i < state.handCount[player]; i++){
		cardNumToName(state.hand[player][i], cardName); //get name from card num
		printf("%s ", name);
		if(strcmp(name, "smithy") == 0){
			hasSmithy = 1; //Smithy card is in player's hand
		}
	}
	
	if (hasSmithy == 1){
		printf ("Player has Smithy\n");
		printf ("Using Smithy card\n");
		smithyEffect(player, state, i); //uses smithy card

		/*Smithy adds 3 cards and discards itself 5+3-1==7*/
		if (state.handCount[player] == 7)
			printf ("Player has the correct number of cards!\n");
		else
			printf("Player has the incorrect number of cards.\n");
	}
	else{
		printf ("Player does not have Smithy\n");
	}
	
	return 0;
}

int main(){
	testSmithyCard();
	return 0;
}