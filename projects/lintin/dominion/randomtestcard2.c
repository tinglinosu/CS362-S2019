/* villageCardEffect()*/


/*
 * Include the following lines in your makefile:
 *
 randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
 */

 


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

int main() {

    int newCards = 0;
    int newActions = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i;
    int tests = 50;  

    int n;
    int handpos = 0;
    int thisPlayer = 0;
    int otherPlayer = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, remodel};

     for(i = 0; i < tests; i++) { 

        int numPlayers = (rand() % 3) + 2;   //randomize the number of player
        int seed = (rand() % 5000) + 1;     //random seed 
        G.deckCount[thisPlayer] = rand() % MAX_DECK;//randomize deck size
	    G.handCount[thisPlayer] = rand() % MAX_HAND;//randomize hand size
   
        // initialize a game state and player cards
        initializeGame(numPlayers, k, seed, &G);

        printf("----------------- Random Test for for: %s ----------------\n", TESTCARD);

        // ----------- TEST 1: +1 cards --------------
        //printf("TEST :+1 card\n");

        // copy the game state to a test case
        memcpy(&testG, &G, sizeof(struct gameState));
        villageCardEffect(thisPlayer, &testG, handpos);


        //Introduced a bug in villageCardEffect()
        newCards = 1;
        xtraCoins = 0;
        printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
        printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
        printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
        assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
        assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);
        assert(testG.coins == G.coins + xtraCoins);

        newActions = 2;
        printf("Actions count = %d, expected = %d\n", testG.numActions, G.numActions + newActions);
        // assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
        
        //No state change should occur to the victory card piles and kingdom card piles. 
        for (n = 0; n < 10; n++) {
            assert(testG.supplyCount[k[n]] == G.supplyCount[k[n]]);
        }
        
        //No state change should occur for other players.
        assert(testG.deckCount[otherPlayer] == G.deckCount[otherPlayer]);
     }

	printf("\n >>>>> SUCCESS: Random Test complete for %s <<<<<\n\n", TESTCARD);


	return 0;
}

