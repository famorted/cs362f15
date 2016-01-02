/*
Filename: refactor.c
Author: Sharon Kuo (kuos@oregonstate.edu)
Last modified: 2015-10-11
Description: Documentation of changes/bugs made

----------------------------------------
Smithy
----------------------------------------
int smithyCard(int currentPlayer, struct gameState *state, int handPos)
--------------------
Refactored into the smithyCard() function.
Function prototype added to dominion_helpers.h.
Introduced a bug in the for loop where the incrementing of i is prefix instead
of postfix, so that the loop only runs 2 times instead of 3. Common for loop
condition mistake. Also set the card to be discarded as trash.

----------------------------------------
Adventurer
----------------------------------------
int adventurerCard(int player, struct gameState *state, int* tempHand)
--------------------
Refactored into the adventurerCard() function.
Function prototype added to dominion_helpers.h.
Introduced a bug in the first while loop when drawing cards; changed the while
loop condition to drawnTreasure <= 2, so that the loop draws a total of 3
treasure cards instead of 2. Additionally set the discard while loop to discard
all but one card (z - 1 > 0 instead of z - 1 >= 0). Common loop condition
mistake.
Also may loop forever if there's only 1 treasure available, since it ends up in
the hand and doesn't get discarded.

----------------------------------------
Council Room
----------------------------------------
int councilRoomCard(int currentPlayer, struct gameState* state, int handPos)
--------------------
Refactored into the councilRoomCard() function.
Function prototype added to dominion_helpers.h.


----------------------------------------
Village
----------------------------------------
int villageCard(int player, struct gameState* state, int handPos)
--------------------
Refactored into the villageCard() function.
Function prototype added to dominion_helpers.h.
Introduced a bug where the handPos and trash flag are switched when passing to
the discardCard() function.

----------------------------------------
Remodel
----------------------------------------
int remodelCard(int player, struct gameState* state, int handPos, int choice1,
  int choice2)
--------------------
Refactored into the remodelCard() function.
Function prototype added to dominion_helpers.h.
Introduced a bug where the break statement inside discard trashed card for loop
is removed from the if statement, causing all cards that match the card to be
trashed to be trashed instead of trashing only one copy (so if one tries to
trash a card that they have multiple copies of in their hand, all copies will
end up being trashed). Also swapped the handPos and trash flags that are passed
to the discardCard() function.

*/
