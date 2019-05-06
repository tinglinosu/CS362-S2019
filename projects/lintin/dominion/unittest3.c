/* mineCardEffect()*/


/*
 * Include the following lines in your makefile:
 *
 testUnitTest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "mineCardEffect"

int main() {
    int i = 0, j= 0, choice1 = 0, choice2 = 0;
    int handpos = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, remodel};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing refactored function for: %s ----------------\n", TESTCARD);

	// ----------- TEST : the card  we will trash is a treasure card--------------
	//printf("TEST :is a treasure card or not\n");

	G.hand[thisPlayer][0] = copper;
	G.hand[thisPlayer][1] = adventurer;
	G.hand[thisPlayer][2] = village;
	G.hand[thisPlayer][3] = smithy;
	G.hand[thisPlayer][4] = mine;

	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 3;
	int result = mineCardEffect(i, j, &testG, thisPlayer, choice1, choice2, handpos);
	printf("test result1 = %d, expected = -1\n", result);

	memcpy(&testG, &G, sizeof(struct gameState));
    j = 7;
    result = mineCardEffect(i, j, &testG, thisPlayer, choice1, choice2, handpos);	
	printf("test result2 = %d, expected = -1\n", result);
    assert(result == -1);

	memcpy(&testG, &G, sizeof(struct gameState));
    choice2 = 27;
    result = mineCardEffect(i,j,&testG, thisPlayer,choice1,choice2, handpos);
	printf("test result3 = %d, expected = -1\n", result);
    assert(result == -1);

	memcpy(&testG, &G, sizeof(struct gameState));
	choice2 = -1;
    result = mineCardEffect(i,j,&testG, thisPlayer,choice1,choice2, handpos);
	printf("test result4 = %d, expected = -1\n", result);
    assert(result == -1);
    
	choice1 = 0; choice2 = gold;
	memcpy(&testG, &G, sizeof(struct gameState));
	result = mineCardEffect(i,j,&testG, thisPlayer,choice1,choice2, handpos);
    printf("test result5 = %d, expected = -1\n", result);
    

	choice1 = 0; // copper position
	choice2 = silver;
    memcpy(&testG, &G, sizeof(struct gameState));
    mineCardEffect(i,j,&testG, thisPlayer,choice1,choice2, handpos);

    for(i = 0; i < testG.handCount[thisPlayer]; i++) {
		if (testG.hand[thisPlayer][i] == silver) {
    		printf("Expect silver in hand succeeded\n");
			printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
			return 0;
		}
	}
	printf("Expect silver in hand failed\n");
	return -1;
}

