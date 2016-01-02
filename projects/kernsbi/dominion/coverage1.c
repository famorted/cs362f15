Billy Kerns
coverage1.c


File 'unittest1.c'
scoreFor() function
Lines executed:96.30% of 81
Branches executed:100.00% of 62
Taken at least once:95.16% of 62
Calls executed:94.44% of 18
Dominion code coverage: 5.72%

#####:   66:                        errorFlag++;
#####:   73:                printf("All tests passed\n");
#####:  154:                return -2;

For unittest1 I wrote test cases to check the scoreFor() function inside dominion.c. 

Lines executed: 
	96.30% of my lines inside unittest1.c ran. Two of the lines that were not executed were due to the program finding an error
	and exiting the test function early since we knew it would fail anyway.  The other line that was not run was due to the 
	program finding an error so it did not print "All tests passed".  This essentially means all lines that were expected to 
	run did.  I believe this was achieved by running a for loop a 1000 times that randomized the gameState each time creating
	many different scenarios for the code to test.  

Branches executed:
	With all these random cards be being added to player's hand, deck, and discard at random I was able to achieved 100% branch
	coverage. This was mainly due to almost all of my branches checking for what card was drawn.  

Taken at least once: 
	The reason the taken at least once is not 100% is because of an if statement that checks for an error count and if that 
	error count is 0 then print "All tests passed". Since there is an error in the scoreFor() function this never happens. 

Calls executed:
	Calls executed is less than 100% thanks to calls to printf not happening because of the error in scoreFor(). 

Dominion code coverage: 
	Dominion code coverage is relativly low but this is to be expected since instead of initializing the game I just filled the
	gameState with junk and only changed the things that were needed by the scoreFor() function.  This combined with the low
	amount of lines in scoreFor lead to a low amount of code coverage in dominion.c.  

Implications:
	Even with the low code coverage the test suite still did it's job in finding an error.  After correcting the error scoreFor()
	worked exactly as it should passing the test cases.


File 'unittest2.c'
fullDeckCount() function
Lines executed:92.68% of 41
Branches executed:100.00% of 22
Taken at least once:86.36% of 22
Calls executed:93.33% of 15
Dominion code coverage: 1.56%

#####:   72:                        errorCount++;
#####:   79:                        errorCount++;
#####:   91:                printf("At least 1 test failed.  Set NOISY_TEST to 1 for more information.\n");

For unittest2 I wrote test cases to check the fullDeckCount() function inside dominion.c.

Lines executed:
	I was able to achieve 92.68% statement coverage with the only lines not running being a couple error counters and a printf
	with an error message.  Thanks to fullDeckCount not having any errors these were never ran.  

Branches executed:
	100% branch coverage was achieved due to all branches being either a check for a correct count of a certain card, a memcmp,
	and a check for an error count.  

Taken at least once:
	Taken at least once coverage is 86.36% because two paths are not taken.  These paths are for when fullDeckCount() returns a
	number different than what the program was expecting and when memcmp fails.  Since fullDeckCount() has no errors these two
	path were never taken.  However, Changing fullDeckCount() to be wrong does induce a trip down these paths.  

Calls executed:
	Calls executed is at 93.33%.  Two printf statements are never ran since they are on error paths.

Dominion code coverage:
	Like in unittest1 I did not initialize the gameState with the dominion code but by filling it with junk and then modifying
	the pieces that were relevant to the fullDeckCount() function.  This combined with the relativly small size of the code in 
	fullDeckCount() lead to poor dominion code coverage.

Implications:
	All types of coverage were good leading me to believe that fullDeckCount() works as it should.


File 'unittest3.c'
discardCard() function
Lines executed:86.79% of 53
Branches executed:100.00% of 32
Taken at least once:75.00% of 32
Calls executed:94.12% of 17
Dominion code coverage: 2.08%

#####:   55:                printf("All tests passed\n");
#####:   74:                errorCount++;
#####:   82:                errorCount++;
#####:   89:                errorCount++;
#####:   96:                errorCount++;
#####:  116:                pre.handCount[p]--;
#####:  129:                errorCount++;

For unittest3 I wrote test cases to check the discardCard() function inside dominion.c. 

Lines executed:
	Like the previous tests the majority of the lines that were not ran are due to error counts not being incremented because 
	certain errors did not occur.  One of the other two lines that did not run is due to a test case failing which prints out 
	an error message instead of "All tests passed".  The last line that does not run is more of a mystery.  This line comes from 
	the discardCard() function and I was using it to implement my own discardCard code.  No matter what I did I could not get 
	this code to run.  I'm relativly certain I could remove this code with no ill effects which I think shows the usefulness of
	gcov for things other than did this test case run.  

