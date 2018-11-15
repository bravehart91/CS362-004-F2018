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
    //Initialize gamestate like in the video
    //Randomize drawntreasure
    //random CardDrawn
    //Z is 0
    int handTestsPassed = 0;
    int handTestsFailed = 0;
    int deckTestsPassed = 0;
    int deckTestsFailed = 0;
    int discardTestsPassed = 0;
    int discardTestsFailed = 0;
//Setting up variables that are found in CardEffect
//NOTE: The system forces some of these to be 0 so randomizing them would not be in line with the system
    int drawnTreasure = 0;
    int temphand[MAX_HAND];
    int cardDrawn = 0;
    int z = 0;

    struct gameState* g = malloc(sizeof(struct gameState));
    struct gameState* test = malloc(sizeof(struct gameState));

    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    int players;
    int currentPlayer;
    int f;
    int randomSeed;

    for (f = 0; f < 5000; f++) {
        randomSeed = floor(Random() * 50000);
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

        useAdventurer(g, drawnTreasure, temphand, z, currentPlayer, cardDrawn);

        //I expect this to fail 100% of the time as the bug I introduced to the adventurer card during assignment 2 was to miscount treasures
        if (g->handCount[currentPlayer] == (test->handCount[currentPlayer]) + 2) {
            //printf("Proper treasures were drawn: PASSED\n");
            handTestsPassed++;
        } else {
            //printf("Wrong number of treasures: FAILED\n");
            handTestsFailed++;
        }

        if (test->deckCount[currentPlayer] > g->deckCount[currentPlayer]) {
            //printf("The deck is less than before: PASSED\n");
            deckTestsPassed++;
        } else {
            //printf("Deck has increased somehow: FAILED\n");
            deckTestsFailed++;
        }

        if (test->discardCount[currentPlayer] <= g->discardCount[currentPlayer]) {
            //printf("The discard pile has increased or stayed the same (if 2 treasures are drawn): PASSED\n");
            discardTestsPassed++;
        } else {
            //printf("Discard pile decreased somehow: FAILED\n");
            discardTestsFailed++;
        }
    }
    printf("randomTestAdventurer results: \n");
    printf("Number of handcount tests passed: %d\n", handTestsPassed);
    printf("Number of handcount tests failed: %d\n", handTestsFailed);
    printf("Number of deckcount tests passed: %d\n", deckTestsPassed);
    printf("Number of deckcount tests failed: %d\n", deckTestsFailed);
    printf("Number of discardcount tests passed: %d\n", discardTestsPassed);
    printf("Number of discardcount tests failed: %d\n\n", discardTestsFailed);
}
