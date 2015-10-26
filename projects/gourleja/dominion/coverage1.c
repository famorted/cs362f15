Jason Gourley
gourleja@oregonstate.edu
CS362-400
Assignment 3 - coverage1.c
Description : Coverage results from unit tests
-------------------------------------------------------------------------------
Coverage findings

After building the unit tests and running them it was interesting to look at the gcov results as well as tracing the calls debugging with ddd.  With this being my first real big dive into using gcov and analyzing the results it seemed like the coverage levels were fairly good.  

For coverage my first step in adding tests was slightly different for the methods verses the cards.  First I started with the methods, which from their names at least gave a clue to how they should function.  Since there is not documentation for the dominion code included for the methods it took time looking through the code and the branching within the code to determine what game states and variables would need to be in place to test the accuracy of the method.  I tried to break down what I would need to enter each branch of the source code and then added a test for each.  This approach works in the case with access to source code, however I'm not sure how one would go about building test cases while black box testing without relying on random testing to do so.  

Viewing the gcov output was helpful to see where there were cases I was miss handling.  I also used ddd to visualize the debugging process and track variables at run-time.  I found this to be a crucial step to understanding how the code was run on certain calls and what internal calls were made that I didn't realize at first glance.  

When I started on the card unit tests my first step was to look at the dominion game documentation as a base.  Without knowing anything about the internals of the program more like black box testing I could create test cases based on the card descriptions to verify whether or not the card's method was producing expected results.  After getting some of these core test cases in place I took a closer look at the implementation to see if there were areas that I was not touching upon in the tests.

I do believe the unit tests do a good job of testing the statements and branches within the code, although I don't know that I have much for good coverage for boundary cases.  Having an understanding of the cards being tested and how they should affect the game state helped to make these unit tests fairly straight forward.  Figuring out base test cases were relatively easy, but understanding how the game state was being changed in more complex card actions was a much more difficult task.  

As far as the boundary cases were concerned with all unit tests it was something that took quite a bit of investigation and though.  Especially in areas where additional method calls were being made by the tested method, which could also be making adjustments to the game state that were out of my control simply with unit tests.  How the method calls were being made internally was not something I had thought about an initial concern, but I soon realized that testing methods that were not atomic would cause potential issues with tracking down bugs and how the data was being handled after the initial method call.

The addition of coverage information helped greatly to better understand how the tests were actually running and helped to also guide better targeted debugging during development.



-------------------------------------------------------------------------------
Unit Test gcov results:

