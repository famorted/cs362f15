Jason Gourley
gourleja@oregonstate.edu
CS362-400
Assignment 2 - refactor.c

-------------------------------------------------------------------------------
Refactored Code
-------------------------------------------------------------------------------

Smithy Card
    Moved card code from switch statement to method cardSmithy()
    Signature: 
        void cardSmithy(int handPos, int player, struct gameState *state);
    Bugs Introduced:
        Changed for loop condition to "i <= 3" from "i < 3"


Adventurer Card
    Moved card code from switch statement to method cardAdventurer()
    Signature: 
        void cardAdventurer(int temphand[], int z, int cardDrawn, int drawntreasure, int handPos, int player, struct gameState *state);
    Bugs Introduced:
        Changed shuffle condition from "state->deckCount[currentPlayer] < 1" to "state->deckCount[currentPlayer] <= 1"
        Changed variable z from post-increment to pre-increment in the else block


Baron Card
    Moved card code from switch statement to method cardBaron()
    Signature: 
        void cardBaron(int choice1, int handPos, int player, struct gameState *state);
    Bugs Introduced:
        Removed the decrement line for estate supply count: "state->supplyCount[estate]--;//Decrement Estates"


Salvager Card
    Moved card code from switch statement to method cardSalvager()
    Signature: 
        void cardSalvager(int choice1, int handPos, int currentPlayer, struct gameState *state);
    Bugs Introduced:
        Changed "state->numBuys++;" to "state->numActions++"


Council Room Card
    Moved card code from switch statement to method cardCouncilRoom()
    Signature: 
        void cardCouncilRoom(int handPos, int currentPlayer, struct gameState *state);
    Bugs Introduced:
        None