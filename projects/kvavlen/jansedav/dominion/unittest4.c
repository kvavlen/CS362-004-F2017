/* ******************************************************************************
Program: unittest4.c
Author: Natasha Kvavle
Function Tested: isGameOver()
Course: CS 362
Assignment: 3
Date: 10/22/2017
Reference: Located in Assignment-3.pdf (Canvas submission)
******************************************************************************** */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

// Toggle debug-related output
#define DEBUG_TEST 1

// assertTrue
//	Compares value1 (actual value) and value2 (expected value) and prints results with message 
//	Returns 1 if values are equal, 0 otherwise
int assertTrue(char *details, int value1, int value2) {
	if (value1 == value2) {
		if (DEBUG_TEST) {
			printf("isGameOver(): Pass - %s: Expected %d, Actual %d\n", details, value2, value1);
		}
		return 1;
	}
	else {
		if (DEBUG_TEST) {
			printf("isGameOver(): Fail - %s: Expected %d, Actual %d		************\n", details, value2, value1);
		}
		return 0;
	}
}

int main() { 


	if (DEBUG_TEST) {
		printf("\n\n>>>>>>> UNIT TEST 4: ISGAMEOVER() <<<<<<<<\n\n");
	}

	int result = 0;

	// Make an array of test games/states
	struct gameState test1, test2, test3, test4, test5, test6;
	struct gameState compare;
	int seed = 100;
	int numPlayers;
	int minPlayers = 2;  // Assumes we have a valid amount -- not looking for initializeGame to fail
	int maxPlayers = 4;
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room }; // Based on Kingdom Cards from cardtest4.c
	int i = 0; 

	for (numPlayers = minPlayers; numPlayers <= maxPlayers; numPlayers++) {			// Create test suite with each number of players possible in game 

		// provinces supply is empty
		if (DEBUG_TEST) {
			printf("\nTEST: Game with %d Players, Province Supply Empty\n", numPlayers);
		}
		initializeGame(numPlayers, k, seed, &test1); 
		test1.supplyCount[province] = 0; 
		memcpy(&compare, &test1, sizeof(struct gameState));
		result += assertTrue("Return Value", isGameOver(&test1), 1); 
		result--; 


			// test state changes after call to isGameOver -- with regard to supply count 
			for (i = 0; i < 27; i++) {
				if (DEBUG_TEST) {
					printf("CARD: %d - ", i); 
				}
				result += assertTrue("Supply Count", test1.supplyCount[i], compare.supplyCount[i]);
				result--;

			}


		
		// province supply is empty & 3 other supplies used in game are empty 
		if (DEBUG_TEST) {
			printf("\nTEST: Game with %d Players; Province, Adventurer, Embargo, Village Supplies Empty\n", numPlayers);
		}
		initializeGame(numPlayers, k, seed, &test2);
		test2.supplyCount[province] = 0;
		test2.supplyCount[adventurer] = 0; 
		test2.supplyCount[embargo] = 0; 
		test2.supplyCount[village] = 0; 
		memcpy(&compare, &test2, sizeof(struct gameState));

		result += assertTrue("Return Value", isGameOver(&test2), 1);
		result--;

			// test state changes after call to isGameOver -- with regard to supply count 
			for (i = 0; i < 27; i++) {
				if (DEBUG_TEST) {
					printf("Card: %d -", i);
				}
				result += assertTrue("Supply Count", test2.supplyCount[i], compare.supplyCount[i]);
				result--;

			}


		// Province supply is not empty & 3 other supplies are empty
		if (DEBUG_TEST) {
			printf("\nTEST: Game with %d Players; Cutpurse, Sea Hag, Minion (3) Supplies Empty\n", numPlayers);
		}
		initializeGame(numPlayers, k, seed, &test3);
		test3.supplyCount[cutpurse] = 0;
		test3.supplyCount[sea_hag] = 0;
		test3.supplyCount[minion] = 0;
		memcpy(&compare, &test3, sizeof(struct gameState));

		result += assertTrue("Return Value", isGameOver(&test3), 1);
		result--;

			// test state changes after call to isGameOver -- with regard to supply count 
			for (i = 0; i < 27; i++) {
				if (DEBUG_TEST) {
					printf("Card: %d -", i);
				}
				result += assertTrue("Supply Count", test3.supplyCount[i], compare.supplyCount[i]);
				result--;

			}

		// 2 Supplies are empty 
		if (DEBUG_TEST) {
			printf("\nTEST: Game with %d Players; Minion, Sea Hag Supplys Empty\n", numPlayers);
		}
		initializeGame(numPlayers, k, seed, &test4);
		test4.supplyCount[sea_hag] = 0;
		test4.supplyCount[minion] = 0;
		memcpy(&compare, &test4, sizeof(struct gameState));

		result += assertTrue("Return Value", isGameOver(&test4), 0);
		result--;

			// test state changes after call to isGameOver -- with regard to supply count 
			for (i = 0; i < 27; i++) {
				if (DEBUG_TEST) {
					printf("Card: %d -", i);
				}
				result += assertTrue("Supply Count", test4.supplyCount[i], compare.supplyCount[i]);
				result--;
			}

		// 1 other supply is empty 
		if (DEBUG_TEST) {
			printf("\nTEST: Game with %d Players; Sea Hag Supply Empty\n", numPlayers);
		}
		initializeGame(numPlayers, k, seed, &test5);
		test5.supplyCount[sea_hag] = 0;
		memcpy(&compare, &test5, sizeof(struct gameState));

		result += assertTrue("Return Value", isGameOver(&test5), 0);
		result--;
		
		// test state changes after call to isGameOver -- with regard to supply count 
		for (i = 0; i < 27; i++) {
			if (DEBUG_TEST) {
				printf("Card: %d -", i);
			}
			result += assertTrue("Supply Count", test5.supplyCount[i], compare.supplyCount[i]);
			result--;

		}
		
		// no other supplies are empty 
		if (DEBUG_TEST) {
			printf("\nTEST: Game with %d Players, No Empty Supplies\n", numPlayers);
		}
		initializeGame(numPlayers, k, seed, &test6);
		memcpy(&compare, &test6, sizeof(struct gameState));

		result += assertTrue("Return Value", isGameOver(&test6), 0);
		result--;

		// test state changes after call to isGameOver -- with regard to supply count 
		for (i = 0; i < 27; i++) {
			if (DEBUG_TEST) {
				printf("Card: %d -", i);
			}
			result += assertTrue("Supply Count", test6.supplyCount[i], compare.supplyCount[i]);

		}
	}




	if (result == 0) {
		printf("\n\nRESULTS: ALL TESTS PASSED\n");
	}
	else {
		printf("\n\nRESULTS: FAIL\n");
	}


	return 0; 

}


