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
    int handTestsPassed = 0;
    int handTestsFailed = 0;
    int deckTestsPassed = 0;
    int deckTestsFailed = 0;
    int discardCountPassed = 0;
    int discardCountFailed = 0;
	int numActionTestPassed = 0;
	int numActionTestFailed = 0;
	
//Setting up variables that are found in CardEffect
	struct gameState* g = malloc(sizeof(struct gameState));
    struct gameState* test = malloc(sizeof(struct gameState));
	
	int z = 0;

    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    int players;
    int currentPlayer;
    int f;
    int randomSeed;

    for (f = 0; f < 5000; f++) {
        randomSeed = floor(Random() * 25000);
        PutSeed(randomSeed);
        players = floor(Random() * MAX_PLAYERS);
        if (players == 0)
        {
            players += 2;
        }


        initializeGame(players, k, randomSeed, g);

        currentPlayer = 0;
        g->deckCount[currentPlayer] = floor(Random() * MAX_DECK);
        memcpy(test, g, sizeof(struct gameState));
		g->hand[0][0] = smithy;
		
        useSmithy(g, currentPlayer, 0, z);

		//I expect all these to fail as one of my introduced bugs is to make smithy draw 4 cards instead of 3; I check for two since you discard the smithy
        if (g->handCount[currentPlayer] == (test->handCount[currentPlayer] + 2)) {
            handTestsPassed++;
        } else {
            handTestsFailed++;
        }
		//I expect all these to fail as one of my introduced bugs is to make smithy draw 4 cards instead of 3
        if (test->deckCount[currentPlayer] - 3 == g->deckCount[currentPlayer]) {
            deckTestsPassed++;
        } else {
            deckTestsFailed++;
        }

        if (test->discardCount[currentPlayer] <= g->discardCount[currentPlayer]) 
		{
            discardCountPassed++;
        } else {
            discardCountFailed++;
        }
		
		if (test->numActions == g->numActions)
		{
			numActionTestPassed++;
		} else {
			numActionTestFailed++;
		}
    }
    printf("randomTestCard2 results: \n");
    printf("Number of handcount tests passed: %d\n", handTestsPassed);
    printf("Number of handcount tests failed: %d\n", handTestsFailed);
    printf("Number of deckcount tests passed: %d\n", deckTestsPassed);
    printf("Number of deckcount tests failed: %d\n", deckTestsFailed);
    printf("Number of discard count tests passed: %d\n", discardCountPassed);
    printf("Number of discard count tests failed: %d\n", discardCountFailed);
	printf("Number of actions remained same tests passed: %d\n", numActionTestPassed++);
	printf("Number of actions remained same tests failed: %d\n\n", numActionTestFailed++);
	
	return 0;
}