#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

int checkCardEffect(int thisPlayer, int card, int choice1, int choice2, int choice3, struct gameState *G, int handpos, int *bonus);
void customAssert(int a);

int main () {

  int i, n, r, p, deckCount, handCount, choice1, choice2, choice3, handpos;
  int bonus = 0;
  int seed = 1000;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;


  printf ("Testing adventurer card.\n");

  printf ("RANDOM TESTS.\n");

  initializeGame(2, k, seed, &G);
  
 



 SelectStream(2);
  PutSeed(3);


  for (n = 0; n < 5; n++) {
    
    p = 0;
    
    /*
     G.deckCount[p] = floor(Random() * MAX_DECK);
     G.discardCount[p] = floor(Random() * MAX_DECK);
     G.handCount[p] = floor(Random() * MAX_HAND);
    */

    
    G.deckCount[p] = floor(Random() * 10);
    G.discardCount[p] = floor(Random() * 10);
    G.handCount[p] = floor(Random() * 10);
	
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

    printf("deck count %d, discard count %d, handCount %d\n", G.deckCount[p], G.discardCount[p], G.handCount[p]);
   
     checkCardEffect(p, k[0], choice1, choice2, choice3, &G, handpos, &bonus);
  }

  return 0;
}

int checkCardEffect(int thisPlayer, int card, int choice1, int choice2, int choice3, struct gameState *G, int handpos, int *bonus) {
 // copy the game state to a test case
  //struct gameState testG;
  int i, newCards, xtraCoins, shuffledCard, z, cardDrawn = 0;
  int currentPlayer = 0;
  int discarded = 0;
  struct gameState testG;
  int temphand[MAX_HAND];
  
  memcpy(&testG, G, sizeof(struct gameState));
  //choice1 = 1;
  

  //before calling adventurer
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
    

  cardEffect(card, choice1, choice2, choice3, &testG, handpos, &bonus);

   //using G
   int run = 0;
   int drawnTreasure = 0;
   while((drawnTreasure < 2) || (run < MAX_DECK)){
   		if(G->deckCount[currentPlayer] < 1){
   			shuffle(currentPlayer, G);
   		}
   		drawCard(currentPlayer, G);
   		cardDrawn = G->hand[currentPlayer][G->handCount[currentPlayer]-1];
   		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
	  		drawnTreasure++;
	  	else{
			  G->discard[currentPlayer][G->discardCount[currentPlayer]-1] = cardDrawn;
			  G->discardCount[currentPlayer]++;
			  G->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
			 // z++;
		}
   
		run++;
   }



  
  newCards = 2;
  xtraCoins = 0;

  //after calling adventure
  printf("\nAfter calling cardEffect function\n\n");
  
  printf("\nTestG\n");
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
  
  printf("\nG\n");
  printf("hand count = %d\n", G->handCount[thisPlayer]);
  printf("showing hand contents \n");
  for(i = 0 ; i < G->handCount[thisPlayer]; i++)
    printf("[%d]th = %d\n", i+1, G->hand[thisPlayer][i]);

  printf("deck count = %d\n", G->deckCount[thisPlayer]); 
  printf("showing deck contents \n");
  for(i = 0 ; i < G->deckCount[thisPlayer]; i++)
    printf("[%d]th = %d\n", i+1, G->deck[thisPlayer][i]);
  
  printf("discard count = %d\n", G->discardCount[thisPlayer]);
  printf("showing discard contents \n");
  for(i = 0 ; i < G->discardCount[thisPlayer]; i++)
    printf("[%d]th = %d\n", i+1, G->discard[thisPlayer][i]);


  int result = memcmp(&testG, G, sizeof(G));
  customAssert(result);
  
}


void customAssert(int result){

  if(result == 0)
  {
    printf("test success\n");
  }
  else
  {
    printf("test failed\n");
  }
}

