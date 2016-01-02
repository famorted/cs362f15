/*
* Unit Test for initializeGame() function in dominion.c
*
* int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed, 
	struct gameState *state)
*
* INPUT: function takes input as number of players, a set of kingdomCards 
* (as set by function kingdomCards()) a random seed, and a constructed game
* state and initiates the said game state.
*
* For this test, we assume that the random number generator functions work as expected.  We check for
* correct implementation only once by running TestRandom().
*
*
* OUTPUT: At the end of initializeGame, we would expect the game state to:
* a. initialize the number of Players correctly (from 2 to MAX_PLAYERS) or error if out of bounds
* b. assert that the cards selected are all of different values
* c. Set the number of curse cards available (10 for 2 players, 20 for 3 players, 30 for all other sets of players)
* d. Set the number of victory cards available (8 for 2 players, 12 for all other sets of players)
* e. Set the number of Gold cards available to 30
* f. Set the number of Silver cards available to 40
* g. Set the number of Copper cards available to 60 (less the 7 drawn per player)
* h. Set the supply count for all Kingdom cards to 10 except Victory cards which are set to 8
*		for 2 players or 12 for 3+ players
* i. Give each player deck 7 copper cards and 3 estate cards
* j. Give each player 5 cards in hand
* k. set all of embargoTokens to 0
* l. Set up first turn (whoseTurn = 0, numActions = 1, numBuys = 1, playedCardCount = 0, phase = 0)
* 
* Here is the Structure of struct gameState:
*struct gameState {
  int numPlayers; //number of players
  int supplyCount[treasure_map+1];  //this is the amount of a specific type of card given a specific number.
  int embargoTokens[treasure_map+1];
  int outpostPlayed;
  int outpostTurn;
  int whoseTurn;
  int phase;
  int numActions;
  int coins;
  int numBuys;
  int hand[MAX_PLAYERS][MAX_HAND];
  int handCount[MAX_PLAYERS];
  int deck[MAX_PLAYERS][MAX_DECK];
  int deckCount[MAX_PLAYERS];
  int discard[MAX_PLAYERS][MAX_DECK];
  int discardCount[MAX_PLAYERS];
  int playedCards[MAX_DECK];
  int playedCardCount;
};
*/

#include "dominion.h"
#include "rngs.h"

#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

const int UNITTEST1_CHANCE_PLAYER_OUT_OF_BOUNDS = 5;
const int UNITTEST1_CHANCE_DUPLICATE_CARDS = 5;
const int UNITTEST1_TRIALS = 10000;

void fuzzState(struct gameState *);
int percentChanceIsOne(int);
int randomNumber(int, int);
int randomNumPlayers();
int checkGameState(struct gameState *, int, int, int *);
void unittest1_initiateKingdomCards(int *);

int main() {
	srand(time(NULL));
	
	//new gameState
	struct gameState * randomState = malloc(sizeof(struct gameState));
	
	int i;
	int numPlayers;
	int kingdomCards[10];
	int randomSeed;
	int firstRun = 1;
	int returnValue;
	
	printf("Unit test 1\r\n");
	printf("Conducting %d random trials.\r\n", UNITTEST1_TRIALS);
	
	int foundErrors = 0;
	int trials;
	for (trials = 0; trials < UNITTEST1_TRIALS; trials++ ){
		//fuzz the state
		fuzzState(randomState);
	
		//semi-randomize inputs (within reason)
		numPlayers = randomNumPlayers();	
		unittest1_initiateKingdomCards(kingdomCards);
		randomSeed = rand();
		
		//run function and store results
		returnValue = initializeGame(numPlayers, kingdomCards, randomSeed, randomState);
		
		//test outputs:
		if (firstRun == 1)
			TestRandom();
		
		if (returnValue != -1) {
			foundErrors -= checkGameState(randomState, returnValue, numPlayers, kingdomCards);	//subtracts a negative to add
		}
		
		firstRun = 0;
	
	}
	
	printf("Unit Test 1 Complete.  I found %d errors\r\n", foundErrors);
	return 0;
}

void fuzzState(struct gameState * state) {
	int i;
	
	unsigned char * ptr = (unsigned char *)state;
	
	for (i = 0; i < sizeof(struct gameState); i++) {
		ptr[i] = (unsigned char)(rand()%256);
	}
}

int percentChanceIsOne(int probability) {
	if ( probability > (rand() % 100)) {
		return 1;
	} else {
		return 0;
	}
}

