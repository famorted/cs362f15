/*	Unit tests for the Adventurer card
		Tests if the player has the correct number of cards and actions
		after using Adventurer
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include "interface.h"

/*adventurer card unit tests*/
int testAdventurerCard(){
	int numPlayer = 2; //players in the game 2-4
	int player = 0; //current player
	int handCount = 5; //Number of cards player starts with
	int i; //counting index for loops
	int hasAdventurer = 0; //Determines if Adventurer card is in player's hand or not.
	char cardName[20]; //name of card
	int numTreasure = 0; //number of treasures in player's hand
	
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
	hand[4] = adventurer;
	
	printf ("Testing adventurerEffect():\n");

	initializeGame(numPlayer, k, 1000, &state); //initialize a new game
	state.handCount[player] = handCount; //set the number of cards in hand
	
	/*give hand to player*/
	memcpy(state.hand[player], hand, sizeof(int) * handCount); 

	/*checks if adventurer is in player's hand*/
	for(i = 0; i < state.handCount[player]; i++){
		cardNumToName(state.hand[player][i], cardName); //get name from card num
		printf("%s ", name);
		if(strcmp(name, "adventurer") == 0){
			hasAdventurer = 1; //Adventurer card is in player's hand
		}
	}
	
	if (hasAdventurer == 1){
		printf ("Player has Adventurer\n");
		printf ("Using Adventurer card\n");
		adventurerEffect(player, state); //uses Adventurer card
		
		/*Adventurer adds 2 treasure cards and discards itself 5+2-1=6*/
		if (state.handCount[player] == 6)
			printf ("Player has the correct number of cards!\n");
		else
			printf("Player has the incorrect number of cards.\n");
		
		/*Adventurer takes one action to play and gives no actions*/
		if (state.numActions == 0)
			printf("Player has the correct number of actions!\n");
		else
			printf("Player has the incorrect number of actions.\n");
		
		/*checks if player has correct number of treasure cards*/
		for(i = 0; i < state.handCount[player]; i++){
			cardNumToName(state.hand[player][i], cardName); //get name from card num
			
			/*counts treasure cards in player's hand*/
			if (strcmp(name, "copper") == 0 || strcmp(name, "silver") == 0 ||
				strcmp(name, "gold") == 0)
			{
				numTreasure++;
			}
			
			/*tests if the user correctly recieved 2 treasures*/
			if(numTreasure == 5)
				printf ("The player has the correct amount of treasure cards!\n");
			else
				printf ("The player incorrectly has %d treasure cards.", numTreasure);
		}
	}
	else{
		printf ("Player does not have Adventurer\n");
	}
	
	return 0;
}

int main(){
	testAdventurerCard();
	return 0;
}