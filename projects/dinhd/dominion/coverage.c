Dustin Dinh
CS 362 Assignment 3

***********************************  cardtest1  ***********************************
Card: Village
Lines executed:22.88% of 577
Branches executed:25.18% of 417
Taken at least once:15.11% of 417
Calls executed:16.16% of 99

All statements were covered in the villageCard function. There were no branch
statements in this function. As a result coverage was straight forward. 

***********************************  cardtest2  ***********************************
Card: Adventurer
Lines executed:29.98% of 577
Branches executed:31.89% of 417
Taken at least once:22.30% of 417
Calls executed:27.27% of 99


Two branches were not covered. As a result 4 statements were not executed. 
The first branch contained 1 statement that checked to see if the deck needed
to be reshuffled. The second depended on not drawing a treasure card. Both of these
problems could have been solved by either manipulating the deck so that it had the
right quantities and composition or increasing the number of runs. Since it requires
less time, inceasing the number of runs is recommended.


***********************************  cardtest3  ***********************************
Card: Smithy
Lines executed:29.98% of 577
Branches executed:31.89% of 417
Taken at least once:22.30% of 417
Calls executed:27.27% of 99

All statements were covered in the smithyCard function. There were no branch
statements in this function. As a result coverage was straight forward. 

***********************************  cardtest4  ***********************************
Card: Mine
Lines executed:29.98% of 577
Branches executed:31.89% of 417
Taken at least once:22.30% of 417
Calls executed:27.27% of 99

Note: With the bug I introduced, coverage was very poor since the function exited
out as soon as it detected an invalid parameter input. If I removed the bug, only one
statement was missed. The reason why the statement was missed was because I did not do
enough boundry checking. I did not include an input that was outside the range of 
possible cards. 

***********************************  cardtest5  ***********************************
Card: Minion
Lines executed:29.98% of 577
Branches executed:31.89% of 417
Taken at least once:22.30% of 417
Calls executed:27.27% of 99

Statement coverage and branch coverage was complete until the functions that involved
the opposing players hand. I discovered that I could not measure the various
states of the other player. Either the values were missing or did not exist. As a
result I could not test those lines of code. 

***********************************  unittest1  ***********************************

Function: GainCard()
Lines executed:32.58% of 577
Branches executed:33.33% of 417
Taken at least once:23.74% of 417
Calls executed:28.28% of 99

All the statements were covered. Branch coverage was excellent with close to a 50% rate
between conditionals.

In this test, I did a good job of checking boundries, calling on all possible cards 
in addition to cards that did not exist

***********************************  unittest2  ***********************************
Function: fullDeckCount()
Lines executed:34.14% of 577
Branches executed:36.21% of 417
Taken at least once:26.62% of 417
Calls executed:28.28% of 99

All the statements were covered. Branch coverage was good. There were cases where 
the branch fallthrough was not covered enough. In the future I would try to increase
fallthrough. 

For boundry checking, I wasnt sure if it was necessary to check for nonexistent players
when calling fullDeckCount() since I think that should be taken care by the calling
method. 

***********************************  unittest3  ***********************************
Function: isGameOver()
Lines executed:40.03% of 577
Branches executed:48.20% of 417
Taken at least once:36.93% of 417
Calls executed:31.31% of 99

I missed one branch, which resulted in missing one statement. According to my test
this should not have been the case because I explicitly tested for a scenario where
the branch should have been taken. After analysing the code, I have not found the
reason why this would be the case. As a result, I think that there is some behavior
in the software that I do not understand, and as a result I need to revise my test
by increasing the number of bounds used in the test in an effort to understand
the behavior.

***********************************  unittest4  ***********************************
Function: scoreFor()
Lines executed:40.03% of 577
Branches executed:48.20% of 417
Taken at least once:36.93% of 417
Calls executed:31.31% of 99

Both statement and branch coverage was good. Boundry coverage was good as well. I
tested scenarios where there were no points and points in each of the possible
locations. One possible improvement is I should have tested the number of points
summed from all 3 locations. 