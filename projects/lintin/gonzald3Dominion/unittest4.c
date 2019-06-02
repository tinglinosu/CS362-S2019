/* adventurerCardEffect()*/


/*
 * Include the following lines in your makefile:
 *
 testUnitTest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurerCardEffect"

int main() {

    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int drawntreasure=0;
    int cardDrawn = 0;
    int z = 0;// this is the counter for the temp hand
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, remodel};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	G.hand[thisPlayer][0] = copper;
	G.hand[thisPlayer][1] = adventurer;
	G.hand[thisPlayer][2] = village;
	G.hand[thisPlayer][3] = smithy;
	G.hand[thisPlayer][4] = mine;


	printf("----------------- Testing refactored function for: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: Happy case --------------
	// copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    
    int totalCards = testG.deckCount[thisPlayer] + testG.handCount[thisPlayer] + testG.discardCount[thisPlayer];
    adventurerCard(&testG);
    expectTwoMoreTreasureCardsInHand(&testG, thisPlayer);
    assert(totalCards == (testG.deckCount[thisPlayer] + testG.handCount[thisPlayer] + testG.discardCount[thisPlayer]));

	// ----------- TEST 2: deck is empty--------------
    memcpy(&testG, &G, sizeof(struct gameState));
    moveDeckCardsToDiscard(&testG, thisPlayer);

    adventurerCard(&testG);

    expectTwoMoreTreasureCardsInHand(&testG, thisPlayer);
    assert(totalCards == (testG.deckCount[thisPlayer] + testG.handCount[thisPlayer] + testG.discardCount[thisPlayer]));

    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
	
	return 0;
}

int expectTwoMoreTreasureCardsInHand(struct gameState *state, int thisPlayer) {
    int treasureCount = 0;
    for (int i = 0; i < state->handCount[thisPlayer]; i++) {
        int card = state->hand[thisPlayer][i];
        if (card >= copper && card <= gold) {
            treasureCount++;
        }
    }
	printf("treasure card in hand: %d, expect player can still get 2 treasure cards after shuffle. \n", treasureCount);
    assert(treasureCount == 3); // +1 already in hand
}

int moveDeckCardsToDiscard(struct gameState *state, int thisPlayer) {
    for (int i = 0; i < state->deckCount[thisPlayer]; i++) {
        int card = state->deck[thisPlayer][i];
        state->discard[thisPlayer][state->discardCount[thisPlayer]] = card;
        state->discardCount[thisPlayer]++;
    }
    state->deckCount[thisPlayer] = 0;
}