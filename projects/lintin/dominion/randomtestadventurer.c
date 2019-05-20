/* adventurerCardEffect()*/


/*
 * Include the following lines in your makefile:
 *
 randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
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

    int thisPlayer = 0;
    int drawntreasure=0;
    int cardDrawn = 0;
    int i,z = 0;// z is the counter for the temp hand
    int tests = 50;   

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
            G.hand[thisPlayer][0] = copper;
            G.hand[thisPlayer][1] = adventurer;
            G.hand[thisPlayer][2] = village;
            G.hand[thisPlayer][3] = smithy;
            G.hand[thisPlayer][4] = mine;


            printf("----------------- Random Test for for: %s ----------------\n", TESTCARD);

            // ----------- TEST 1: Happy case --------------
            // copy the game state to a test case
            memcpy(&testG, &G, sizeof(struct gameState));



            int totalCards = testG.deckCount[thisPlayer] + testG.handCount[thisPlayer] + testG.discardCount[thisPlayer];
            adventurerCardEffect(drawntreasure, &testG, thisPlayer, cardDrawn, z);
            expectTwoMoreTreasureCardsInHand(&testG, thisPlayer);
            assert(totalCards == (testG.deckCount[thisPlayer] + testG.handCount[thisPlayer] + testG.discardCount[thisPlayer]));

            // ----------- TEST 2: deck is empty--------------
            memcpy(&testG, &G, sizeof(struct gameState));
            moveDeckCardsToDiscard(&testG, thisPlayer);
            adventurerCardEffect(drawntreasure, &testG, thisPlayer, cardDrawn, z);
            expectTwoMoreTreasureCardsInHand(&testG, thisPlayer);
            assert(totalCards == (testG.deckCount[thisPlayer] + testG.handCount[thisPlayer] + testG.discardCount[thisPlayer]));
}
            printf("\n >>>>> SUCCESS: Random Test complete for %s <<<<<\n\n", TESTCARD);
            
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