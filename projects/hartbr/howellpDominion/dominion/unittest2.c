#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdbool.h>

//This tests the compare helper function

int main() {
	int big = 100;
	int small = 1;
	int zero = 0;
	int negativeSmall = -1;
	int negativeBig = -100;
	
	if (compare(big, small) == 1)
		printf("Big positive int > small positive int, TEST 1 PASSED\n");
	else
		printf("Big/small positive int mismatch, TEST 1 FAILED\n");
	
	if (compare(small, big) == -1)
		printf("Big positive int > small positive int, TEST 2 PASSED\n");
	else
		printf("Big/small positive int mismatch, TEST 2 FAILED\n");
	
	if (compare(big, big) == 0)
		printf("Two of same positive ints equal, TEST 3 PASSED\n");
	else
		printf("Two of same positive ints not equal, TEST 3 FAILED\n");
	
	if (compare(negativeSmall, negativeSmall) == 0)
		printf("Negative ints same, TEST 4 PASSED\n");
	else
		printf("Negative ints not same, TEST 4 FAILED\n");
	
	if (compare(negativeBig, negativeSmall) == -1)
		printf("Negative int big < small, TEST 5 PASSED\n");
	else
		printf("Negative ints mismatched, TEST 5 FAILED\n");
	
	if (compare(negativeSmall, negativeBig) == 1)
		printf("Negative int small > big, TEST 6 PASSED\n");
	else
		printf("Negative ints mismatched, TEST 6 FAILED\n");
	
	if (compare(small, zero) == 1)
		printf("Positive int bigger than 0, TEST 7 PASSED\n");
	else
		printf("Zero mismatch, TEST 7 FAILED\n");
		
	if (compare(negativeSmall, zero) == -1)
		printf("Negative smaller than 0, TEST 8 PASSED\n");
	else
		printf("Zero mismatch, TEST 8 FAILED\n");
	
	if (compare(zero, zero) == 0)
		printf("Zero equals zero, TEST 9 PASSED\n");
	else
		printf("Zero eqaulity mismatch, TEST 9 FAILED\n");
	
	return 0;
	
}