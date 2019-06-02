
/*
 * Include the following lines in your makefile:
 *
 cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)

 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "great_hall"

int main() {
    int newCards = 0, newActions= 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;
    int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

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
  
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST +1 card --------------
	printf("TEST :+1 card and +1 Action\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 1;
	xtraCoins = 0;

	//1 card should come from this player's own pile and not change the coin counts
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
	assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);
	assert(testG.coins == G.coins + xtraCoins);

   //+1 Action
    newActions = 1;
	printf("Actions count = %d, expected = %d\n", testG.numActions, G.numActions + newActions);

    //No state change should occur to the victory card piles and kingdom card piles. 
    for (n = 0; n < 10; n++) {
        assert(testG.supplyCount[k[n]] == G.supplyCount[k[n]]);
    }
    
    //No state change should occur for other players.
	assert(testG.deckCount[otherPlayer] == G.deckCount[otherPlayer]);

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}

