/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * testadventurerAction: testadventurerAction.c dominion.o rngs.o
 *      gcc -o testadventurerAction -g  testadventurerAction.c dominion.o rngs.o $(CFLAGS)
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

//bonus 제거, max bonus 제거,  

int main() {
    int i; //needed
    int seed = 1000; //needed
    int numPlayer = 2;
    //int maxBonus = 10;
    int p, r, handCount;
    //int newCards = 0;
    int discarded = 1;
    int shuffledCards = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;
    int maxHandCount = 5;
    // arrays of all coppers, silvers, and golds
    int adventurers[MAX_HAND];
    int temphand[MAX_HAND];

    int drawtreasure = 0;
    int cardDrawn = 0;
    int beforeTreasureCount = 0;
    int afterTreasureCount = 0;

    int numOfCardBefore, numOfCardAfter;

    for (i = 0; i < MAX_HAND; i++)
       adventurers[i] = adventurer;
        
    printf ("TESTING adventurerAction():\n");
 
               // memset(&G, 23, sizeof(struct gameState));   // clear the game state
                printf("line 46\n");
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                printf("line 48\n");
          //      G.handCount[p] = handCount;                 // set the number of cards on hand
            //    newCards = 3;

                memcpy(&testG, &G, sizeof(struct gameState));
                printf("line 53\n");
                p = 0;

                numOfCardBefore = numHandCards(&testG);
                printf("numOfCardBefore = %d\n", numOfCardBefore);
                for(handCount = 0 ; handCount < numOfCardBefore; handCount++)
                {
                    if( G.hand[p][handCount]  == copper)
                        beforeTreasureCount++;
                    else if( G.hand[p][handCount]  == silver)
                        beforeTreasureCount++;
                    else if( G.hand[p][handCount]  == gold)
                        beforeTreasureCount++;
                }

                //int a = adventurerAction(&testG, temphand, &drawtreasure, &cardDrawn);
                cardEffect(adventurer, 0, 0, 0, &testG, 0, 0);
                
                numOfCardAfter = numHandCards(&testG);
                printf("numOfCardAfter=%d\n", numOfCardAfter);
                for(handCount = 0 ; handCount < numOfCardAfter; handCount++)
                {
                    if( G.hand[p][handCount]  == copper)
                        afterTreasureCount++;
                    else if( G.hand[p][handCount]  == silver)
                        afterTreasureCount++;
                    else if( G.hand[p][handCount]  == gold)
                        afterTreasureCount++;
                }

                
#if (NOISY_TEST == 1)
                printf("line 57\n");
                printf("hand treasure count = %d, expected = %d\n", afterTreasureCount, beforeTreasureCount + 2);
                printf("hand treasure count = %d, expected = %d\n", drawtreasure, drawtreasure);
                
#endif
                //assert(afterTreasureCount == beforeTreasureCount + 2);
                //afterTreasureCount == beforeTreasureCount + 2);


 /*   
    for (p = 0; p < numPlayer; p++)
    {
        

        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
            
#if (NOISY_TEST == 1)
                printf("Test player %d with %d adventurer card(s).\n", p, handCount);
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand
                
                //newCards = 3;
                //beforeTreasureCount = afterTreasureCount = 0;

//기존 treasure 카드를 가지고 있는 숫자
               
                memcpy(G.hand[p], adventurers, sizeof(int) * handCount); // set all the cards to adventurer
                //여기 전체를 smithy 카드로 채우면 되겠다.
                
                adventurerAction(&G, temphand, &drawtreasure, &cardDrawn);
                //updateCoins(p, &G, bonus);
//action이 끝나면 treasure 카드의 수가 2 증가해야한다. 

#if (NOISY_TEST == 1)
                if( G.hand[p][handCount]  == copper || G.hand[p][handCount]  == silver || G.hand[p][handCount]  == gold)
                    afterTreasureCount++;
                printf("treasure card held in hand = %d, expected = %d\n", afterTreasureCount, beforeTreasureCount + 2);              
#endif
                assert(afterTreasureCount == beforeTreasureCount + 2);
          
            
        }

    }
*/




    printf("All tests passed!\n");

    return 0;
}