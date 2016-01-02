I refactored the dominion.c code to have functions for the following cards: smithy, adventurer, council room, village, and steward.

The bugs I introduced were in smithy, adventurer, village, and steward.

In smithy_card(), I introduced a bug, where instead of discarding a card at the end of the players turn, a card gets trashed. 

In adventurer_card(), I introduced a bug, where the while loop keeps running until 4 treasure cards are found.  Instead of two.

In village_card(), I introduced a bug, where the fuction draws two cards instead of two.

In steward_card(), I introduced a bug, where the function trashes one card and discards two cards, instead of trashing two cards and discarding one card.
