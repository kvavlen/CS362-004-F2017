/* ******************************************************************************
Program: cardtest2.c
Author: Natasha Kvavle
Function Tested: adventurer_effect() via cardEffect()
Course: CS 362
Assignment: 3
Date: 10/22/2017
References: Located in Assignment-3.pdf (Canvas submission)
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
			printf("cardEffect() / adventurer_effect(): Pass - %s: Expected %d, Actual %d\n", details, value2, value1);
		}
		return 1;
	}
	else {
		if (DEBUG_TEST) {
			printf("cardEffect() / adventurer_effect(): Fail - %s: Expected %d, Actual %d		************\n", details, value2, value1);
		}
		return 0;
	}
}

// assertFalse
//	Compares value1 (actual value) and value2 (expected value to not be equal to) and prints results with message 
//	Returns 1 if values are not equal, 0 otherwise
int assertFalse(char *details, int value1, int value2) {
	if (value1 != value2) {
		if (DEBUG_TEST) {
			printf("cardEffect() / adventurer_effect(): Pass - %s: Expected Not %d, Actual %d\n", details, value2, value1);
		}
		return 1;
	}
	else {
		if (DEBUG_TEST) {
			printf("cardEffect() / adventurer_effect(): Fail - %s: Expected Not %d, Actual %d		************\n", details, value2, value1);
		}
		return 0;
	}
}

int main() {

	if (DEBUG_TEST) {
		printf("\n\n>>>>>>> CARD TEST 2: ADVENTURER_EFFECT() <<<<<<<<\n\n");
	}

	// Keep track of how many tests are passing of those attempted
	int result = 0; 


	// Initialize values 
	struct gameState test, compare; 
	int seed = 100; 
	int k[10] = { adventurer, smithy, remodel, feast, mine, sea_hag, tribute, treasure_map, council_room, village };	// randomly chosen, only real importance is that it contains our adventurer card																												
	// Input for numPlayers
	int minPlayers = 2;
	int midPlayers = 3; 
	int maxPlayers = 4; // based on fact that MAX_PLAYERS = 4
	int numPlayers[3] = { minPlayers, midPlayers, maxPlayers }; 

	// Input required for cardEffect, but not our function -- included so that the function can be called via cardEffect 
	//		and therefore implemented as a switch statement or separate function
	int choice1 = 0; 
	int choice2 = 0; 
	int choice3 = 0;
	int bonus = 0; 

	// Input for handPos
	int minPos = 0; 
	int midPos = 2; 
	int maxPos = 4; 
	int handPos[3] = { minPos, midPos, maxPos }; 
	
	// Iterators 
	int i, l, m, n;

	// Setup: Empty Deck, Full Discard 

	for (i = 1; i < 3; i++) {

		for (n = 0; n < 3; n++) {										// test with min/max position of Adventurer card in hand

			if (DEBUG_TEST) {
				printf("\n\nTEST: Number of players - %d, Position of Adventurer Card - %d, Player 0 has full discard, empty deck \n\n", numPlayers[i], handPos[n]);
			}
	
			// Only testing with starting player as player 0
			initializeGame(numPlayers[i], k, seed, &test);
			test.deckCount[0] = 0;
			test.discardCount[0] = MAX_DECK;
			memcpy(&compare, &test, sizeof(struct gameState));

			result += assertTrue("Return Value", cardEffect(adventurer, choice1, choice2, choice3, &test, handPos[n], &bonus), 0); // test if returns 0
			result--;

			for (l = 0; l < 27; l++) {
				if (DEBUG_TEST) {
					printf("Supply Card %d -", l);
				}
				result += assertTrue("Supply Count", test.supplyCount[l], compare.supplyCount[l]);
				result--;
			}

			if (DEBUG_TEST) {
				printf("Player: %d - ", 0);
			}

			// Make sure 2 cards got added to hand and the adventurer card is discarded
			result += assertTrue("Hand Count", test.handCount[0], compare.handCount[0] + 1);
			result--;

			if (DEBUG_TEST) {
				printf("Player: %d - ", 0);
			}

			// Check that the last 2 cards added to hand are treasure cards 
			if (assertTrue("Last Card Added to Hand", test.hand[0][test.handCount[0] - 1], copper) || assertTrue("Last Card Added to Hand", test.hand[0][test.handCount[0] - 1], silver) || assertTrue("Last Card Added to Hand", test.hand[0][test.handCount[0] - 1], gold)) {
				// do nothing
			}
			else {
				result--;
			}

			if (DEBUG_TEST) {
				printf("Player: %d - ", 0);
			}

			if (assertTrue("Second to Last Card Added to Hand", test.hand[0][test.handCount[0] - 2], copper) || assertTrue("Second to Last Card Added to Hand", test.hand[0][test.handCount[0] - 2], silver) || assertTrue("Second to Last Card Added to Hand", test.hand[0][test.handCount[0] - 2], gold)) {
				// do nothing
			}
			else {
				result--;
			}


			if (DEBUG_TEST) {
				printf("Player: %d - ", 0);
			}

			// Check deck count, discard count 
			result += assertFalse("Deck Count", test.deckCount[0], 0);		// make sure deck count isn't 0 anymore
			result--;

			// Check other players aren't affected

			for (m = 1; m < numPlayers[i]; m++) {
				if (m != 0) {			// not our current player 

					if (DEBUG_TEST) {
						printf("Other Player %d - ", m);
					}

					result += assertTrue("Hand Count", test.handCount[m], compare.handCount[m]); //hand count doesn't change 
					result--;

					if (DEBUG_TEST) {
						printf("Other Player %d - ", m);
					}

					result += assertTrue("Deck Count", test.deckCount[m], compare.deckCount[m]); //deck count doesn't change
					result--;

					if (DEBUG_TEST) {
						printf("Other Player %d - ", m);
					}

					result += assertTrue("Discard Count", test.discardCount[m], compare.discardCount[m]); // discard count doesn't change 
					result--;
				}
			}
		}
		
	}


	// Setup: Full Deck, Empty Discard

	for (i = 0; i < 3; i++) {

		for (n = 0; n < 3; n++) {										// test with min/max position of Adventurer card in hand

			if (DEBUG_TEST) {
				printf("\n\nTEST: Number of players - %d, Position of Adventurer Card - %d, Player 0 has full deck, empty discard \n\n", numPlayers[i], handPos[n]);
			}

		// Only testing with starting player as player 0
			initializeGame(numPlayers[i], k, seed, &test);
			test.deckCount[numPlayers[i]] = MAX_DECK;
			test.discardCount[numPlayers[i]] = 0;
			memcpy(&compare, &test, sizeof(struct gameState));


			result += assertTrue("Return Value", cardEffect(adventurer, choice1, choice2, choice3, &test, handPos[n], &bonus), 0); // test if returns 0
			result--;

			for (l = 0; l < 27; l++) {
				if (DEBUG_TEST) {
					printf("Supply Card %d - ", l);
				}
				result += assertTrue("Supply Count", test.supplyCount[l], compare.supplyCount[l]);
				result--;
			}

			if (DEBUG_TEST) {
				printf("Player: %d - ", 0);
			}

			// Make sure 2 cards got added to hand and the adventurer card is discarded
			result += assertTrue("Hand Count", test.handCount[0], compare.handCount[0] + 1);
			result--;


			if (DEBUG_TEST) {
				printf("Player: %d - ", 0);
			}

			// Check that the last 2 cards added to hand are treasure cards 
			if (assertTrue("Last Card Added to Hand", test.hand[0][test.handCount[0] - 1], copper) || assertTrue("Last Card Added to Hand", test.hand[0][test.handCount[0] - 1], silver) || assertTrue("Last Card Added to Hand", test.hand[0][test.handCount[0] - 1], gold)) {
				// do nothing
			}
			else {
				result--;
			}

			if (DEBUG_TEST) {
				printf("Player: %d - ", 0);
			}

			if (assertTrue("Second to Last Card Added to Hand", test.hand[0][test.handCount[0] - 2], copper) || assertTrue("Second to Last Card Added to Hand", test.hand[0][test.handCount[0] - 2], silver) || assertTrue("Second to Last Card Added to Hand", test.hand[0][test.handCount[0] - 2], gold)) {
				// do nothing
			}
			else {
				result--;
			}

			if (DEBUG_TEST) {
				printf("Player: %d - ", 0);
			}			

			// Check other players aren't affected

			for (m = 0; m < numPlayers[i]; m++) {
				if (m != 0) {			// not our current player 

					if (DEBUG_TEST) {
						printf("Other Player %d - ", m);
					}

					result += assertTrue("Hand Count", test.handCount[m], compare.handCount[m]); //hand count doesn't change 
					result--;


					if (DEBUG_TEST) {
						printf("Other Player %d - ", m);
					}

					result += assertTrue("Deck Count", test.deckCount[m], compare.deckCount[m]); //deck count doesn't change
					result--;


					if (DEBUG_TEST) {
						printf("Other Player %d - ", m);
					}

					result += assertTrue("Discard Count", test.discardCount[m], compare.discardCount[m]); // discard count doesn't change 
					result--;
				}
			}
		}
	}
	
	if (result == 0) {
		printf("\n\nRESULT: PASS\n");
	}
	else {
		printf("\n\nRESULT: FAIL\n");
	}

	return 0; 
}