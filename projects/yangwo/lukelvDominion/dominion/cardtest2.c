/*
 * cardtest2.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest_2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"


void customAssert(int a, int b);


int main() {
    int newCards = 0;
    int discarded = 0;
    int xtraCoins = 0;
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

	// ----------- TEST 1: +2 cards in hand from deck--------------
	printf("TEST 1: choice1 = 1 = +2 cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	

	//before calling adventurer
	printf("hand count = %d\n", testG.handCount[thisPlayer]);
	printf("showing hand contents \n");
	for(i = 0 ; i < testG.handCount[thisPlayer]; i++)
		printf("[%d]th = %d\n", i+1, testG.hand[thisPlayer][i]);

	printf("deck count = %d\n", testG.deckCount[thisPlayer]);	
	printf("showing deck contents \n");
	for(i = 0 ; i < testG.deckCount[thisPlayer]; i++)
		printf("[%d]th = %d\n", i+1, testG.deck[thisPlayer][i]);
	
	printf("discard count = %d\n", testG.discard[thisPlayer]);
		

	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 2;
	xtraCoins = 0;

	//after calling adventure
	printf("hand count = %d\n", testG.handCount[thisPlayer]);
	printf("showing hand contents \n");
	for(i = 0 ; i < testG.handCount[thisPlayer]; i++)
		printf("[%d]th = %d\n", i+1, testG.hand[thisPlayer][i]);
	
	printf("deck count = %d\n", testG.deckCount[thisPlayer]);
	printf("showing deck contents \n");
	for(i = 0 ; i < testG.deckCount[thisPlayer]; i++)
		printf("[%d]th = %d\n", i+1, testG.deck[thisPlayer][i]);
	
	printf("discard count = %d\n", testG.discard[thisPlayer]);
	

	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	
	
	customAssert(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	customAssert(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);

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

