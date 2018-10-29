#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdbool.h>

//This tests the shuffle function

int main() {
	int seed = 1000;
	int numPlayers = 2;
	int maxBonus = 0;
	int p, r, handCount;
	int bonus;
	int thisPlayer = 0;
	
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,sea_hag, tribute, smithy, council_room};
	
	struct gameState S, zeroCard, testS;
	initializeGame(numPlayers, k, seed, &S);
	memcpy(&testS, &S, sizeof(struct gameState));
	memcpy(&zeroCard, &S, sizeof(struct gameState));
	
	struct gameState *modifiedS;
	modifiedS = &S;
	struct gameState *zeroC;
	zeroC = &zeroCard;
	
	shuffle(thisPlayer, modifiedS);
	
	
	if (modifiedS->deckCount[thisPlayer] == testS.deckCount[thisPlayer]) {
		printf("DeckCount has not changed, TEST 1 PASSED\n");
	}
	else {
		printf("DeckCount changed, TEST 1 FAILED\n");
	}
	
	zeroC->deckCount[thisPlayer] = 0;
	if (shuffle(thisPlayer, zeroC) == -1) {
		printf("Deck with zero cards will not shuffle, TEST 2 PASSED\n");
	}
	else {
		printf("Deck with zero cards, TEST 2 FAILED\n");
	}
	
	bool cardDiff = false;
	
	for (p = 0; p < modifiedS->deckCount[thisPlayer]; p++) {
		if (modifiedS->deck[thisPlayer][p] != testS.deck[thisPlayer][p]) {
			cardDiff = true;
		}
	}
	if (cardDiff == false) {
		printf("Cards are different, TEST 3 PASSED\n");
	}
	else {
		printf("Cards are not different or were shuffled into same order, TEST 3 FAILED\n");
	}
	
	return 0;
	
}