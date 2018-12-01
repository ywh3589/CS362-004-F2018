#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

int checkCardEffect(int thisPlayer, int card, int choice1, int choice2, int choice3, struct gameState *G, int handpos, int *bonus);
void customAssert(int a, int b);

int main () {

  int i, n, r, p, deckCount, handCount, choice1, choice2, choice3, handpos;
  int bonus = 0;
  int seed = 1000;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf("before initializeGame G's hand count = %d\n", G.handCount[0]);
  printf("before initializeGame G's deck count = %d\n", G.deckCount[0]);
  printf("before initializeGame G's discard count = %d\n", G.discardCount[0]);
  //G.discardCount[0] = 0;
  //printf("after sentencing = %d\n", G.discardCount[0]);
  


  printf ("Testing village card.\n");

  printf ("RANDOM TESTS.\n");

  initializeGame(2, k, seed, &G);
  


  SelectStream(2);
  PutSeed(3);


  for (n = 0; n < 5; n++) {
      
    G.deckCount[p] = floor(Random() * 10);
    G.discardCount[p] = floor(Random() * 10);
    G.handCount[p] = floor(Random() * 10);
	
    //내용도 randomm하게 넣자
    for(i = 0; i < G.deckCount[p]; i++)
    {
    	G.deck[p][i] = floor(Random() * 7);
    	//G.deck[p][i] = 4;
    }
	for(i = 0; i < G.discardCount[p]; i++)
	{
		G.discard[p][i] = floor(Random() * 7);
		//G.discard[p][i] = 4;
	}
	for(i = 0; i < G.handCount[p]; i++)
	{
		//G.hand[p][i] = 4;
		G.hand[p][i] = floor(Random() * 7);
	}


  handpos = floor(Random() * 7);

  if(handpos >= G.handCount[p])
    handpos = 0;


    printf("deck count %d, discard count %d, handCount %d\n", G.deckCount[p], G.discardCount[p], G.handCount[p]);
    printf("handpos %d\n", handpos);
    checkCardEffect(p, k[7], choice1, choice2, choice3, &G, handpos, &bonus);
  }

  printf ("ALL TESTS OK\n");


  return 0;
}



int checkCardEffect(int thisPlayer, int card, int choice1, int choice2, int choice3, struct gameState *G, int handpos, int *bonus) {
 // copy the game state to a test case
  //struct gameState testG;
  int i, newCards, xtraCoins,xtraActions, shuffledCards, z, cardDrawn = 0;
  int currentPlayer = 0;
  int discarded = 1;
  struct gameState testG;
  int temphand[MAX_HAND];
  
  memcpy(&testG, G, sizeof(struct gameState));
  //choice1 = 1;
  printf("after deck count %d, discard count %d, handCount %d\n", G->deckCount[thisPlayer], G->discardCount[thisPlayer], G->handCount[thisPlayer]);

  //before calling village
  /*
  printf("\nBefore calling cardEffect function\n"); 
  printf("hand count = %d\n", testG.handCount[thisPlayer]);
  printf("showing hand contents \n");
  for(i = 0 ; i < testG.handCount[thisPlayer]; i++)
    printf("[%d]th = %d\n", i+1, testG.hand[thisPlayer][i]);

  printf("deck count = %d\n", testG.deckCount[thisPlayer]); 
  printf("showing deck contents \n");
  for(i = 0 ; i < testG.deckCount[thisPlayer]; i++)
    printf("[%d]th = %d\n", i+1, testG.deck[thisPlayer][i]);
  
  printf("discard count = %d\n", testG.discardCount[thisPlayer]);
  printf("showing discard contents \n");
  for(i = 0 ; i < testG.discardCount[thisPlayer]; i++)
    printf("[%d]th = %d\n", i+1, testG.discard[thisPlayer][i]);
    
*/
  cardEffect(card, choice1, choice2, choice3, &testG, handpos, &bonus);
 printf("after calling function deck count %d, discard count %d, handCount %d\n", G->deckCount[thisPlayer], G->discardCount[thisPlayer], G->handCount[thisPlayer]);

   //using G
   int run = 0;
   int drawnTreasure = 0;
  //choice1 = 1;
  
  newCards = 1;
  xtraCoins = 0;
  xtraActions = 2;
  shuffledCards = 0;
    if(G->deckCount[thisPlayer] <= 0)
       shuffledCards = G->discardCount[thisPlayer];
  printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G->handCount[thisPlayer] + newCards - discarded);
  printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G->deckCount[thisPlayer] - newCards + shuffledCards);
  printf("coins = %d, expected = %d\n", testG.coins, G->coins + xtraCoins);
  printf("actions = %d, expected = %d\n", testG.numActions, G->numActions + xtraActions);
  
  customAssert(testG.handCount[thisPlayer], G->handCount[thisPlayer] + newCards - discarded);
  customAssert(testG.deckCount[thisPlayer], G->deckCount[thisPlayer] - newCards + shuffledCards);
  customAssert(testG.coins, G->coins + xtraCoins);
  customAssert(testG.numActions, G->numActions + xtraActions);
 
//  customAssert(testG.discardCount[thisPlayer], G->deckCount[thisPlayer]);
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