Branches executed:
	100% branch was achieved by the majority of my branches just being checks for correct output after running the discardCard()
	function.  With the rest being a check for error count and if statements for doing my own discardCard code.

Taken at least once:
	Taken at least once is low due to a lot of if statements checking for correct output.  Since the majority of the output from
	discardCard() is correct these paths are usually not followed with the exception on the stray line of code of mentioned earlier
	that I cannot get to run, the if statement for "All tests passed", and the if statement checking that discardCount is incremented
	since there is an error there.

Calls executed:
	All calls were executed except for a call to printf to print "All test passed" which was never called because all the tests did
	not pass.

Dominion card coverage:
	Again I did not use the initialize game function so the only code from dominion.c that I used was the discardCard() function.
	Since this is a rather large function it pushed my dominion code coverage up from the previous tests.

Implications:
	With general code coverage high the test suite was able to detect and report an error in the discardCard() function.  If my 
	test coverage would have been lower this error might hae gone unnoticed.  If we were to fix the error in discardCard() we 
	could have a reasonable amount of confidence in discardCard() working like it should.


File 'unittest4.c'
Lines executed:88.52% of 61
Branches executed:100.00% of 34
Taken at least once:79.41% of 34
Calls executed:90.91% of 11
Dominion code coverage: 1.91%

#####:   97:                        errorCount++;
#####:  104:                        errorCount++;
#####:  111:                        errorCount++;
#####:  118:                        errorCount++;
#####:  125:                        errorCount++;
#####:  132:                        errorCount++;
#####:  148:                printf("At least one failed test.  Set NOISY_TEST to 1 for more information\n");

For unittest4 I wrote test cases to check the updateCoins() function inside dominion.c. 

Lines executed:  
	I was able to get 88.52% statement coverage in unittest4.  Since my test suite could not detect any errors in updateCoins() 
	the only lines that were not run were error counters and a printf to print error message.  This means that all my test
	scenarios were ran.

Branches executed:
	I achieved 100% branch coverage thanks to all of my branches being checks for correct output and error flags.  

Taken at least once:
	Taken at least once is 79.41% with the remaining 20.59% being error paths that will not run due to updateCoins() being
	implemented correctly.

Calls executed:
	All call were executed except for the one printf that prints out an error message.  Since the test suite did not find any
	errors, this was never ran.

Dominion code coverage:
	Again I did not use the initialize game function so the only code from dominion.c that I used was the updateCoins() function.
	This is a pretty small function meaning dominion code coverage is also small.

Implications:
	With all coverage being high I can reasonably say all my test scenarios were ran and that updateCoins() works as intended.

File 'cardtest1.c'
Lines executed:88.37% of 86
Branches executed:91.89% of 74
Taken at least once:78.38% of 74
Calls executed:94.44% of 18
Dominion code coverage: 19.41%

 #####:   70:                printf("All tests passed\n");
 #####:   94:                errors++;
 #####:  100:                errors++;
 #####:  125:                        errors++;
 #####:  134:                                errors++;
 #####:  140:                        if(i != turn){
 #####:  144:                                errors++;
 #####:  154:                                errors++;
 #####:  165:                                errors++;
 #####:  182:                                errors++;

For cardtest1 I wrote test cases to check the smithy card inside dominion.c.

Lines executed:
	For cardtest1 I had statement coverage of 88.37% with the majority of the 11.63% that is not covered coming from error 
	counter that were never tripped and a printf that lets us know if all test passed.  Thanks to a user implemented error this
	is exactly what we are expecting.  Line 140 is never run due to the previously mentioned error in the discardCard() function.

Branches executed:
	Branches executed is lower here than for all of my unittests due to some more complicated error paths that have if statements
	and for loops buried within some other if statements and for loops.  If the first error condition is not met then it will never
	get to the secondary ones with these statements...I think.

Taken at least once:
	Taken at least once is also low due to the same reasons as branches executed being low.  Some branches will never be traveled
	unless a certain error show up.  If that error does not show up then these branches are not traveled which brings down the 
	taken at least once percentage.

Calls executed:
	The only call not executed is the call to printf() to tell the user that all tests passed.  All tests did not pass so this is 
	expected.

Dominion code coverage:
	Dominion code coverage is higher for this test since I used the initialize game function from dominion.c which uses a lot of 
	code.  This combined with the code in smithyCard() makes up a fair chunk of code in dominion.c.

