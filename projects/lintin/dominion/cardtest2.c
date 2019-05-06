
/*
 * Include the following lines in your makefile:
 *
 cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
 */



#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int main() {
    int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int handpos = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
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


	printf("----------------- Testing card: %s ----------------\n", TESTCARD);

	// ----------- TEST : happy case --------------
	// copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    int totalCards = testG.deckCount[thisPlayer] + testG.handCount[thisPlayer] + testG.discardCount[thisPlayer];
    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

    expectTwoMoreTreasureCardsInHand(&testG, thisPlayer);
    assert(totalCards == (testG.deckCount[thisPlayer] + testG.handCount[thisPlayer] + testG.discardCount[thisPlayer]));

	// ----------- TEST : deck is empty--------------
    memcpy(&testG, &G, sizeof(struct gameState));
    moveDeckCardsToDiscard(&testG, thisPlayer);
    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
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

//to empty the deck 
int moveDeckCardsToDiscard(struct gameState *state, int thisPlayer) {
    for (int i = 0; i < state->deckCount[thisPlayer]; i++) {
        int card = state->deck[thisPlayer][i];
        state->discard[thisPlayer][state->discardCount[thisPlayer]] = card;
        state->discardCount[thisPlayer]++;
    }
    state->deckCount[thisPlayer] = 0;
}