/*	Unit tests for the village card
		Tests if the player has the correct number of cards and actions
		after using village
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include "interface.h"

/*Village card unit tests*/
int testVillageCard(){
	int numPlayer = 2; //players in the game 2-4
	int player = 0; //current player
	int handCount = 5; //Number of cards player starts with
	int i; //counting index for loops
	int hasVillage = 0; //Determines if Village card is in player's hand or not.
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
	hand[4] = village;
	
	printf ("Testing villageEffect():\n");

	initializeGame(numPlayer, k, 1000, &state); //initialize a new game
	state.handCount[player] = handCount; //set the number of cards in hand
	memcpy(state.hand[player], hand, sizeof(int) * handCount); //give hand to player

	/*checks if village is in player's hand*/
	for(i = 0; i < state.handCount[player]; i++){
		cardNumToName(state.hand[player][i], cardName); //get name from card num
		printf("%s ", name);
		if(strcmp(name, "village") == 0){
			hasVillage = 1; //village card is in player's hand
		}
	}
	
	if (hasVillage == 1){
		printf ("Player has village\n");
		printf ("Using village card\n");
		villageEffect(player, state, i); //uses village card
		
		/*Village adds 1 card and discards itself*/
		if (state.handCount[player] == 5)
			printf ("Player has the correct number of cards!\n");
		else
			printf("Player has the incorrect number of cards.\n");
		
		/*Village takes one action to play and gives 2 actions 1-1+2=2*/
		if (state.numActions == 2)
			printf("Player has the correct number of actions!\n");
		else
			printf("Player has the incorrect number of actions.\n");
	}
	else{
		printf ("Player does not have village\n");
	}
	
	return 0;
}

int main(){
	testVillageCard();
	return 0;
}