Implications:
	Looking at the low percent of branches executed and taken at least once lets me know that I probably should have seperated some
	of my error checking statements better to ensure that they run.  On the other side of this it also lets me know that the error
	condition required to create the secondary error never happens.


File 'cardtest2.c'
Lines executed:88.89% of 81
Branches executed:97.50% of 80
Taken at least once:83.75% of 80
Calls executed:94.12% of 17
Dominion code coverage: 22.53%

#####:   68:                printf("At least 1 test failed.  Define NOISY_TEST to 1 for more information\n");
#####:  108:                                funErrors++;
#####:  117:                                funErrors++;
#####:  126:                                funErrors++;
#####:  141:                                funErrors++;
#####:  157:                        if(post.handCount[currentPlayer] != pre->handCount[currentPlayer]+2){
#####:  162:                                funErrors++;
#####:  171:                                funErrors++;
#####:  179:                        funErrors++;

For cardtest2 I wrote test cases to check the adventurer card inside dominion.c.

Lines executed:
	88.89% of cardtest2 was executed while the 11.11% that was not executed were a printf statement for letting the user know
	if there were any errors, an error counter, and a check with in an if statement that never evaluated to true after 10,000
	runs.

Branches executed:
	All but one branch executes because it is in a if statement that only evaluates to true on extremely rare circumstances.  
	Since this circumstance is so rare it is no surprise that the second if statement is never triggered but the code is left
	in just in case.

Taken at left once:
	The 16.25% that is not executed at least once is due to if statements looking for incorrect data.  Since it did not find any
	these paths were not taken.

Calls executed:
	Like before the only call not executed is a printf to let the user know about an error.

Dominion code coverage:
	Dominion code coverage is higher for this test since I used the initialize game function from dominion.c which uses a lot of 
	code.  This combined with the code in adventureCard() makes up a fair chunk of code in dominion.c.

Implications:
	This was an interesting test suite.  My orriginal test cause a seg fault and after digging around I discovered a couple bugs
	in the adventurer card that had to be fixed before my code would even run.  I also discovered a bug that I was not even testing
	for which let me know even though my coverage was pretty good it does not mean there are no bugs.


File 'cardtest3.c'
Lines executed:86.36% of 66
Branches executed:90.48% of 42
Taken at least once:71.43% of 42
Calls executed:94.44% of 18
Dominion code coverage: 21.32%

#####:   73:                printf("All tests passed\n");
#####:   92:                funErrors++;
#####:   99:                funErrors++;
#####:  110:                        if(t != currentPlayer){
#####:  115:                                funErrors++;
#####:  119:                        if(t != currentPlayer){
#####:  124:                                funErrors++;
#####:  133:                                funErrors++;
#####:  148:                                funErrors++;

For cardtest3 I wrote test cases to check the village card inside dominion.c.

Lines executed:
	The lines that were not executed are a printf that lets us know all test passed.  Since this is not true it did not run.  Some
	error counter were not incremented which is expected and some if statements that will only run if certain errors are encountered.
	These results are what I was expecting.

Branches executed:
	The branches executed percentage is low due to some branches being within error branches that are not being traveled.  These are
	mainly for testing that other players hands and etc... have not been changed.  It does not meet the first condition so the program
	does not bother checking for the rest.

Taken at least once:
	The low percentage of taken an least once is due to the reasons in branches executed.

Calls executed:
	The only call not executed is a printf to let the user know all test passed.  Since there is an error this is never executed.

Dominion code coverage:
	Dominion code coverage is relativly high for because the initialize game function is used.  This accounts for most of the dominion
	code coverage as the village card does not have a lot of code.

Implications:
	With good test coverage I think that this test suite can be counted on to give us accurate results when testing the village card.
	After fixing the discardCard() function the village card passes all my tests so we can reasonably say that this card does what
	it is supposed to do.

File 'cardtest4.c'
Lines executed:82.61% of 69
Branches executed:86.96% of 46
Taken at least once:67.39% of 46
Calls executed:94.44% of 18
Dominion code coverage: 19.58%

#####:   74:                printf("All tests passed\n");
#####:   92:                funErrors++;
#####:   99:                funErrors++;
#####:  106:                funErrors++;
#####:  118:                        if(t != currentPlayer){
#####:  123:                                funErrors++;
#####:  127:                        if(t != currentPlayer){
#####:  132:                                funErrors++;
#####:  141:                                funErrors++;
#####:  145:                        if(t != currentPlayer){
#####:  150:                                funErrors++;
#####:  165:                                funErrors++;


For cardtest4 I wrote test cases to check the great hall card inside dominion.c.

The same as cardtest3.c as the only difference is great hall gives a player +1 actions instead of +2 actions
