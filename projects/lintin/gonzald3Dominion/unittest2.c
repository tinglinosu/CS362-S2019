/* villageCardEffect()*/


/*
 * Include the following lines in your makefile:
 *
 testUnitTest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "villageCard"

int main() {
    int newCards = 0;
    int newActions = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int n;
    int handpos = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int otherPlayer = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, remodel};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing refactored function for: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: +1 cards --------------
	//printf("TEST :+1 card\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

    printf("hand count before play village = %d\n", testG.handCount[thisPlayer]);
	printf("deck count before play village = %d\n", testG.deckCount[thisPlayer]);
    printf("#coins before play village = %d\n", testG.deckCount[thisPlayer]);

	villageCard(&testG, handpos);

    //Introduced a bug in villageCardEffect()
	newCards = 1;
	xtraCoins = 0;
	printf("current hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("current deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("current #coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);

	newActions = 2;
	printf("current actions count = %d, expected = %d\n", testG.numActions, G.numActions + newActions);
	
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
	assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);
	assert(testG.coins == G.coins + xtraCoins);
    assert(testG.numActions == G.numActions + newActions);
     
    //No state change should occur to the victory card piles and kingdom card piles. 
    for (n = 0; n < 10; n++) {
        assert(testG.supplyCount[k[n]] == G.supplyCount[k[n]]);
    }
    
    //No state change should occur for other players.
	assert(testG.deckCount[otherPlayer] == G.deckCount[otherPlayer]);

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}

