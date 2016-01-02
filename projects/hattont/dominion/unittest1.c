#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"

int main(int argc, char *argv[]){
    int i = 0;
    printf("unittest4.c\n");
    struct gameState state;
    
    /*Initialize supplyCount to 1 for every card.*/
    for (i = 0; i <= treasure_map; i++) {
        state.supplyCount[i] = 1;
    }

    printf("isGameOver(): %s 1 of every card\n", 
        (!isGameOver(&state)) ? "PASS" : "FAIL" );
    
    state.supplyCount[province] = 0;
    
    printf("isGameOver(): %s province is empty\n", 
        (isGameOver(&state)) ? "PASS" : "FAIL" );    
    
    state.supplyCount[province] = 1;
    state.supplyCount[curse] = 0;
    printf("isGameOver(): %s 1 card is empty\n", 
        (!isGameOver(&state)) ? "PASS" : "PASS" );

    state.supplyCount[minion] = 0;
    printf("isGameOver(): %s 2 cards are empty\n", 
        (!isGameOver(&state)) ? "PASS" : "FAIL" );

    state.supplyCount[treasure_map] = 0;
    printf("isGameOver(): %s 3 cards are empty\n", 
        (isGameOver(&state)) ? "PASS" : "FAIL" );

    return 0;
}