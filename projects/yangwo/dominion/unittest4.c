/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * unittest4 : unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int i, r, currenPlayer, result;
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    
    printf ("TESTING numHandCards():\n");

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    
    currenPlayer = 0;

    //Test 1: result should be "5" because in initializeGame() function, user drawCards() five times.
    
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    result = numHandCards(&G);

    customAssert(result);

    return 0;
 
}

void customAssert(int a){

    //it is already know that when player starts game, they get 5 cards in hands
    //(from initializeGame() function, user drawCards() five times)
    if(a == 5)
    {
        printf("test passed!\n");
    }
    else
    {
        printf("test failed\n");
    }
}