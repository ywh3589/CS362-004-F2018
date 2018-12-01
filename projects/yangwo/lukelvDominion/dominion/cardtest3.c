/*
 * cardtest3.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest_3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

void customAssert(int a, int b);

int main() {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int xtraActions = 0;
    int shuffledCards = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: +1 cards and +2 action--------------
	printf("TEST 1:  +1 cards, and +2 actions\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	//choice1 = 1;
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 1;
	xtraCoins = 0;
	xtraActions = 2;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	
	printf("actions = %d, expected = %d\n", testG.numActions, G.numActions + xtraActions);
	
	customAssert(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	customAssert(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	customAssert(testG.coins, G.coins + xtraCoins);
	customAssert(testG.numActions, G.numActions + xtraActions);


// ----------- TEST 2: comparing with another player--------------
	printf("TEST 2: what about another player\n");

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	//choice1 = 1;
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 1;
	xtraCoins = 0;
	xtraActions = 2;
	printf("\nplayer\n");
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	
	printf("actions = %d, expected = %d\n", testG.numActions, G.numActions + xtraActions);
	
	customAssert(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	customAssert(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	customAssert(testG.coins, G.coins + xtraCoins);
	customAssert(testG.numActions, G.numActions + xtraActions);

	printf("\nanother player\n");
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer+1], G.handCount[thisPlayer+1]);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer+1], G.deckCount[thisPlayer+1]);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins);
	printf("actions = %d, expected = %d\n", testG.numActions, G.numActions);
	customAssert(testG.handCount[thisPlayer+1], G.handCount[thisPlayer+1]);
	customAssert(testG.deckCount[thisPlayer+1], G.deckCount[thisPlayer+1]);
	customAssert(testG.coins, G.coins);
	customAssert(testG.numActions, G.numActions);

	return 0;
}


void customAssert(int a, int b){

	if(a == b)
	{
		printf("test success\n");
	}
	else
	{
		printf("test failed\n");
	}
}


