/*
Author:  Andrew Shen
File:  refactor.c
Assignment 2
Date:  11 October 15
Notes:  Documentation of refactored cards in dominion.c as well as explanation of introduced bugs
*/

/** line 649 **************************************************				
* adventurer effect refactored into adventurerEffect() 
*	bug on line 644:
*		before:
*			if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
*		after:
*			if (cardDrawn == copper || cardDrawn == silver)
*	explanation:
*		the bug introduced makes it so that if a gold card is drawn, it does not increase treasure count
**************************************************************/

/** line 680 **************************************************
* smithy effect refactored into smithyEffect()
*	bug on line 687
*		before:
*			for (i = 0; i < 4; i++)
*		after:
*			for (i = 0; i < 3; i++)
**************************************************************/

/** line 698 **************************************************				
* village effect refactored into villageEffect()
*	bug on line 707:
*		before:
*			state->numActions = state->numActions + 2;
*		after:
*			state->numActions = state->numActions + 1;
*	explanation:
*		the bug introduced makes it so that the village card only increases actions by 1
**************************************************************/

/** line 715 **************************************************			
* feast refactored into feastEffect()
*	bug on line 729
*		before:
*			    while( x == 1) {
*		after:
*			    while( x != 1) {
*	explanation:					
*		this bug makes it so that the buy loop cannot be entered
**************************************************************/

/** line 770 **************************************************
* great_hall refactored into great_hallEffect()
*	bug on line 775:
*		before:
*			state->numActions++;
*		after:
*			state->numActions--;
*	explanation:
*		instead of increasing number of actions by 1, the great_hall card decreases actions by 1
**************************************************************/