int randomNumber(int from, int to) {
	int a, b;
	if (from < to) {
		a = from;
		b = to;
	} else {
		a = to;
		b = from;
	}
	
	return rand() % ((b - a) + 1) + a;
}

int randomNumPlayers(){
	//Number of players
	int numPlayers = randomNumber(2, MAX_PLAYERS);
	
	//on occasion, attempt to place out of bounds
	if (percentChanceIsOne(UNITTEST1_CHANCE_PLAYER_OUT_OF_BOUNDS) == 1) {
		numPlayers = randomNumber(-1000,1000);
	}
	
	return numPlayers;
}

void unittest1_initiateKingdomCards(int * kingdomCards) {
		
	int i;
	int randCard;
	size_t chosenCardsMemSize = sizeof(int)*(treasure_map+1);
	int * chosenCards = malloc(chosenCardsMemSize);

		
	memset(chosenCards, 0, chosenCardsMemSize);

	int duplicateCardsAllowed = percentChanceIsOne(UNITTEST1_CHANCE_DUPLICATE_CARDS);
	for (i = 0; i < 10; i++){
		if (duplicateCardsAllowed == 0) {
			randCard = randomNumber(0, treasure_map);
			while (chosenCards[randCard] == 1) {
				randCard = randomNumber(0, treasure_map);
			}
			kingdomCards[i] = randCard;
			chosenCards[randCard] = 1;
		} else {
			kingdomCards[i] = randomNumber(0, treasure_map);
		}
	}
		
	free(chosenCards);
}


