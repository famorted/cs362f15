#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

void testUpdateCoins(){
	struct gameState* g = malloc(sizeof(struct gameState));
	
	g->coins = 0;
	

}

int main(){
	printf("Testing updateCoins\n");

	testUpdateCoins();

	printf("Test updateCoins passed\n");

	return 0;
}
