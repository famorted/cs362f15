/*
*	Unit Test 2 for shuffle() in dominion.cabs
*
*	INPUT: shuffle takes as an input a game state and a player identifier
*	OUTPUT: at the end, shuffle seeks to reorder the cards in the players deck
*	
*	TEST: To test, we will:
		1. Fuzz the gameState
		2. Create a new deck of size 0-MAX_DECK
		3. Show that the same cards are still present but (usually) in a different order
*/

#include "dominion.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void fuzzState(struct gameState *);
int randomNumber(int, int);
char * decToChar(char *, int);
char * doubleArrayName(char *str, const char * name, int v1, int v2);
char * singleArrayName(char * str, const char * name, int v);
int compareValues(int a, int b, const char * varName);
int compareStates(struct gameState * a, struct gameState * b, int playerNum);

main(int argc, char * argv[]){
	int unit2_test_trials = 10000;
	int deckRange = MAX_DECK;			//from 0 to deckRange
	
	if (argc > 1) {
		unit2_test_trials = atoi(argv[1]);
		if (unit2_test_trials < 1) {
			printf("Usage: unittest2 <trials>\r\n");
			exit(1);
		}
	}
	
	srand(time(NULL));
	
	//new gameState
	struct gameState * gs = malloc(sizeof(struct gameState));
	struct gameState * stateCopy = malloc(sizeof(struct gameState));
	
	int i;
	int trial;
	int playerNum;
	int returnValue;
	int numberOfErrors = 0;
	
	printf("Unit test 2\r\n");
	printf("Conducting %d random trials.\r\n", unit2_test_trials);
	
	for (trial = 0; trial < unit2_test_trials; trial++) {
		fuzzState(gs);

		//semi-randomize inputs (within reason)
		playerNum = randomNumber(0, MAX_PLAYERS-1);
		gs->deckCount[playerNum] = randomNumber(0, deckRange);
		
		//for later comparison
		memcpy(stateCopy, gs, sizeof(struct gameState));
		
		//perform function
		returnValue = shuffle(playerNum, gs);
		
		if (returnValue > -1) {
			numberOfErrors -= compareStates(gs, stateCopy, playerNum);
		}
	}
	
	printf("Unit Test 2 Complete\r\n");
	printf("Number of errors found: %d\r\n", numberOfErrors);
	

	free(gs);
	free(stateCopy);
	return 0;
}

