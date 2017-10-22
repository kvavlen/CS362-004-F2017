/* ******************************************************************************
Program: cardtest1.c
Author: Natasha Kvavle
Function Tested: smithy_effect() via cardEffect()
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
			printf("cardEffect() / smithy_effect(): Pass - %s: Expected %d, Actual %d\n", details, value2, value1);
		}
		return 1;
	}
	else {
		if (DEBUG_TEST) {
			printf("cardEffect() / smithy_effect(): Fail - %s: Expected %d, Actual %d		************\n", details, value2, value1);
		}
		return 0;
	}
}

// Testing Smithy Card - Reference: Assignment 3 Testing something v. testing for business rules
int main() {


	if (DEBUG_TEST) {
		printf("\n\n>>>>>>> CARD TEST 1: SMITHY_EFFECT() <<<<<<<<\n\n");
	}
	int result = 0;
	int seed = 100;			// random seed 
	int minPlayers = 2;		// Don't want initialize game to crash 
	int maxPlayers = 4;		
	int k[10] = { smithy, adventurer, feast, mine, remodel, sea_hag, treasure_map, tribute, council_room, cutpurse }; // Selected to include card testing
	struct gameState test;
	struct gameState compare;

	int choice1 = 0;	 // These have no affect on smithy 
	int choice2 = 0;
	int choice3 = 0;

	int minHandPos = 0;
	int maxHandPos = 4;
	int bonus = 0;		// This has no affect on smithy 

	int handPos[2] = { minHandPos, maxHandPos };
	int supplyCard; 
	int numPlayers[2] = { minPlayers, maxPlayers };
	int i,  m, l;


	for (i = 0; i < 2; i++) {	// iterate through test scenarios with dif number of players


			for (m = 0; m < 2; m++) {					// test with min and max handPos
				if (DEBUG_TEST) {
					printf("\n\nTEST SETUP: NUMBER OF PLAYERS: %d, ", numPlayers[i]);
				}

				if (DEBUG_TEST) {
					printf("SMITHY HAND POSITION: %d\n\n", handPos[m]);
				}
				initializeGame(numPlayers[i], k, seed, &test);
				test.hand[0][handPos[m]] = smithy;					// Put the card in the starting player's hand 
				memcpy(&compare, &test, sizeof(struct gameState)); // copy memory so we can compare results with expected 

				result += assertTrue("Return Value", cardEffect(smithy, choice1, choice2, choice3, &test, handPos[m], &bonus), 0);
				result--;


				if (DEBUG_TEST) {
					printf("PLAYER %d - ", 0);
				}
				// Now test what happens as a result 
				result += assertTrue("Hand Count", test.handCount[0], compare.handCount[0] - 1 + 3); // Make sure smithy taken out of player's hand 
				result--;

				if (DEBUG_TEST) {
					printf("PLAYER %d - ", 0);
				}

				result += assertTrue("Deck Count", test.deckCount[0], compare.deckCount[0] - 3);	// Make sure that the deck of player decreased by 3
				result--;

				if (DEBUG_TEST) {
					printf("PLAYER %d - ", 0);
				}

				result += assertTrue("Discard Count", test.discardCount[0], compare.discardCount[0] + 1); // Make sure card was discarded 
				result--;


				for (l = 0; l < numPlayers[i]; l++) {					// iterate through other players and make sure their states haven't changed
					if (l != 0) {												// make sure we're not looking at our current player though 
						if (DEBUG_TEST) {
							printf("OTHER PLAYER %d - ", l);
						}
						result += assertTrue("Deck Count", test.deckCount[l], compare.deckCount[l]);
						result--;

						if (DEBUG_TEST) {
							printf("OTHER PLAYER %d - ", l);
						}
						result += assertTrue("Hand Count", test.handCount[l], compare.handCount[l]);
						result--;

						if (DEBUG_TEST) {
							printf("OTHER PLAYER %d - ", l);
						}
						result += assertTrue("Discard Count", test.discardCount[l], compare.discardCount[l]);
						result--;
					}
				}

				for (supplyCard = 0; supplyCard < 27; supplyCard++) {
					if (DEBUG_TEST) {
						printf("SUPPLY: CARD %d -", supplyCard);
					}
					result += assertTrue("Supply Count", test.supplyCount[supplyCard], compare.supplyCount[supplyCard]); // make sure supplies not changed
					result--;
				}

			}
	}
	if (result == 0) {
		printf("\n\nRESULT: ALL TESTS PASSED\n"); 
	}
	else {
		printf("\n\nRESULT: FAILED\n"); 
	}

	return 0; 
}


