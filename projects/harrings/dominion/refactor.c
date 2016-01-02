refactor.c

For the adventurer card I  changed the logic of if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
to if (cardDrawn == copper && cardDrawn == silver && cardDrawn == gold) this will cause the game to not incriment treasure drawn 
and it is easy to overlook

For the council function I made it so each time through the for loop 2 cards are drawn rather then 1 so 8 cards instead of 4 are drawn.

For gardens I made no changes.

For the smithy card I changed the incrimenter on i from a postfix to a prefix so now only 2 cards are drawn instead of 3.

FOr the village card I changed the state->numActions = state->numActions + 2 to state->numActions =2; so now 
instead of increasing actions by 2 it sets total actions to 2.