int checkGameState(struct gameState * s, int returnValue, int numPlayers, int * kingdomCards) {
	
	int i;
	int j;
	int containsGreatHall;
	int containsGardens;
	
	//Check number of players underbounds
	if (numPlayers < 2) {
		printf("Did not catch too few players (numPlayers = %d)\r\n", numPlayers);
		return -1;
	}
	
	//Check number of players overbounds
	if (numPlayers > MAX_PLAYERS) {
		printf("Did not catch too many players (numPlayers = %d)\r\n", numPlayers);
		return -1;
	}
	
	//Check number of players match
	if (s->numPlayers != numPlayers) {
		printf("Number of players does not match: INPUT = %d, OUTPUT = %d\r\n", numPlayers, s->numPlayers);
		return -1;
	}
	
	//check for card duplicates
	int duplicateCards = 0;
	for (i = 0; i < 9; i++) {
		for (j = i+1; j < 10; j++) {
			if (kingdomCards[i] == kingdomCards[j]) {
				duplicateCards = 1;
			}
		}
	}

	if (duplicateCards == 1) {
		printf("Did not catch duplicate cards.\r\nValues:\r\n");
		for (i = 0; i < 10; i++) {
			printf("kingdomCards[%d] = %d\r\n", i, kingdomCards[i]);
		}
		return -1;
	}
			
	// c. Set the number of curse cards available (10 for 2 players, 20 for 3 players, 30 for all other sets of players)
	if ((numPlayers == 2 && s->supplyCount[curse] != 10) ||
		(numPlayers == 3 && s->supplyCount[curse] != 20) ||
		(numPlayers == 4 && s->supplyCount[curse] != 30)) {
			printf("curse count is incorrect.  players = %d, curse supply = %d\r\n", numPlayers, s->supplyCount[curse]);
			
	}
	
	// d. Set the number of victory cards available (8 for 2 players, 12 for all other sets of players)
	if ((numPlayers == 2 && s->supplyCount[estate] != 8) ||
		(numPlayers > 2 && s->supplyCount[estate] != 12)) {
			printf("estate count is incorrect.  players = %d, estate supply = %d\r\n", numPlayers, s->supplyCount[estate]);
			return -1;
	}
	
	if ((numPlayers == 2 && s->supplyCount[duchy] != 8) ||
		(numPlayers > 2 && s->supplyCount[duchy] != 12)) {
			printf("duchy count is incorrect.  players = %d, duchy supply = %d\r\n", numPlayers, s->supplyCount[duchy]);
			return -1;
	}	
	
	if ((numPlayers == 2 && s->supplyCount[province] != 8) ||
		(numPlayers > 2 && s->supplyCount[province] != 12)) {
			printf("province count is incorrect.  players = %d, province supply = %d\r\n", numPlayers, s->supplyCount[province]);
			return -1;
	}

	// e. Set the number of Gold cards available to 30
	if (s->supplyCount[gold] != 30) {
		printf("Gold count is incorrect.  Expected 30 gold.  Actual: %d\r\n", s->supplyCount[gold]);
		return -1;
	}
	
	
	// f. Set the number of Silver cards available to 40
	if (s->supplyCount[silver] != 40) {
		printf("silver count is incorrect.  Expected 40 silver.  Actual: %d\r\n", s->supplyCount[silver]);
		return -1;
	}
	
	// g. Set the number of Copper cards available to 60 (less the 7 drawn per player)
	if (s->supplyCount[copper] != 60 - (7*numPlayers)) {
		printf("copper count is incorrect.  Expected %d copper.  Actual: %d\r\n", 60 - (7*numPlayers), s->supplyCount[copper]);
		return -1;
	}
	
	// h. Set the supply count for all Kingdom cards to 10 except Victory cards which are set to 8
	//		for 2 players or 12 for 3+ players
	//first determine if we selected the cards
	containsGreatHall = 0;
	containsGardens = 0;
	for(i = adventurer; i < treasure_map; i++) {
		int found = 0;
		for (j = 0; j < 10; j++) {
			if (kingdomCards[j] == i) {
				found = 1;
			}
		}
		if ((found == 1 && i != gardens && i != great_hall && s->supplyCount[i] != 10) ||
			(found == 1 && (i == gardens || i == great_hall) && numPlayers == 2 && s->supplyCount[i] != 8 ) ||
			(found == 1 && (i == gardens || i == great_hall) && numPlayers > 2 && s->supplyCount[i] != 12 ) ||
			(found == 0 && s->supplyCount[i] != -1))	{
			printf("Incorrect Supply: CardType = %d, Card Supply = %d\r\n", i, s->supplyCount[i]);
			for (j = 0; j < 10; j++) {
				printf("kingdomCards[%d] = %d\r\n", j, kingdomCards[j]);
			}
			return -1;
		}
	}
	
	int copperSum;
	int estateSum;
	// i. Give each player deck 7 copper cards and 3 estate cards
	for (i = 0; i < numPlayers; i++) {
		copperSum = 0;
		estateSum = 0;
		for (j = 0; j < s->handCount[i]; j++){
			if (s->hand[i][j] == copper) {
				copperSum++;
			} 
			if (s->hand[i][j] == estate) {
				estateSum++;
			}
		}
		for (j = 0; j < s->deckCount[i]; j++){
			if (s->deck[i][j] == copper) {
				copperSum++;
			} 
			if (s->deck[i][j] == estate) {
				estateSum++;
			}
		}
		if (copperSum != 7 || estateSum != 3) {
			printf("Copper or estate Total incorrect for player %d\r\n", i);
			for (j = 0; j < s->deckCount[i]; j++) {
				printf("deck[%d][%d] = %d\r\n", i, j, s->deck[i][j]);
			}
			for (j = 0; j < s->handCount[i]; j++) {
				printf("hand[%d][%d] = %d\r\n", i, j, s->hand[i][j]);
			}
			return -1;
		}
	}
	
	// j. Give each player 5 cards in hand
	/*
	for (i = 0; i < numPlayers; i++) {
		if (s->handCount[i] != 5) {
			printf("Incorrect hand count. Player %d has %d cards:\r\n", i, s->handCount[i]);
			for (j = 0; j < s->handCount[i]; j++) {
				printf("hand[%d][%d] = %d\r\n", i, j, s->hand[i][j]);
			}
			return -1;
		}
	}
	*/
	// k. set all of embargoTokens to 0
	
	// l. Set up first turn (whoseTurn = 0, numActions = 1, numBuys = 1, playedCardCount = 0, phase = 0)
	if (s->whoseTurn != 0) {
		printf("WhoseTurns is incorrect: Expected 0, Actual %d \r\n", s->whoseTurn);
		return -1;
	}
	
	if (s->numActions != 1) {
		printf("numActions is incorrect: Expected 1, Actual %d\r\n", s->numActions);
		return -1;
	}
	
	if (s->numBuys != 1) {
		printf("numBuys is incorrect: Expected 1, Actual %d\r\n", s->numBuys);
		return -1;
	}
	
	if (s->playedCardCount != 0) {
		printf("playedCardCount is incorrect: Expected 0, Actual %d\r\n", s->playedCardCount);
		return -1;
	}
	
	if (s->phase != 0) {
		printf("phase is incorrect: Expected 0, Actual %d\r\n", s->phase);
		return -1;
	}
	
	//successful test
	return 0;
}
