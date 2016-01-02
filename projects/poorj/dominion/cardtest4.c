/*	Unit tests for the Remodel card
		Tests if the player has the correct number of cards and actions
		after using Remodel
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include "interface.h"

/*Remodel card unit tests*/
int testRemodelCard(){
	int numPlayer = 2; //players in the game 2-4
	int player = 0; //current player
	int handCount = 5; //Number of cards player starts with
	int i; //counting index for loops
	int hasRemodel = 0; //Determines if Remodel card is in player's hand or not.
	char cardName[20]; //name of card
	int numCopper = 0;
	int numSilver = 0; //number of treasures in player's hand
	
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
	hand[4] = remodel;
	
	printf ("Testing RemodelEffect():\n");

	initializeGame(numPlayer, k, 1000, &state); //initialize a new game
	state.handCount[player] = handCount; //set the number of cards in hand
	
	/*give hand to player*/
	memcpy(state.hand[player], hand, sizeof(int) * handCount); 

	/*checks if Remodel is in player's hand*/
	for(i = 0; i < state.handCount[player]; i++){
		cardNumToName(state.hand[player][i], cardName); //get name from card num
		printf("%s ", name);
		if(strcmp(name, "remodel") == 0){
			hasRemodel = 1; //Remodel card is in player's hand
		}
	}
	
	if (hasRemodel == 1){
		printf ("Player has Remodel\n");
		printf ("Using Remodel card\n");
		
		/*uses remodel card from hand[4] to get rid of hand[0] and get enum 5 
		(silver card)*/
		remodelEffect(player, state, 4, 0, 5);
		
		/*checks if player has correct number of each card*/
		for(i = 0; i < state.handCount[player]; i++){
			cardNumToName(state.hand[player][i], cardName); //get name from card num
			
			/*counts copper cards in player's hand*/
			if (strcmp(name, "copper") == 0){
				numCopper++;
			}
			
			/*counts silver cards in player's hand*/
			if (strcmp(name, "silver") == 0){
				numSilver++;
			}
			
			/*tests if the user correctly removed the copper*/
			if(numCopper == 0)
				printf ("The player has the correct amount of copper cards!\n");
			else
				printf ("The player incorrectly has %d copper cards.", numCopper);
			
			/*tests if the user correctly recieved another silver*/
			if(numSilver == 2)
				printf ("The player has the correct amount of silver cards!\n");
			else
				printf ("The player incorrectly has %d silver cards.", numSilver);
		}
	}
	else{
		printf ("Player does not have Remodel\n");
	}
	
	return 0;
}

int main(){
	testRemodelCard();
	return 0;
}