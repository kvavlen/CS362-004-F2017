/* ******************************************************************************
Program: unittest3.c
Author: Natasha Kvavle
Function Tested: gainCard()
Course: CS 362
Assignment: 3
Date: 10/22/2017
Reference: Located in Assignment-3.pdf (Canvas submission)
using testUpdateCoins for how to properly use memcpy 
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
			printf("gainCard(): Pass - %s: Expected %d, Actual %d\n", details, value2, value1);
		}
		return 1;
	}
	else {
		if (DEBUG_TEST) {
			printf("gainCard(): Fail - %s: Expected %d, Actual %d		************\n", details, value2, value1);
		}
		return 0;
	}
}

// checkGameState
//	Checks players' deck, hand, and discard piles to ensure appropriate changes in game state
//  Returns result -- 0 if all tests pass
int checkGameState(struct gameState *test, struct gameState *compare, int cardNum, int player, int numPlayers, int toFlag) {

	int result = 0; 
	int j;

	if (toFlag == 1) {
		if (DEBUG_TEST) {
			printf("Player %d -", player);
		}
		result += assertTrue("Deck Count", test->deckCount[player], compare->deckCount[player] + 1); // deck count incremented
		result--;
		if (DEBUG_TEST) {
			printf("Player %d -", player);
		}
		result += assertTrue("Last Card in Deck", test->deck[player][test->deckCount[player] - 1], cardNum); // the card is in appropriate spot in deck 
		result--;
	}
	else {
		if (DEBUG_TEST) {
			printf("Player %d -", player);
		}
		result += assertTrue("Deck Count", test->deckCount[player], compare->deckCount[player]); // deck count stays the same
		result--;
	}

	if (toFlag == 2) {
		if (DEBUG_TEST) {
			printf("Player %d -", player);
		}
		result += assertTrue("Hand Count", test->handCount[player], compare->handCount[player] + 1); // hand count increases
		result--;
		
		if (DEBUG_TEST) {
			printf("Player %d -", player);
		}
		result += assertTrue("Last Card in Hand", test->hand[player][test->handCount[player] - 1], cardNum); // the card is in appropriate spot in hand
		result--;
	}
	else {
		if (DEBUG_TEST) {
			printf("Player %d -", player);
		}
		result += assertTrue("Hand Count", test->handCount[player], compare->handCount[player]); // hand count stays the same
		result--;
	}
	
	if (toFlag == 0) {
		if (DEBUG_TEST) {
			printf("Player %d -", player);
		}
		result += assertTrue("Discard Count", test->discardCount[player], compare->discardCount[player] + 1); // discard count incremented
		result--;
		if (DEBUG_TEST) {
			printf("Player %d -", player);
		}
		result += assertTrue("Last Card in Discard", test->discard[player][test->discardCount[player] - 1], cardNum); // the card is in appropriate spot in discard 
		result--;
	}
	else {
		if (DEBUG_TEST) {
			printf("Player %d -", player);
		}
		result += assertTrue("Discard Count", test->discardCount[player], compare->discardCount[player]); // discard count stays the same 
		result--;
	}


	result += assertTrue("Supply Count of Card Gained", test->supplyCount[cardNum], compare->supplyCount[cardNum] - 1); // supply count was decremented
	result--;


	for (j = 0; j < numPlayers; j++) {

		if (j != player) {
			if (DEBUG_TEST) {
				printf("Other Player %d -", j);
			}
			result += assertTrue("Deck Count", test->deckCount[j], compare->deckCount[j]); // deck count of other player not affected
			result--;
			if (DEBUG_TEST) {
				printf("Other Player %d -", j);
			}
			result += assertTrue("Discard Count", test->discardCount[j], compare->discardCount[j]); // discard count stays the same 
			result--;
			if (DEBUG_TEST) {
				printf("Other Player %d -", j);
			}
			result += assertTrue("Hand Count", test->handCount[j], compare->handCount[j]); // hand count stays the same
			result--;
		}

	}

	return result; 
}

int main() {


	if (DEBUG_TEST) {
		printf("\n\n>>>>>>> UNIT TEST 3: GAINCARD() <<<<<<<<\n\n");
	}

	int result = 0; 

	// Make an array of test games/states
	struct gameState test1, test2, test3, test4, test5, test6; 
	struct gameState compare; 
	int toFlag; // 0, 1, 2 
	int seed = 100;
	int minPlayer = 2; // don't want initializeGame to fail -- min/max for OK gameplay
	int maxPlayer = 4;
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room }; // Based on Kingdom Cards from cardtest4.c
	int i, j; //for loop declarations

	printf("\n\nTEST SET: Chosen supply not used in game \n\n"); 
	initializeGame(minPlayer, k, seed, &test1);
	initializeGame(maxPlayer, k, seed, &test2);

	// for each player in min test
	for (j = 0; j < minPlayer; j++) {
		if (DEBUG_TEST) {
			printf("\nTest - Min (2) players in game, testing with player %d, Card %d\n\n", j, feast);
		}
		result += assertTrue("Return Value", gainCard(feast, &test1, 0, j),  -1);
		result--;
	}

	// for each player in max test
	for (j = 0; j < maxPlayer; j++) {
		if (DEBUG_TEST) {
			printf("\nTest - Max (4) players in game, testing with player %d, Card %d\n\n", j, feast);
		}
		result += assertTrue("Return Value", gainCard(feast, &test2, 0, j), -1);
		result--;
	}

	printf("TEST SET: Chosen supply is empty \n");
	initializeGame(minPlayer, k, seed, &test1);
	initializeGame(maxPlayer, k, seed, &test2);

	test1.supplyCount[embargo] = 0; 
	test2.supplyCount[embargo] = 0; 

	// for each player in min test
	for (j = 0; j < minPlayer; j++) {
		if (DEBUG_TEST) {
			printf("\nTest - Min (2) players in game, testing with player %d, Card %d\n\n", j, embargo);
		}
		result += assertTrue("Return Value", gainCard(embargo, &test1, 0, j), -1);
		result--;
	}

	// for each player in max test
	for (j = 0; j < maxPlayer; j++) {
		if (DEBUG_TEST) {
			printf("\nTest - Max (4) players in game, testing with player %d, Card %d\n\n", j, embargo);
		}
		result += assertTrue("Return Value", gainCard(embargo, &test2, 0, j), -1);
		result--;
	}

	printf("\n\nTEST SET: Chosen supply is used in game & not empty \n");
	printf("\n>> Adding supply card to deck\n\n");
	toFlag = 1;

	// For all cards available(at the moment)
	int card[17] = { curse, estate, duchy, province, copper, silver, gold, adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room };
	for (i = 0; i < 17; i++) {

		// for each player in min test
		for (j = 0; j < minPlayer; j++) {
			if (DEBUG_TEST) {
				printf("\nTest: Min (2) players in game, testing with Player %d, adding Card %d to deck \n\n", j, card[i]); 
			}
			initializeGame(minPlayer, k, seed, &test1);
			memcpy(&compare, &test1, sizeof(struct gameState));  // copy current state of the game

			result += assertTrue("Return Value", gainCard(card[i], &test1, toFlag, j), 0);
			result--;

			result += checkGameState(&test1, &compare, card[i], j, minPlayer, toFlag); 

		}

		// for each player in max test
		for (j = 0; j < maxPlayer; j++) {
			initializeGame(maxPlayer, k, seed, &test2);
			if (DEBUG_TEST) {
				printf("\nTest: Max (4) players in game, testing with Player %d, adding Card %d to deck \n\n", j, card[i]);
			}

			initializeGame(minPlayer, k, seed, &test2);
			memcpy(&compare, &test2, sizeof(struct gameState));  // copy current state of the game

			result += assertTrue("Return Value", gainCard(card[i], &test2, toFlag, j), 0);
			result--;

			result += checkGameState(&test2, &compare, card[i], j, maxPlayer, toFlag);

		}
	}

	printf("\n\n>> Adding supply card to hand\n\n");
	toFlag = 2;

	// For all cards available(at the moment)
	for (i = 0; i < 17; i++) {

		// for each player in min test
		for (j = 0; j < minPlayer; j++) {
			if (DEBUG_TEST) {
				printf("\nTest: Min (2) players in game, testing with player %d, adding Card %d to hand \n\n", j, card[i]);
			}
			initializeGame(minPlayer, k, seed, &test3);			// Initialize game, start from scratch 
			memcpy(&compare, &test3, sizeof(struct gameState));  // copy current state of the game

			result += assertTrue("Return Value", gainCard(card[i], &test3, toFlag, j), 0);
			result--;

			result += checkGameState(&test3, &compare, card[i], j, minPlayer, toFlag);
		}

		// for each player in min test
		for (j = 0; j < maxPlayer; j++) {
			if (DEBUG_TEST) {
				printf("\nTest: Max (4) players in game, testing with player %d, adding Card %d to hand \n\n", j, card[i]);
			}

			initializeGame(maxPlayer, k, seed, &test4);			// Initialize game, start from scratch 
			memcpy(&compare, &test4, sizeof(struct gameState));  // copy current state of the game

			result += assertTrue("Return Value", gainCard(card[i], &test4, toFlag, j), 0);
			result--;

			result += checkGameState(&test4, &compare, card[i], j, maxPlayer, toFlag);
		}
	}

	printf("\n\n>> Adding supply card to discard pile\n\n");
	toFlag = 0; 

	// For all cards available(at the moment)
	for (i = 0; i < 17; i++) {

		// for each player in min test
		for (j = 0; j < minPlayer; j++) {
			if (DEBUG_TEST) {
				printf("\nTest: Min (2) players in game, testing with player %d, adding Card %d to discard \n", j, card[i]);
			}
			initializeGame(minPlayer, k, seed, &test5);			// Initialize game, start from scratch 
			memcpy(&compare, &test5, sizeof(struct gameState));  // copy current state of the game


			result += assertTrue("Return Value", gainCard(card[i], &test5, toFlag, j), 0);
			result--;

			result += checkGameState(&test5, &compare, card[i], j, minPlayer, toFlag);
		}

		// for each player in max test
		for (j = 0; j < maxPlayer; j++) {
			if (DEBUG_TEST) {
				printf("\nTest: Max (4) players in game, testing with player %d, adding Card %d to discard \n", j, card[i]);
			}
			initializeGame(maxPlayer, k, seed, &test6);			// Initialize game, start from scratch 
			memcpy(&compare, &test6, sizeof(struct gameState));  // copy current state of the game


			result += assertTrue("Return Value", gainCard(card[i], &test6, toFlag, j), 0);
			result--;

			result += checkGameState(&test6, &compare, card[i], j, maxPlayer, toFlag);
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


