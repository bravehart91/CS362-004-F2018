#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>

int main()
{
	//Setting up test variables
    int handTestsPassed = 0;
    int handTestsFailed = 0;
    int deckTestsPassed = 0;
    int deckTestsFailed = 0;
    int numActionsPassed = 0;
    int numActionsFailed = 0;

    struct gameState* g = malloc(sizeof(struct gameState));
    struct gameState* test = malloc(sizeof(struct gameState));

    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    int players;
    int currentPlayer;
    int f;
    int randomSeed;
//Main loop
    for (f = 0; f < 5000; f++) {
        randomSeed = floor(Random() * 25000);
        PutSeed(randomSeed);
        players = floor(Random() * MAX_PLAYERS);
		//Want to make sure floor doesn't pick 0 players
        if (players == 0)
        {
            players += 2;
        }


        initializeGame(players, k, randomSeed, g);

        currentPlayer = 0;
		//Randomize the deck count
        g->deckCount[currentPlayer] = floor(Random() * MAX_DECK);
        memcpy(test, g, sizeof(struct gameState));
		g->hand[0][0] = village;
		//Use a random handpos here
        useVillage(g, currentPlayer, 0);

        if (g->handCount[currentPlayer] == (test->handCount[currentPlayer])) {
            handTestsPassed++;
        } else {
            handTestsFailed++;
        }

        if (test->deckCount[currentPlayer] - 1 == g->deckCount[currentPlayer]) {
            deckTestsPassed++;
        } else {
            deckTestsFailed++;
        }

        if (test->numActions + 2 == g->numActions) 
		{
            numActionsPassed++;
        } else {
            numActionsFailed++;
        }
    }
    printf("randomTestCard1 results: \n");
    printf("Number of handcount tests passed: %d\n", handTestsPassed);
    printf("Number of handcount tests failed: %d\n", handTestsFailed);
    printf("Number of deckcount tests passed: %d\n", deckTestsPassed);
    printf("Number of deckcount tests failed: %d\n", deckTestsFailed);
    printf("Number of action comparison tests passed: %d\n", numActionsPassed);
    printf("Number of action comparison tests failed: %d\n\n", numActionsFailed);
	
	return 0;
}