void fuzzState(struct gameState * state) {
	int i;
	
	unsigned char * ptr = (unsigned char *)state;
	
	for (i = 0; i < sizeof(struct gameState); i++) {
		ptr[i] = (unsigned char)(rand()%256);
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

//compare all a and b except deck
/*struct gameState {
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
};*/
int compareStates(struct gameState * a, struct gameState * b, int playerNum){
	int returnValue = 0;
	int i, j;
	char str[50];
	
	returnValue += compareValues(a->numPlayers, b->numPlayers, "numPlayers");
	
	for (i = 0; i < treasure_map+1; i++) {
		returnValue += compareValues(a->supplyCount[i], b->supplyCount[i], singleArrayName(str, "supplyCount", i));
	}
	
	for (i = 0; i < treasure_map+1; i++) {
		returnValue += compareValues(a->embargoTokens[i], b->embargoTokens[i], singleArrayName(str, "embargoTokens", i));
	}
	
	returnValue += compareValues(a->outpostPlayed, b->outpostPlayed, "outpostPlayed");
	returnValue += compareValues(a->outpostTurn, b->outpostTurn, "outpostTurn");
	returnValue += compareValues(a->whoseTurn, b->whoseTurn, "whoseTurn");
	returnValue += compareValues(a->phase, b->phase, "phase");
	returnValue += compareValues(a->numActions, b->numActions, "numActions");
	returnValue += compareValues(a->coins, b->coins, "coins");
	returnValue += compareValues(a->numBuys, b->numBuys, "numBuys");
	
	for (i = 0; i < MAX_PLAYERS; i++) {
		for (j = 0; j < MAX_HAND; j++) {
			returnValue += compareValues(a->hand[i][j], b->hand[i][j], doubleArrayName(str, "hand", i, j));
		}
	}
	
	for (i = 0; i < MAX_PLAYERS; i++) {
		returnValue += compareValues(a->handCount[i], b->handCount[i], singleArrayName(str, "handCount", i));
	}
	
	//int deckCount[MAX_PLAYERS];
	for (i = 0; i < MAX_PLAYERS; i++) {
		returnValue += compareValues(a->deckCount[i], b->deckCount[i], singleArrayName(str, "deckCount", i));
	}  
  
	//int discard[MAX_PLAYERS][MAX_DECK];
	for (i = 0; i < MAX_PLAYERS; i++) {
		for (j = 0; j < MAX_DECK; j++) {
			returnValue += compareValues(a->discard[i][j], b->discard[i][j], doubleArrayName(str, "discard", i, j));
		}
	}	
	
	//int discardCount[MAX_PLAYERS];
	for (i = 0; i < MAX_PLAYERS; i++) {
		returnValue += compareValues(a->discardCount[i], b->discardCount[i], singleArrayName(str, "discardCount", i));
	} 	
	
	//int playedCards[MAX_DECK];
	for (i = 0; i < MAX_DECK; i++) {
		returnValue += compareValues(a->playedCards[i], b->playedCards[i], singleArrayName(str, "playedCards", i));
	} 
	
	//int playedCardCount;
	returnValue += compareValues(a->playedCardCount, b->playedCardCount, "playedCardCount");
	
	//compare other player's deck
	for (i = 0; i < MAX_PLAYERS; i++) {
		if (i != playerNum) {
			for (j = 0; j < MAX_DECK; j++){
				returnValue += compareValues(a->deck[i][j], b->deck[i][j], doubleArrayName(str, "deck", i, j));
			}
		}
	}
	
	
	/* MAKE SURE THE CARDS STILL EXIST IN DECK */
	
	int card;
	int cardCountA;
	int cardCountB;
	for (i = 0; i < MAX_DECK; i++) {
		card = a->deck[playerNum][i];
		cardCountA = 0;
		cardCountB = 0;
		for(j = 0; j < MAX_DECK; j++) {
			if (a->deck[playerNum][j] == card)
				cardCountA++;
			if (b->deck[playerNum][j] == card)
				cardCountB++;
		}
		if (cardCountA != cardCountB) {
			printf("Card counts in deck don't match.  Card = '%d', Before: %d, After: %d\r\n", card, cardCountB, cardCountA);
			returnValue += -1;
		}
	}
	
	return returnValue;
}

int compareValues(int a, int b, const char * varName) {
	if (a != b) {
		printf("%s does not match.  Before: %d, After: %d\r\n", varName, b, a);
		return -1;
	}
	return 0;
}

char * singleArrayName(char * str, const char * name, int v) {
	char * ptr;
	strcpy(str, name);
	strcat(str, "[");
	ptr = &str[strlen(str)];
	
	ptr = decToChar(ptr, v);
	strcat(str, "]");
	
	return str;
}

char * doubleArrayName(char *str, const char * name, int v1, int v2) {
	char * ptr;
	strcpy(str, name);
	strcat(str, "[");
	
	ptr = &str[strlen(str)];
	ptr = decToChar(ptr, v1);
	strcat(str, "][");
	
	ptr = &str[strlen(str)];	
	ptr = decToChar(ptr, v2);
	strcat(str, "]");	
	
	return str;	
}

char * decToChar(char * s, int v) {
	//BASE
	if (v == 0) {
		s[0] = '0';
		s[1] = '\0';
		return (s+1);
	}
	
	//RECURSIVE
	s = decToChar(s, v/10);
	s[0] = (v % 10) + '0';
	s[1] = '\0';
	return s+1;
}
