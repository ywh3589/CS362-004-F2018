/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
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
    
    int card, r;
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    int resCmpArray[2] = {0, 0};
    int temp = 0;
    struct gameState G;
    int currentPlayer = 0;

    
    printf ("TESTING fullDeckCount():\n");

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
             
    //testing all cards from 0(estate) to 26(treasure_map)
    for(card = 0; card < 27; card++)
    {
        int result = 0;
        result = fullDeckCount(currentPlayer, card, &G);
        if(result != 0)
        {
            if(temp >=2)
            {
                printf("test failed!\n");
                exit(1);                                
            }
            
            resCmpArray[temp] = card;
            temp++;
        }                   
    }

    customAssert(resCmpArray);

    return 0;
}

void customAssert(int *cmpArray) {

    int stdArray[2] = {1, 4};

    if(memcmp(stdArray, cmpArray, sizeof(stdArray)) == 0)
    {
        printf("all tests passed!\n");
    }     
    else
    {
        printf("test failed!\n");
    }
         
     exit(0);
}