/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * unittest3 : unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
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

void customAssert(int *cmpArr);

int main() {
    int i, r, currenPlayer, result, card;
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int costArr[27];
    
    printf ("TESTING getCost():\n");

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    memset(costArr, 0, sizeof(costArr));

    currenPlayer = 0;

    //Test : storing cost which getCost() function returns into costArr 
    //       and compare costArr with stdArr in customAssert() function 

    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    

    for(card = 0 ; card < 27; card++)
    {
        result = getCost(card);
        
        costArr[card] = result;
    }

    customAssert(costArr);

    return 0;
 
}

void customAssert(int *cmpArr){

    //it is already know that each card has its own cost, so stdArr is array of costs for each card.
    //for example, copper's cardnumber is 4 and cost is 0, so stdArr[4] should be 0.
    
    int stdArr[27] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4};

    if(memcmp(stdArr, cmpArr, sizeof(stdArr)) == 0)
    {
        printf("test passed!\n");
    }
    else
    {
        printf("test failed\n");
    }
}