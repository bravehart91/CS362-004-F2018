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
	g->deckCount[currentPlayer] = floor(Random() * MAX_DECK);
	memcpy(test, g, sizeof(struct gameState));
	
	playAdventurer(g);
	
	if (g->handCount[currentPlayer] == (test->handCount[currentPlayer]) + 2) {
        printf("Proper treasures were drawn: PASSED\n");
    } else {
        printf("Wrong number of treasures: FAILED\n");
    }
	
	if (test->deckCount[currentPlayer] > g->deckCount[currentPlayer]) {
        printf("The deck is less than before: PASSED\n");
    } else {
        printf("Deck has increased somehow: FAILED\n");
    }
	
	if (test->discardCount[currentPlayer] <= g->discardCount[currentPlayer]) {
        printf("The discard pile has increased or stayed the same (if 2 treasures are drawn): PASSED\n");
    } else {
        printf("Discard pile decreased somehow: FAILED\n");
    }
	
	if (test->numActions == g->numActions)
	{
		printf("Number of actions correct: PASSED\n");
	} else {
		printf("Number of actions are wrong: FAILED\n");
	}
	
	return 0;
}