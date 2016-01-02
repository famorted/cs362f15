#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

//=====================
//TEST ADVENTURER CARD
//=====================

int main() {
    
    printf("\n\nAdventurer Card Test\n\n");
    
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, great_hall, tribute, smithy};
    int i;
    int currentPlayer = 0;
    struct gameState *s;
    printf("Initializing Game...\n");
	initializeGame(2, k, 21, s);

	s->deckCount[1] = rand() % MAX_DECK;
	s->discardCount[1] = rand() % MAX_DECK;
	s->handCount[1] = rand() % MAX_HAND;
	
	cardEffect(adventurer, 0, 0, 0, s, 0, 0);
    
    printf("\n\nAdventurer Card Test Successful!\n\n");
    
    return 0;
}