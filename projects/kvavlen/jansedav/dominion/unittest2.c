/* ******************************************************************************
Program: unittest2.c
Author: Natasha Kvavle
Function Tested: initializeGame()
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
			printf("initializeGame(): Pass - %s: Expected %d, Actual %d\n", details, value2, value1);
		}
		return 1;
	}
	else {
		if (DEBUG_TEST) {
			printf("initializeGame(): Fail - %s: Expected %d, Actual %d		************\n", details, value2, value1);
		}
		return 0;
	}
}

int main() {

	if (DEBUG_TEST) {
		printf("\n\n>>>>>>> UNIT TEST 2: INITIALIZEGAME() <<<<<<<<\n\n");
	}

	int result = 0;				// check for 0 at end to determine if passed all tests
	int seed = 100;

	// Num players
	int numPlayers; 
	int minPlayers = 1;
	int maxPlayers = 5;

	// Kingdom card sets - min/mid/max
	int set_0[0];	// minimum amount of cards
	int set_1[5];	// mid amount of cards, all different
	int set_2[10];	// max amount of cards, all different
	int set_3[10];	// max amount of cards, all same 

	// Iterators
	int i, j, l, m, n, p;

	// Put correct number of kingdom cards in sets 
	for (m = 0; m < 10; m++) {
		if (m < 5) {
			set_1[m] = m + 7;
		}
		set_2[m] = m + 7;
		set_3[m] = 7;
	}
	int *k;


	// Make game state variable for each set of Kingdom Cards
	struct gameState test0, test1, test2, test3, compare;
	struct gameState test[4] = { test0, test1, test2, test3 }; 


	
	for (numPlayers = minPlayers; numPlayers <= maxPlayers; numPlayers++) {			// Create test suite with each number of players possible in game 

		for (i = 0; i < 4; i++) {														// Create test cases for possible numbers of kingdom cards

			// Pick set based on iteration
			if (i == 0) {
				k = set_0; // empty
			}
			else if (i == 1) {
				k = set_1; // 5 cards
			}
			else if (i == 2) {
				k = set_2; // 10 cards, all different
			}
			else {
				k = set_3; // 10 cards, all same
			}

			if (DEBUG_TEST) {
				printf("\n\nTEST: Game with %d Players, Kingdom Card Set %d\n\n", numPlayers, i);
			}


			// TEST: Bad number of players
			if (numPlayers == 1 || numPlayers == 5) {

				result += assertTrue("Return Value", initializeGame(numPlayers, k, seed, &test[i]), -1);
				result--;

				// TEST: NUM PLAYERS
				result += assertTrue("Number of Players", test[i].numPlayers, 0);
				result--;

				// initialize game doesn't continue -- returns before performs remaining actions
			}

			// TEST: Good number of players
			else {
				// TEST: bad kingdom card sets
				if (i != 2) {
					result += assertTrue("Return Value", initializeGame(numPlayers, k, seed, &test[i]), -1);
					result--;

					// TEST: NUM PLAYERS
					result += assertTrue("Number of Players", test[i].numPlayers, numPlayers);
					result--;
				}

				// Test: good kingdom card sets
				else {
					result += assertTrue("Return Value", initializeGame(numPlayers, k, seed, &test[i]), 0);
					result--;

					// Save in comparison test gameState
					memcpy(&compare, &test[i], sizeof(struct gameState));

					// TEST: NUM PLAYERS
					result += assertTrue("Number of Players", test[i].numPlayers, numPlayers);
					result--;

					// Count the number of coppers, estates in deck of each player
					for (j = 0; j < numPlayers; j++) {

						int copper_count = 0;
						int estate_count = 0;

						for (l = 0; l < 10; l++) {
							if (test[i].deck[j][l] == 4) {
								copper_count++;
							}
							else if (test[i].deck[j][l] == 1) {
								estate_count++;
							}
						}

						if (DEBUG_TEST) {
							printf("PLAYER %d -", j);
						}

						result += assertTrue("Deck - # Coppers", copper_count, 7);
						result--;

						if (DEBUG_TEST) {
							printf("PLAYER %d -", j);
						}
						result += assertTrue("Deck - # Estates", estate_count, 3);
						result--;

						// Test all players have a deck count of 10
						if (DEBUG_TEST) {
							printf("PLAYER %d -", j);
						}
						result += assertTrue("Deck Count", test[i].deckCount[j], 10);
						result--;

						// Test that the first player (whose turn it is) has a hand count of 5
						if (j == 0) {
							if (DEBUG_TEST) {
								printf("PLAYER %d -", j);
							}

							result += assertTrue("Hand Count", test[i].handCount[j], 5);
							result--;
						}
						else {
							if (DEBUG_TEST) {
								printf("PLAYER %d -", j);
							}
							result += assertTrue("Hand Count", test[i].handCount[j], 0);
							result--;
						}
					}


					// Test: SUPPLY COUNTS

					if (numPlayers == 2) {

						result += assertTrue("Supply - # Curse ", test[i].supplyCount[curse], 20);
						result--;

						result += assertTrue("Supply - Victory - # Estate", test[i].supplyCount[estate], 8);
						result--;

						result += assertTrue("Supply - Victory - # Duchy", test[i].supplyCount[duchy], 8);
						result--;

						result += assertTrue("Supply - Victory - # Province", test[i].supplyCount[province], 8);
						result--;

						result += assertTrue("Supply - Treasure - # Copper ", test[i].supplyCount[copper], 46);
						result--;

						result += assertTrue("Supply - Treasure - # Silver", test[i].supplyCount[silver], 40);
						result--;

						result += assertTrue("Supply - Treasure - # Gold", test[i].supplyCount[gold], 30);
						result--;

						for (n = 0; n < 10; n++) {
							if (k[n] != province && k[n] != duchy && k[n] != estate) {
								if (DEBUG_TEST) {
									printf("CARD %d - ", k[n]);
								}
								result += assertTrue("Supply - Kingdom", test[i].supplyCount[k[n]], 10);
								result--;
							}
						}
					}
					else if (numPlayers == 3) {
						result += assertTrue("Supply - # Curse ", test[i].supplyCount[curse], 30);
						result--;

						result += assertTrue("Supply - Victory - # Estate", test[i].supplyCount[estate], 12);
						result--;

						result += assertTrue("Supply - Victory - # Duchy", test[i].supplyCount[duchy], 12);
						result--;

						result += assertTrue("Supply - Victory - # Province", test[i].supplyCount[province], 12);
						result--;

						result += assertTrue("Supply - Treasure - # Copper ", test[i].supplyCount[copper], 39);
						result--;

						result += assertTrue("Supply - Treasure - # Silver", test[i].supplyCount[silver], 40);
						result--;

						result += assertTrue("Supply - Treasure - # Gold", test[i].supplyCount[gold], 30);
						result--;

						for (n = 0; n < 10; n++) {
							if (k[n] != province && k[n] != duchy && k[n] != estate) {
								if (DEBUG_TEST) {
									printf("CARD %d - ", k[n]);
								}
								result += assertTrue("Supply - Kingdom", test[i].supplyCount[k[n]], 10);
								result--;
							}
						}

					}

					else {
						result += assertTrue("Supply - # Curse ", test[i].supplyCount[curse], 30);
						result--;

						result += assertTrue("Supply - Victory - # Estate", test[i].supplyCount[estate], 12);
						result--;

						result += assertTrue("Supply - Victory - # Duchy", test[i].supplyCount[duchy], 12);
						result--;

						result += assertTrue("Supply - Victory - # Province", test[i].supplyCount[province], 12);
						result--;

						result += assertTrue("Supply - Treasure - # Copper ", test[i].supplyCount[copper], (60 - 7 * numPlayers));
						result--;

						result += assertTrue("Supply - Treasure - # Silver", test[i].supplyCount[silver], 40);
						result--;

						result += assertTrue("Supply - Treasure - # Gold", test[i].supplyCount[gold], 30);
						result--;

						for (n = 0; n < 10; n++) {
							if (k[n] != province && k[n] != duchy && k[n] != estate) {
								if (DEBUG_TEST) {
									printf("CARD %d - ", k[n]);
								}
								result += assertTrue("Supply - Kingdom", test[i].supplyCount[k[n]], 10);
								result--;
							}
						}
					}


					// TEST: Embargo Tokens (assuming we're only using set_2)
					int supply_array[17] = { curse, estate, duchy, province, copper, silver, gold, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
					for (p = 0; p < 17; p++) {
						if (DEBUG_TEST) {
							printf("CARD %d - ", p);
						}
						result += assertTrue("Embargo Token", test[i].embargoTokens[supply_array[p]], 0);
						result--;
						
					}
						
					// Other Game State Properties
					result += assertTrue("Outpost Played", test[i].outpostPlayed, 0);
					result--;

					result += assertTrue("Outpost Turn", test[i].outpostTurn, 0);
					result--;

					result += assertTrue("Whose Turn", test[i].whoseTurn, 0);
					result--;

					result += assertTrue("Number of Actions", test[i].numActions, 1);
					result--;

					result += assertTrue("Number of Buys", test[i].numBuys, 1);
					result--;

					result += assertTrue("Coins", test[i].coins, 0);
					result--;
				}
			}
		}
	}

	// Print results of tests
	if (result == 0) {
		printf("\n\nRESULT: PASS\n"); 
	}
	else {
		printf("\n\nRESULT: FAIL\n"); 
	}

	return 0; 

}


