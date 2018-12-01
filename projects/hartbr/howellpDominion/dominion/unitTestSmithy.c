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
	int drawnTreasure = 0;
    int temphand[MAX_HAND];
    int cardDrawn = 0;
    int z = 0;

	int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
	
    struct gameState* g = malloc(sizeof(struct gameState));
    struct gameState* test = malloc(sizeof(struct gameState));
	
	int players = 2;
	int currentPlayer = 0;
	int randomSeed;
	
	randomSeed = floor(Random() * 50000);
	PutSeed(randomSeed);
	
	initializeGame(players, k, randomSeed, g);
	g->whoseTurn = 0;
	g->deckCount[currentPlayer] = 25;
	memcpy(test, g, sizeof(struct gameState));
	
	playSmithy(currentPlayer,g, 0);
	
	if (g->handCount[currentPlayer] == (test->handCount[currentPlayer] + 2)) {
		printf("Hand size is correct: PASSED\n");
	} else {
		printf("Hand size is wrong: FAILED\n");
	}

	if (test->deckCount[currentPlayer] - 3 == g->deckCount[currentPlayer]) {
		printf("Deck size is 3 cards less than before: PASSED\n");
	} else {
		printf("Deck size is not 3 cards less: FAILED\n");
	}

	if (test->discardCount[currentPlayer] <= g->discardCount[currentPlayer]) 
	{
		printf("Discard pile grew: PASSED\n");
	} else {
		printf("Discard pile did not grow: FAILED\n");
	}
	
	if (test->numActions == g->numActions)
	{
		printf("Actions did not change: PASSED\n");
	} else {
		printf("Actions changed: FAILED\n");
	}
	
	return 0;
}