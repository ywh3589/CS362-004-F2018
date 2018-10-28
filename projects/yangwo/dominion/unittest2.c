/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
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
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;

    printf ("TESTING isGameOver():\n");

                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

                //test 1, when supplyCount[province] == 0, it should return 1
                G.supplyCount[province] = 0;
                int firstTestResul = isGameOver(&G);

                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                
                //test 2, when supplyCount[0], supplyCount[1], supplyCount[2] == 0, it should return 1
                G.supplyCount[0] = G.supplyCount[1] = G.supplyCount[2] = 0;
                int secondTestResul = isGameOver(&G);

                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                
                //test 3, when supplyCount[0], supplyCount[1] == 0, it should return 0
                G.supplyCount[0] = G.supplyCount[1] = 0; 
                int thirdTestResul = isGameOver(&G);


                customAssert(firstTestResul, secondTestResul, thirdTestResul);


    return 0;
}

int customAssert(int a, int b, int c){

    if(a == 1)
    {
        if(b == 1)
        {
            if(c == 0)
            {
                 printf("All tests passed!\n");
            }   
            else
            {
                printf("tests failed!\n");

            }    
        }
        else
        {
            printf("tests failed!\n");
        }
    
    }
    else
    {
        printf("tests failed!\n");
    }

    return 0;
}
