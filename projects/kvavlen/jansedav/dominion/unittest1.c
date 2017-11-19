/* ******************************************************************************
Program: unittest1.c
Author: Natasha Kvavle
Function Tested: numHandCards()
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
			printf("numHandCards(): Pass - %s: Expected %d, Actual %d\n", details, value2, value1);
		}
		return 1;
	}
	else {
		if (DEBUG_TEST) {
			printf("numHandCards(): Fail - %s: Expected %d, Actual %d		************\n", details, value2, value1);
		}
		return 0;
	}
}

int main() {

	if (DEBUG_TEST) {
		printf("\n\n>>>>>>> UNIT TEST 1: NUMHANDCARDS() <<<<<<<<\n\n");
	}

	int result = 0;						// Keep track of number of tests passed v. attempted; if 0 -> passed all tests
	int seed = 100;						// Seed for initializeGame
	int minPlayers = 2;					// Range of number of players to play each test game
	int maxPlayers = 4; 
	int minHand = 0;					// Range of number of cards player may have in hand 
	int maxHand = 5;
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room }; // Based on Kingdom Cards from cardtest4.c
	struct gameState test;				// Game states for test conditions 
	struct gameState compare;			// Game state to compare test conditions to 

	// Declare variables to later be used / iterators
	int numPlayers;
	int whoseTurn;
	int numCards;
	int i; 

	// Create a test suite for each number of players in the game 
	for (numPlayers = minPlayers; numPlayers <= maxPlayers; numPlayers++) {

		// Handle each num of players
	
			// TEST - Initialized Game State only 
			if (DEBUG_TEST) {
				printf("\n\nTEST: %d Players, Initialized Game State (Player 0 goes first)\n\n", numPlayers);
				
			}
			initializeGame(numPlayers, k, seed, &test);							// initialize game
			memcpy(&compare, &test, sizeof(struct gameState));					// copy current state of the game to the compare gameState

			if (DEBUG_TEST) {
				printf("PLAYER %d - ", 0);
			}
			result += assertTrue("Hand Count/Return Value", numHandCards(&test), compare.handCount[0]);
			result--;


			if (DEBUG_TEST) {
				printf("PLAYER %d - ", 0);
			}
			result += assertTrue("Deck Count", test.deckCount[0], compare.deckCount[0]); 
			result--;


			if (DEBUG_TEST) {
				printf("PLAYER %d - ", 0);
			}
			result += assertTrue("Discard Count", test.discardCount[0], compare.discardCount[0]); 
			result--;

			// Check other player's hands to ensure no state change
			for (i = 1; i < numPlayers; i++) {
				if (DEBUG_TEST) {
					printf("OTHER PLAYER %d -", i);
				}
				// Can't get hand count via numhandcards because not this player's turn 
				result += assertTrue("Hand Count", test.handCount[i], compare.handCount[i]);
				result--;

				if (DEBUG_TEST) {
					printf("OTHER PLAYER %d -", i);
				}
				result += assertTrue("Deck Count", test.deckCount[i], compare.deckCount[i]);
				result--;

				if (DEBUG_TEST) {
					printf("OTHER PLAYER %d -", i);
				}
				result += assertTrue("Discard Count", test.discardCount[i], compare.discardCount[i]);
				result--;
			}
			

			// TEST - Articial Game State (Change whose turn it is, number of cards in hand)

			// Making each player play first 
			for (whoseTurn = 0; whoseTurn < numPlayers; whoseTurn++) {

				for (numCards = minHand; numCards <= maxHand; numCards++) {
					// Check the hand of the player whose turn it is
					if (DEBUG_TEST) {
						printf("\n\nTEST: %d Players, Artificial Game State: Player %d's Turn, Hand Count %d \n\n", numPlayers, whoseTurn, numCards);
					}

					initializeGame(numPlayers, k, seed, &test);
					test.whoseTurn = whoseTurn;
					test.handCount[whoseTurn] = numCards;
					memcpy(&compare, &test, sizeof(struct gameState));


					if (DEBUG_TEST) {
						printf("PLAYER %d -", whoseTurn);
					}
					result += assertTrue("Hand Count / Return Value", numHandCards(&test), compare.handCount[whoseTurn]);
					result--;

					if (DEBUG_TEST) {
						printf("PLAYER %d -", whoseTurn);
					}
					result += assertTrue("Deck Count", test.deckCount[whoseTurn], compare.deckCount[whoseTurn]);
					result--;

					if (DEBUG_TEST) {
						printf("PLAYER %d -", whoseTurn);
					}
					result += assertTrue("Discard Count", test.discardCount[whoseTurn], compare.discardCount[whoseTurn]);
					result--;

					// Check other player's hands
					for (i = 0; i < numPlayers; i++) {

						if (i != whoseTurn) {
							if (DEBUG_TEST) {
								printf("OTHER PLAYER %d -", i);
							}
							// Can't get hand count via numhandcards because not this player's turn 
							result += assertTrue("Return Value", test.handCount[i], compare.handCount[i]);
							result--;

							if (DEBUG_TEST) {
								printf("OTHER PLAYER %d -", i);
							}
							result += assertTrue("Deck Count", test.deckCount[i], compare.deckCount[i]);
							result--;

							if (DEBUG_TEST) {
								printf("OTHER PLAYER %d -", i);
							}
							result += assertTrue("Discard Count", test.discardCount[i], compare.discardCount[i]);
							result--;
						}
					}
				}
			}
		}
	

	// Determine if tests passed or not
	if (result == 0) {
		printf("\n\nRESULT: PASS\n");
	}
	else {
		printf("\n\nRESULT: FAIL\n"); 
	}
	return 0; 
}