File 'cardtest4.c'
Lines executed:78.95% of 57
cardtest4.c:creating 'cardtest4.c.gcov'

        -:    0:Source:unittest1.c
        -:    0:Graph:unittest1.gcno
        -:    0:Data:unittest1.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:/*
        -:    2: * Jason Gourley
        -:    3: * gourleja@oregonstate.edu
        -:    4: * CS362-400
        -:    5: * Assignment 3 - unittest1.c
        -:    6: * Description : Unit tests for isGameOver method
        -:    7: */
        -:    8:
        -:    9:#include <stdio.h>
        -:   10:#include <stdlib.h>
        -:   11:#include "dominion.h"
        -:   12:#include "rngs.h"
        -:   13:
        -:   14:#define METHODNAME  "isGameOver"
        -:   15:#define BASESEED    10
        -:   16:
        -:   17:/*
        -:   18: * Description:     Test the return values of the isGameOver method
        -:   19: * Preconditions:   The games state has been initialized, the seed and method name to test are passed
        -:   20: * Postconditions:  The general messages and any failed test messages are displayed
        -:   21: */
        1:   22:int testMethod(char* currentTest, int seed, struct gameState *state)
        -:   23:{
        -:   24:    int i;
        1:   25:    int testsPassed = 0;
        1:   26:    int testsFailed = 0;
        1:   27:    int expectedValue = 0;
        -:   28:
        1:   29:    printf ("\n\n-------------------------------------------------------------------------------\n");
        1:   30:    printf ("-------------------------------------------------------------------------------\n");
        1:   31:    printf ("Testing Method  : %s()\n", currentTest);
        1:   32:    printf ("Seed            : %i\n", seed);
        -:   33:
        -:   34:    //check new game produces the correct value
        1:   35:    expectedValue = 1;
        1:   36:    if(isGameOver(state) == expectedValue) {
    #####:   37:        printf("  TEST FAIL    : Newly initialized game failed\n");
    #####:   38:        testsFailed++;
        1:   39:    } else {testsPassed++;}
        -:   40:
        -:   41:    //check a lack of province cards produces the correct value
        1:   42:    expectedValue = 0;
        1:   43:    state->supplyCount[province] = 0;
        1:   44:    if(isGameOver(state) == expectedValue) {
    #####:   45:        printf("  TEST FAIL    : Province supply out check failed\n");
    #####:   46:        testsFailed++;
        1:   47:    } else {testsPassed++;}
        -:   48:
        -:   49:    //check that when 3 supply piles are empty produces the correct value
        1:   50:    expectedValue = 0;
        1:   51:    state->supplyCount[province] = 1;
        4:   52:    for(i=0; i<3; i++){
        3:   53:        state->supplyCount[i] = 0;
        -:   54:    }
        1:   55:    if(isGameOver(state) == expectedValue) {
    #####:   56:        printf("  TEST FAIL    : 3 card supply out check failed\n");
    #####:   57:        testsFailed++;
        1:   58:    } else {testsPassed++;}
        -:   59:
        1:   60:    printf ("    Tests Passed    : %i\n", testsPassed);
        1:   61:    printf ("    Tests Failed    : %i\n", testsFailed);
        1:   62:    printf ("-------------------------------------------------------------------------------\n\n");
        -:   63:
        1:   64:    return 0;
        -:   65:}
        -:   66:
        -:   67:
        -:   68:/*
        -:   69: * Preconditions:   The user can pass a seed value for testing or it defaults to a set value
        -:   70: * Postconditions:  Exit the test program normally
        -:   71: */
        1:   72:int main (int argc, char** argv)
        -:   73:{
        -:   74:
        -:   75:    // Setup Game Seed
        -:   76:    int seed;
        1:   77:    char* currentTest = METHODNAME;
        1:   78:    if(argv[1]) {
    #####:   79:        seed = atoi(argv[1]);
        -:   80:    } else {
        1:   81:        seed = BASESEED;
        -:   82:    }
        -:   83:
        -:   84:    // Initialize Game State
        -:   85:    struct gameState G;
        1:   86:    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
        1:   87:    initializeGame(2, k, seed, &G);
        -:   88:
        1:   89:    testMethod(currentTest,seed, &G);
        1:   90:    return 0;
        -:   91:}
        -:   92:
        -:    0:Source:unittest2.c
        -:    0:Graph:unittest2.gcno
        -:    0:Data:unittest2.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:/*
        -:    2: * Jason Gourley
        -:    3: * gourleja@oregonstate.edu
        -:    4: * CS362-400
        -:    5: * Assignment 3 - unittest2.c
        -:    6: * Description : Unit tests for buyCard method
        -:    7: */
        -:    8:
        -:    9:#include <stdio.h>
        -:   10:#include <stdlib.h>
        -:   11:#include "dominion.h"
        -:   12:#include "rngs.h"
        -:   13:
        -:   14:#define METHODNAME  "buyCard"
        -:   15:#define BASESEED    10
        -:   16:
        -:   17:/*
        -:   18: * Description:     Test the return values of the buyCard method
        -:   19: * Preconditions:   The games state has been initialized, the seed and method name to test are passed
        -:   20: * Postconditions:  The general messages and any failed test messages are displayed
        -:   21: */
        1:   22:int testMethod(char* currentTest, int seed, struct gameState *state)
        -:   23:{
        -:   24:    int i;
        1:   25:    int testsPassed = 0;
        1:   26:    int testsFailed = 0;
        1:   27:    int expectedValue = 0;
        1:   28:    int expectedState = 0;
        -:   29:
        1:   30:    printf ("\n\n-------------------------------------------------------------------------------\n");
        1:   31:    printf ("-------------------------------------------------------------------------------\n");
        1:   32:    printf ("Testing Method  : %s()\n", currentTest);
        1:   33:    printf ("Seed            : %i\n", seed);
        -:   34:
       26:   35:    for(i=0; i<25; i++){
       25:   36:        state->supplyCount[i] = 1;
        -:   37:    }
        -:   38:
        1:   39:    int supplyPos = 1;
        -:   40:
        -:   41:    //check lack of buys produces the correct error
        1:   42:    expectedValue = -1;
        1:   43:    state->numBuys = 0;
        1:   44:    if(buyCard(supplyPos,state) != expectedValue) {
    #####:   45:        printf("  TEST FAIL    : No buys left check failed\n");
    #####:   46:        testsFailed++;
        1:   47:    } else {testsPassed++;}
        -:   48:
        -:   49:    //check lack of cards
        1:   50:    state->numBuys = 1;
        1:   51:    state->supplyCount[supplyPos] = 0;
        1:   52:    if(buyCard(supplyPos,state) != expectedValue) {
    #####:   53:        printf("  TEST FAIL    : No cards left check failed\n");
    #####:   54:        testsFailed++;
        1:   55:    } else {testsPassed++;}
        1:   56:    state->supplyCount[supplyPos] = 1;
        -:   57:
        -:   58:    //check lack of coins produces the correct error
        1:   59:    state->numBuys = 1;
        1:   60:    state->coins = 0;
        1:   61:    supplyPos = 1;
        1:   62:    if(buyCard(supplyPos,state) != expectedValue) {
    #####:   63:        printf("  TEST FAIL    : No coins left check failed\n");
    #####:   64:        testsFailed++;
        1:   65:    } else {testsPassed++;}
        -:   66:
        -:   67:    //check coin value is correct after call
        1:   68:    state->numBuys = 1;
        1:   69:    state->coins = 5;
        1:   70:    expectedValue = 0;
        1:   71:    if(buyCard(supplyPos,state) != expectedValue || state->coins != 3) {
    #####:   72:        printf("  TEST FAIL    : coins value check failed\n");
    #####:   73:        testsFailed++;
        1:   74:    } else {testsPassed++;}
        -:   75:
        -:   76:    //check numbuys value is correct after call
        1:   77:    state->numBuys = 1;
        1:   78:    state->coins = 5;
        1:   79:    state->supplyCount[1] = 1;
        1:   80:    expectedState = 0;
        1:   81:    int buyCardTest = buyCard(supplyPos,state);
        1:   82:    if(buyCardTest != expectedValue || state->numBuys != expectedState) {
    #####:   83:        printf("  TEST FAIL    : numBuys value check failed, %i, %i\n", buyCardTest, state->numBuys);
    #####:   84:        testsFailed++;
        1:   85:    } else {testsPassed++;}
        -:   86:
        -:   87:    // Check card taken has supply reduced
        1:   88:    state->numBuys = 1;
        1:   89:    state->coins = 5;
        1:   90:    state->supplyCount[1] = 1;
        1:   91:    expectedValue = state->supplyCount[supplyPos] - 1;
        1:   92:    int testBuy = buyCard(supplyPos,state);
        1:   93:    if(state->supplyCount[supplyPos] != expectedValue) {
    #####:   94:        printf("  TEST FAIL    : Card supply value reduced correctly check failed\n");
    #####:   95:        testsFailed++;
        1:   96:    } else {testsPassed++;}
        -:   97:
        1:   98:    printf ("    Tests Passed    : %i\n", testsPassed);
        1:   99:    printf ("    Tests Failed    : %i\n", testsFailed);
        1:  100:    printf ("-------------------------------------------------------------------------------\n\n");
        -:  101:
        1:  102:    return 0;
        -:  103:}
        -:  104:
        -:  105:
        -:  106:/*
        -:  107: * Preconditions:   The user can pass a seed value for testing or it defaults to a set value
        -:  108: * Postconditions:  Exit the test program normally
        -:  109: */
        1:  110:int main (int argc, char** argv)
        -:  111:{
        -:  112:
        -:  113:    // Setup Game Seed
        -:  114:    int seed;
        1:  115:    char* currentTest = METHODNAME;
        1:  116:    if(argv[1]) {
    #####:  117:        seed = atoi(argv[1]);
        -:  118:    } else {
        1:  119:        seed = BASESEED;
        -:  120:    }
        -:  121:
        -:  122:    // Initialize Game State
        -:  123:    struct gameState G;
        1:  124:    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
        1:  125:    initializeGame(2, k, seed, &G);
        -:  126:
        1:  127:    testMethod(currentTest,seed, &G);
        1:  128:    return 0;
        -:  129:}
        -:    0:Source:unittest3.c
        -:    0:Graph:unittest3.gcno
        -:    0:Data:unittest3.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:/*
        -:    2: * Jason Gourley
        -:    3: * gourleja@oregonstate.edu
        -:    4: * CS362-400
        -:    5: * Assignment 3 - unittest3.c
        -:    6: * Description : Unit tests for playCard method
        -:    7: */
        -:    8:
        -:    9:#include <stdio.h>
        -:   10:#include <stdlib.h>
        -:   11:#include "dominion.h"
        -:   12:#include "rngs.h"
        -:   13:
        -:   14:#define METHODNAME  "playCard"
        -:   15:#define BASESEED    10
        -:   16:
        -:   17:/*
        -:   18: * Description:     Test the return values of the playCard method
        -:   19: * Preconditions:   The games state has been initialized, the seed and method name to test are passed
        -:   20: * Postconditions:  The general messages and any failed test messages are displayed
        -:   21: */
        1:   22:int testMethod(char* currentTest, int seed, struct gameState *state)
        -:   23:{
        -:   24:    int i;
        1:   25:    int testsPassed = 0;
        1:   26:    int testsFailed = 0;
        1:   27:    int expectedValue = 0;
        1:   28:    int expectedState = 0;
        1:   29:    int actualValue = 0;
        1:   30:    int actualState = 0;
        -:   31:
        1:   32:    printf ("\n\n-------------------------------------------------------------------------------\n");
        1:   33:    printf ("-------------------------------------------------------------------------------\n");
        1:   34:    printf ("Testing Method  : %s()\n", currentTest);
        1:   35:    printf ("Seed            : %i\n", seed);
        -:   36:
        1:   37:    int supplyPos = 1;
        -:   38:
        -:   39:    //check incorrect phase produces the correct error value
        1:   40:    expectedValue = -1;
        1:   41:    state->phase = 0;
        1:   42:    actualValue = playCard(0, -1, -1, -1, state);
        1:   43:    if(actualValue != expectedValue) {
    #####:   44:        printf("  TEST FAIL    : Phase check failed\n");
    #####:   45:        testsFailed++;
        1:   46:    } else {testsPassed++;}
        -:   47:
        -:   48:    //check incorrect phase produces the correct error value
        1:   49:    expectedValue = -1;
        1:   50:    state->numActions = 0;
        1:   51:    actualValue = playCard(0, -1, -1, -1, state);
        1:   52:    if(actualValue != expectedValue) {
    #####:   53:        printf("  TEST FAIL    : Phase check failed\n");
    #####:   54:        testsFailed++;
        1:   55:    } else {testsPassed++;}
        -:   56:
        -:   57:    //check incorrect card type produces the correct error value
        1:   58:    expectedValue = -1;
        1:   59:    state->numActions = 1;
        1:   60:    state->hand[whoseTurn(state)][0] = 0;
        1:   61:    actualValue = playCard(0, -1, -1, -1, state);
        1:   62:    if(actualValue != expectedValue) {
    #####:   63:        printf("  TEST FAIL    : Action card check failed\n");
    #####:   64:        testsFailed++;
        1:   65:    } else {testsPassed++;}
        -:   66:
        -:   67:    //check for correct action decrement value
        1:   68:    expectedValue = 0;
        1:   69:    state->numActions = 1;
        1:   70:    state->hand[whoseTurn(state)][0] = 7;
        1:   71:    actualValue = playCard(0, -1, -1, -1, state);
        1:   72:    if(actualValue != expectedValue) {
    #####:   73:        printf("  TEST FAIL    : Actions decrement check failed\n");
    #####:   74:        testsFailed++;
        1:   75:    } else {testsPassed++;}
        -:   76:
        -:   77:    //check for correct coin increment value
        1:   78:    expectedValue = state->coins + 2;
        1:   79:    state->numActions = 2;
        1:   80:    state->hand[whoseTurn(state)][0] = 17;
        1:   81:    actualValue = playCard(0, 1, -1, -1, state);
        1:   82:    if(state->coins != expectedValue) {
        1:   83:        printf("  TEST FAIL    : Coin increment check failed\n");
        1:   84:        testsFailed++;
    #####:   85:    } else {testsPassed++;}
        -:   86:
        1:   87:    printf ("    Tests Passed    : %i\n", testsPassed);
        1:   88:    printf ("    Tests Failed    : %i\n", testsFailed);
        1:   89:    printf ("-------------------------------------------------------------------------------\n\n");
        -:   90:
        1:   91:    return 0;
        -:   92:}
        -:   93:
        -:   94:
        -:   95:/*
        -:   96: * Preconditions:   The user can pass a seed value for testing or it defaults to a set value
        -:   97: * Postconditions:  Exit the test program normally
        -:   98: */
        1:   99:int main (int argc, char** argv)
        -:  100:{
        -:  101:
        -:  102:    // Setup Game Seed
        -:  103:    int seed;
        1:  104:    char* currentTest = METHODNAME;
        1:  105:    if(argv[1]) {
    #####:  106:        seed = atoi(argv[1]);
        -:  107:    } else {
        1:  108:        seed = BASESEED;
        -:  109:    }
        -:  110:
        -:  111:    // Initialize Game State
        -:  112:    struct gameState G;
        1:  113:    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
        1:  114:    initializeGame(2, k, seed, &G);
        -:  115:
        1:  116:    testMethod(currentTest,seed, &G);
        1:  117:    return 0;
        -:  118:}
        -:    0:Source:unittest4.c
        -:    0:Graph:unittest4.gcno
        -:    0:Data:unittest4.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:/*
        -:    2: * Jason Gourley
        -:    3: * gourleja@oregonstate.edu
        -:    4: * CS362-400
        -:    5: * Assignment 3 - unittest4.c
        -:    6: * Description : Unit tests for endTurn method
        -:    7: */
        -:    8:
        -:    9:#include <stdio.h>
        -:   10:#include <stdlib.h>
        -:   11:#include "dominion.h"
        -:   12:#include "rngs.h"
        -:   13:
        -:   14:#define METHODNAME  "endTurn"
        -:   15:#define BASESEED    10
        -:   16:
        -:   17:/*
        -:   18: * Description:     Test the return values of the endTurn method
        -:   19: * Preconditions:   The games state has been initialized, the seed and method name to test are passed
        -:   20: * Postconditions:  The general messages and any failed test messages are displayed
        -:   21: */
        1:   22:int testMethod(char* currentTest, int seed, struct gameState *state)
        -:   23:{
        -:   24:    int i;
        1:   25:    int testsPassed = 0;
        1:   26:    int testsFailed = 0;
        1:   27:    int expectedValue = 0;
        1:   28:    int expectedState = 0;
        -:   29:
        1:   30:    printf ("\n\n-------------------------------------------------------------------------------\n");
        1:   31:    printf ("-------------------------------------------------------------------------------\n");
        1:   32:    printf ("Testing Method  : %s()\n", currentTest);
        1:   33:    printf ("Seed            : %i\n", seed);
        -:   34:
        -:   35:    //check that the current players hand count is reset after method call
        1:   36:    expectedValue = 0;
        1:   37:    state->whoseTurn = 0;
        1:   38:    endTurn(state);
        1:   39:    if(state->handCount[0] != expectedValue) {
    #####:   40:        printf("TEST FAIL    : Current player hand count reset failed\n");
    #####:   41:        testsFailed++;
        1:   42:    } else {testsPassed++;}
        -:   43:
        -:   44:    //check that the outposts played is reset after method call
        1:   45:    expectedValue = 0;
        1:   46:    endTurn(state);
        1:   47:    if(state->outpostPlayed != expectedValue) {
    #####:   48:        printf("TEST FAIL    : Outpost's Played reset failed\n");
    #####:   49:        testsFailed++;
        1:   50:    } else {testsPassed++;}
        -:   51:
        -:   52:    //check that the phase value is reset after method call
        1:   53:    expectedValue = 0;
        1:   54:    endTurn(state);
        1:   55:    if(state->phase != expectedValue) {
    #####:   56:        printf("TEST FAIL    : Phase reset failed\n");
    #####:   57:        testsFailed++;
        1:   58:    } else {testsPassed++;}
        -:   59:
        -:   60:    //check that the number of actions is reset after method call
        1:   61:    expectedValue = 1;
        1:   62:    endTurn(state);
        1:   63:    if(state->numActions != expectedValue) {
    #####:   64:        printf("TEST FAIL    : Number of Actions reset failed\n");
    #####:   65:        testsFailed++;
        1:   66:    } else {testsPassed++;}
        -:   67:
        -:   68:    //check that the number of buys available is reset after method call
        1:   69:    expectedValue = 1;
        1:   70:    endTurn(state);
        1:   71:    if(state->numBuys != expectedValue) {
    #####:   72:        printf("TEST FAIL    : Number of Buys value reset failed\n");
    #####:   73:        testsFailed++;
        1:   74:    } else {testsPassed++;}
        -:   75:
        -:   76:    //check that the current players card count is reset after method call
        1:   77:    expectedValue = 0;
        1:   78:    endTurn(state);
        1:   79:    if(state->playedCardCount != expectedValue) {
    #####:   80:        printf("TEST FAIL    : Played card count value reset failed\n");
    #####:   81:        testsFailed++;
        1:   82:    } else {testsPassed++;}
        -:   83:
        -:   84:    //check that the next player is correctly given control after method call, using first player
        1:   85:    state->whoseTurn = 0;
        1:   86:    expectedValue = 1;
        1:   87:    endTurn(state);
        1:   88:    if(state->whoseTurn != expectedValue) {
    #####:   89:        printf("TEST FAIL    : Next player value reset failed\n");
    #####:   90:        testsFailed++;
        1:   91:    } else {testsPassed++;}
        -:   92:
        -:   93:    //check that the next player is correctly given control after method call, using last player
        1:   94:    state->whoseTurn = 1;
        1:   95:    expectedValue = 0;
        1:   96:    endTurn(state);
        1:   97:    if(state->whoseTurn != expectedValue) {
    #####:   98:        printf("TEST FAIL    : Next player value reset failed\n");
    #####:   99:        testsFailed++;
        1:  100:    } else {testsPassed++;}
        -:  101:
        1:  102:    printf ("    Tests Passed    : %i\n", testsPassed);
        1:  103:    printf ("    Tests Failed    : %i\n", testsFailed);
        1:  104:    printf ("-------------------------------------------------------------------------------\n\n");
        -:  105:
        1:  106:    return 0;
        -:  107:}
        -:  108:
        -:  109:
        -:  110:/*
        -:  111: * Preconditions:   The user can pass a seed value for testing or it defaults to a set value
        -:  112: * Postconditions:  Exit the test program normally
        -:  113: */
        1:  114:int main (int argc, char** argv)
        -:  115:{
        -:  116:
        -:  117:    // Setup Game Seed
        -:  118:    int seed;
        1:  119:    char* currentTest = METHODNAME;
        1:  120:    if(argv[1]) {
    #####:  121:        seed = atoi(argv[1]);
        -:  122:    } else {
        1:  123:        seed = BASESEED;
        -:  124:    }
        -:  125:
        -:  126:    // Initialize Game State
        -:  127:    struct gameState G;
        1:  128:    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
        1:  129:    initializeGame(2, k, seed, &G);
        -:  130:
        1:  131:    testMethod(currentTest,seed, &G);
        1:  132:    return 0;
        -:  133:}
        -:    0:Source:cardtest1.c
        -:    0:Graph:cardtest1.gcno
        -:    0:Data:cardtest1.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:/*
        -:    2: * Jason Gourley
        -:    3: * gourleja@oregonstate.edu
        -:    4: * CS362-400
        -:    5: * Assignment 3 - cardtest1.c
        -:    6: * Description : Unit tests for smithy card
        -:    7: */
        -:    8:
        -:    9:#include <stdio.h>
        -:   10:#include <stdlib.h>
        -:   11:#include "dominion.h"
        -:   12:#include "rngs.h"
        -:   13:
        -:   14:#define CARDNAME  "smithy"
        -:   15:#define BASESEED    10
        -:   16:
        -:   17:/*
        -:   18: * Description:     Test the return values of the smithy card
        -:   19: * Preconditions:   The games state has been initialized, the seed and method name to test are passed
        -:   20: * Postconditions:  The general messages and any failed test messages are displayed
        -:   21: */
        1:   22:int testCard(char* currentTest, int seed, struct gameState *state)
        -:   23:{
        -:   24:    int i;
        1:   25:    int testsPassed = 0;
        1:   26:    int testsFailed = 0;
        1:   27:    int expectedValue = 0;
        -:   28:
        1:   29:    printf ("\n\n-------------------------------------------------------------------------------\n");
        1:   30:    printf ("-------------------------------------------------------------------------------\n");
        1:   31:    printf ("Testing Method  : %s()\n", currentTest);
        1:   32:    printf ("Seed            : %i\n", seed);
        -:   33:
        -:   34:    //Check increase of cards in hand
        1:   35:    expectedValue = state->handCount[state->whoseTurn] + 2;
        1:   36:    cardSmithy(1,0,state);
        1:   37:    if(state->handCount[state->whoseTurn] != expectedValue) {
        1:   38:        printf("  TEST FAIL    : Smithy card added correct number of cards failed\n");
        1:   39:        testsFailed++;
    #####:   40:    } else {testsPassed++;}
        -:   41:
        1:   42:    printf ("    Tests Passed    : %i\n", testsPassed);
        1:   43:    printf ("    Tests Failed    : %i\n", testsFailed);
        1:   44:    printf ("-------------------------------------------------------------------------------\n\n");
        -:   45:
        1:   46:    return 0;
        -:   47:}
        -:   48:
        -:   49:
        -:   50:/*
        -:   51: * Preconditions:   The user can pass a seed value for testing or it defaults to a set value
        -:   52: * Postconditions:  Exit the test program normally
        -:   53: */
        1:   54:int main (int argc, char** argv)
        -:   55:{
        -:   56:
        -:   57:    // Setup Game Seed
        -:   58:    int seed;
        1:   59:    char* currentTest = CARDNAME;
        1:   60:    if(argv[1]) {
    #####:   61:        seed = atoi(argv[1]);
        -:   62:    } else {
        1:   63:        seed = BASESEED;
        -:   64:    }
        -:   65:
        -:   66:    // Initialize Game State
        -:   67:    struct gameState G;
        1:   68:    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
        1:   69:    initializeGame(2, k, seed, &G);
        -:   70:
        1:   71:    testCard(currentTest,seed, &G);
        -:   72:
        1:   73:    return 0;
        -:   74:}
        -:    0:Source:cardtest2.c
        -:    0:Graph:cardtest2.gcno
        -:    0:Data:cardtest2.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:/*
        -:    2: * Jason Gourley
        -:    3: * gourleja@oregonstate.edu
        -:    4: * CS362-400
        -:    5: * Assignment 3 - cardtest2.c
        -:    6: * Description : Unit tests for Adventurer card
        -:    7: */
        -:    8:
        -:    9:#include <stdio.h>
        -:   10:#include <stdlib.h>
        -:   11:#include "dominion.h"
        -:   12:#include "rngs.h"
        -:   13:
        -:   14:#define CARDNAME  "adventurer"
        -:   15:#define BASESEED    10
        -:   16:
        -:   17:/*
        -:   18: * Description:     Test the return values of the adventurer card
        -:   19: * Preconditions:   The games state has been initialized, the seed and method name to test are passed
        -:   20: * Postconditions:  The general messages and any failed test messages are displayed
        -:   21: */
        1:   22:int testCard(char* currentTest, int seed, struct gameState *state)
        -:   23:{
        -:   24:    int i;
        1:   25:    int testsPassed = 0;
        1:   26:    int testsFailed = 0;
        1:   27:    int expectedValue = 0;
        -:   28:
        1:   29:    printf ("\n\n-------------------------------------------------------------------------------\n");
        1:   30:    printf ("-------------------------------------------------------------------------------\n");
        1:   31:    printf ("Testing Method  : %s()\n", currentTest);
        1:   32:    printf ("Seed            : %i\n", seed);
        -:   33:
        -:   34:    //Check increase of cards in hand
        -:   35:
        1:   36:    int currentPlayer = whoseTurn(state);
        1:   37:    int drawntreasure=0;
        1:   38:    int handPos = 0;
        -:   39:    int temphand[MAX_HAND];// moved above the if statement
        1:   40:    int z = 0;// this is the counter for the temp hand
        -:   41:    int cardDrawn;
        -:   42:
        -:   43:    //Check reduction of cards in hand
        1:   44:    expectedValue = state->handCount[currentPlayer] - 1;
        1:   45:    cardAdventurer(temphand, z, cardDrawn, drawntreasure, handPos, currentPlayer, state);
        1:   46:    if(state->handCount[currentPlayer] < expectedValue) {
    #####:   47:        printf("  TEST FAIL    : Adventurer remove card from hand failed\n");
    #####:   48:        testsFailed++;
        1:   49:    } else {testsPassed++;}
        -:   50:
        -:   51:    //Check addition of cards to hand
        1:   52:    expectedValue = state->handCount[currentPlayer];
        1:   53:    cardAdventurer(temphand, z, cardDrawn, drawntreasure, handPos, currentPlayer, state);
        1:   54:    if(state->handCount[currentPlayer] - expectedValue > 1) {
    #####:   55:        printf("  TEST FAIL    : Adventurer add correct number of cards to hand failed\n");
    #####:   56:        testsFailed++;
        1:   57:    } else {testsPassed++;}
        -:   58:
        -:   59:    //Check hand size with lack of treasure cards to add to hand
        1:   60:    state->deckCount[currentPlayer] = 10;
        1:   61:    int card = 0;
      501:   62:    for (i = 0; i < 500; i++)
        -:   63:    {
      500:   64:      state->deck[currentPlayer][i] = card;
      500:   65:      state->discard[currentPlayer][i] = card;
        -:   66:    }
        1:   67:    expectedValue = state->handCount[currentPlayer] - 1;
        1:   68:    cardAdventurer(temphand, z, cardDrawn, drawntreasure, handPos, currentPlayer, state);
        1:   69:    if(state->handCount[currentPlayer] != expectedValue) {
        1:   70:        printf("  TEST FAIL    : Adventurer no treasure available but cards to hand failed\n");
        1:   71:        testsFailed++;
    #####:   72:    } else {testsPassed++;}
        -:   73:
        1:   74:    printf ("    Tests Passed    : %i\n", testsPassed);
        1:   75:    printf ("    Tests Failed    : %i\n", testsFailed);
        1:   76:    printf ("-------------------------------------------------------------------------------\n\n");
        -:   77:
        1:   78:    return 0;
        -:   79:}
        -:   80:
        -:   81:
        -:   82:/*
        -:   83: * Preconditions:   The user can pass a seed value for testing or it defaults to a set value
        -:   84: * Postconditions:  Exit the test program normally
        -:   85: */
        1:   86:int main (int argc, char** argv)
        -:   87:{
        -:   88:
        -:   89:    // Setup Game Seed
        -:   90:    int seed;
        1:   91:    char* currentTest = CARDNAME;
        1:   92:    if(argv[1]) {
    #####:   93:        seed = atoi(argv[1]);
        -:   94:    } else {
        1:   95:        seed = BASESEED;
        -:   96:    }
        -:   97:
        -:   98:    // Initialize Game State
        -:   99:    struct gameState G;
        1:  100:    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
        1:  101:    initializeGame(2, k, seed, &G);
        -:  102:
        1:  103:    testCard(currentTest,seed, &G);
        -:  104:
        1:  105:    return 0;
        -:  106:}
        -:    0:Source:cardtest3.c
        -:    0:Graph:cardtest3.gcno
        -:    0:Data:cardtest3.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:/*
        -:    2: * Jason Gourley
        -:    3: * gourleja@oregonstate.edu
        -:    4: * CS362-400
        -:    5: * Assignment 3 - cardtest3.c
        -:    6: * Description : Unit tests for great_hall card
        -:    7: */
        -:    8:
        -:    9:#include <stdio.h>
        -:   10:#include <stdlib.h>
        -:   11:#include "dominion.h"
        -:   12:#include "rngs.h"
        -:   13:
        -:   14:#define CARDNAME  "great_hall"
        -:   15:#define BASESEED    10
        -:   16:
        -:   17:/*
        -:   18: * Description:     Test the return values of the great_hall card
        -:   19: * Preconditions:   The games state has been initialized, the seed and method name to test are passed
        -:   20: * Postconditions:  The general messages and any failed test messages are displayed
        -:   21: */
        1:   22:int testCard(char* currentTest, int seed, struct gameState *state)
        -:   23:{
        -:   24:    int i;
        1:   25:    int testsPassed = 0;
        1:   26:    int testsFailed = 0;
        1:   27:    int expectedValue = 0;
        1:   28:    int bonus = 0;
        -:   29:
        1:   30:    printf ("\n\n-------------------------------------------------------------------------------\n");
        1:   31:    printf ("-------------------------------------------------------------------------------\n");
        1:   32:    printf ("Testing Method  : %s()\n", currentTest);
        1:   33:    printf ("Seed            : %i\n", seed);
        -:   34:
        -:   35:    //Check increase of cards in hand
        1:   36:    expectedValue = state->handCount[state->whoseTurn];
        1:   37:    cardEffect(great_hall,0,0,0,state, 0, &bonus);
        1:   38:    if(state->handCount[state->whoseTurn] != expectedValue) {
    #####:   39:        printf("  TEST FAIL    : great_hall card add card to hand failed\n");
    #####:   40:        testsFailed++;
        1:   41:    } else {testsPassed++;}
        -:   42:
        -:   43:    //Check increase of cards in hand
        1:   44:    expectedValue = state->numActions + 1;
        1:   45:    cardEffect(great_hall,0,0,0,state, 0, &bonus);
        1:   46:    if(state->numActions != expectedValue) {
    #####:   47:        printf("  TEST FAIL    : great_hall card add number of actions failed\n");
    #####:   48:        testsFailed++;
        1:   49:    } else {testsPassed++;}
        -:   50:
        1:   51:    printf ("    Tests Passed    : %i\n", testsPassed);
        1:   52:    printf ("    Tests Failed    : %i\n", testsFailed);
        1:   53:    printf ("-------------------------------------------------------------------------------\n\n");
        -:   54:
        1:   55:    return 0;
        -:   56:}
        -:   57:
        -:   58:
        -:   59:/*
        -:   60: * Preconditions:   The user can pass a seed value for testing or it defaults to a set value
        -:   61: * Postconditions:  Exit the test program normally
        -:   62: */
        1:   63:int main (int argc, char** argv)
        -:   64:{
        -:   65:
        -:   66:    // Setup Game Seed
        -:   67:    int seed;
        1:   68:    char* currentTest = CARDNAME;
        1:   69:    if(argv[1]) {
    #####:   70:        seed = atoi(argv[1]);
        -:   71:    } else {
        1:   72:        seed = BASESEED;
        -:   73:    }
        -:   74:
        -:   75:    // Initialize Game State
        -:   76:    struct gameState G;
        1:   77:    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
        1:   78:    initializeGame(2, k, seed, &G);
        -:   79:
        1:   80:    testCard(currentTest,seed, &G);
        -:   81:
        1:   82:    return 0;
        -:   83:}
        -:    0:Source:cardtest4.c
        -:    0:Graph:cardtest4.gcno
        -:    0:Data:cardtest4.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:/*
        -:    2: * Jason Gourley
        -:    3: * gourleja@oregonstate.edu
        -:    4: * CS362-400
        -:    5: * Assignment 3 - cardtest4.c
        -:    6: * Description : Unit tests for minion card
        -:    7: */
        -:    8:
        -:    9:#include <stdio.h>
        -:   10:#include <stdlib.h>
        -:   11:#include "dominion.h"
        -:   12:#include "rngs.h"
        -:   13:
        -:   14:#define CARDNAME  "minion"
        -:   15:#define BASESEED    10
        -:   16:
        -:   17:/*
        -:   18: * Description:     Test the return values of the minion card
        -:   19: * Preconditions:   The games state has been initialized, the seed and method name to test are passed
        -:   20: * Postconditions:  The general messages and any failed test messages are displayed
        -:   21: */
        1:   22:int testCard(char* currentTest, int seed, struct gameState *state)
        -:   23:{
        -:   24:    int i;
        1:   25:    int testsPassed = 0;
        1:   26:    int testsFailed = 0;
        1:   27:    int expectedValue = 0;
        1:   28:    int bonus = 0;
        -:   29:
        1:   30:    printf ("\n\n-------------------------------------------------------------------------------\n");
        1:   31:    printf ("-------------------------------------------------------------------------------\n");
        1:   32:    printf ("Testing Method  : %s()\n", currentTest);
        1:   33:    printf ("Seed            : %i\n", seed);
        -:   34:
        -:   35:    //Check increase of cards in hand
        1:   36:    expectedValue = state->numActions + 1;
        1:   37:    cardEffect(minion,0,0,0,state, 0, &bonus);
        1:   38:    if(state->numActions != expectedValue) {
    #####:   39:        printf("  TEST FAIL    : minion card add action failed\n");
    #####:   40:        testsFailed++;
        1:   41:    } else {testsPassed++;}
        -:   42:
        -:   43:    //Check increase of coins for player
        1:   44:    expectedValue = state->coins + 2;
        1:   45:    cardEffect(minion,1,0,0,state, 0, &bonus);
        1:   46:    if(state->coins != expectedValue) {
    #####:   47:        printf("  TEST FAIL    : minion card add coins failed\n");
    #####:   48:        testsFailed++;
        1:   49:    } else {testsPassed++;}
        -:   50:
        -:   51:    //Check size of players hand after call is correct
        1:   52:    expectedValue = 4;
        1:   53:    cardEffect(minion,0,1,0,state, 0, &bonus);
        1:   54:    if(state->handCount[state->whoseTurn] != expectedValue) {
    #####:   55:        printf("  TEST FAIL    : minion redraw hand size failed\n");
    #####:   56:        testsFailed++;
        1:   57:    } else {testsPassed++;}
        -:   58:
        -:   59:    //Check size of opponents hand after call is correct, over 5 in hand
        1:   60:    expectedValue = 4;
        1:   61:    state->whoseTurn = 0;
        1:   62:    state->handCount[1] = 5;
        1:   63:    cardEffect(minion,0,1,0,state, 0, &bonus);
        1:   64:    if(state->handCount[1] != expectedValue) {
    #####:   65:        printf("  TEST FAIL    : minion redraw opponents hand size failed\n");
    #####:   66:        testsFailed++;
        1:   67:    } else {testsPassed++;}
        -:   68:
        -:   69:    //Check size of opponents hand after call is correct, less than 5 in hand
        1:   70:    expectedValue = 4;
        1:   71:    state->whoseTurn = 0;
        1:   72:    state->handCount[1] = 4;
        1:   73:    cardEffect(minion,0,1,0,state, 0, &bonus);
        1:   74:    if(state->handCount[1] != expectedValue) {
    #####:   75:        printf("  TEST FAIL    : minion add cards to opponents hand failed\n");
    #####:   76:        printf("hand count %i\n", state->handCount[1]);
    #####:   77:        testsFailed++;
        1:   78:    } else {testsPassed++;}
        -:   79:
        1:   80:    printf ("    Tests Passed    : %i\n", testsPassed);
        1:   81:    printf ("    Tests Failed    : %i\n", testsFailed);
        1:   82:    printf ("-------------------------------------------------------------------------------\n\n");
        -:   83:
        1:   84:    return 0;
        -:   85:}
        -:   86:
        -:   87:
        -:   88:/*
        -:   89: * Preconditions:   The user can pass a seed value for testing or it defaults to a set value
        -:   90: * Postconditions:  Exit the test program normally
        -:   91: */
        1:   92:int main (int argc, char** argv)
        -:   93:{
        -:   94:
        -:   95:    // Setup Game Seed
        -:   96:    int seed;
        1:   97:    char* currentTest = CARDNAME;
        1:   98:    if(argv[1]) {
    #####:   99:        seed = atoi(argv[1]);
        -:  100:    } else {
        1:  101:        seed = BASESEED;
        -:  102:    }
        -:  103:
        -:  104:    // Initialize Game State
        -:  105:    struct gameState G;
        1:  106:    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
        1:  107:    initializeGame(2, k, seed, &G);
        -:  108:
        1:  109:    testCard(currentTest,seed, &G);
        -:  110:
        1:  111:    return 0;
        -:  112:}