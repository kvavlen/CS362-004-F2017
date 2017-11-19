/* ******************************************************************************
Program: cardtest4.c
Author: Natasha Kvavle
Function Tested: remodel_effect()
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
			printf("cardEffect() / remodel_effect(): Pass - %s: Expected %d, Actual %d\n", details, value2, value1);
		}
		return 1;
	}
	else {
		if (DEBUG_TEST) {
			printf("cardEffect() / remodel_effect(): Fail - %s: Expected %d, Actual %d		************\n", details, value2, value1);
		}
		return 0;
	}
}

// checkGameState
//	Checks supply count of all cards, players' deck, hand, and discard count to ensure appropriate changes in game state
//  Returns result -- 0 if all tests pass
int checkGameState(int numPlayers, int player, int cardNum, struct gameState *compare, struct gameState *test) {

	int result = 0;
	int j;
	int i; 

	for (i = 0; i < 27; i++) {

		if (i != cardNum) {
			if (DEBUG_TEST) {
				printf("Supply Card %d - ", i);
			}

			result += assertTrue("Supply Count", test->supplyCount[i], compare->supplyCount[i]); // supply count not affected
			result--;
		}
		else {
			if (DEBUG_TEST) {
				printf("Supply Card %d -", i);
			}
			result += assertTrue("Supply Count of Treasure Card", test->supplyCount[cardNum], compare->supplyCount[cardNum] - 1); // supply count was decremented
			result--;
		}


	}

	if (DEBUG_TEST) {
		printf("Starting Player %d -", player);
	}

	result += assertTrue("Deck Count", test->deckCount[player], compare->deckCount[player]); // deck count stays the same
	result--;

	if (DEBUG_TEST) {
		printf("Starting Player %d -", player);
	}

	result += assertTrue("Hand Count", test->handCount[player], compare->handCount[player] - 2); // hand count decreases by 2 (lose remodel card, lose a trashed card)
	result--;

	if (DEBUG_TEST) {
		printf("Starting Player %d -", player);
	}

	result += assertTrue("Discard Count", test->discardCount[player], compare->discardCount[player] + 2); // discard count increases by 2 (Get remodel card, and treasure card)
	result--;

	for (j = 0; j < numPlayers; j++) {

		if (j != player) {
			if (DEBUG_TEST) {
				printf("Other Player %d - ", j);
			}
			result += assertTrue("Deck Count", test->deckCount[j], compare->deckCount[j]); // deck count of other player not affected
			result--;

			if (DEBUG_TEST) {
				printf("Other Player %d - ", j);
			}

			result += assertTrue("Discard Count", test->discardCount[j], compare->discardCount[j]); // discard count stays the same 
			result--;

			if (DEBUG_TEST) {
				printf("Other Player %d - ", j);
			}

			result += assertTrue("Hand Count", test->handCount[j], compare->handCount[j]); // hand count stays the same
			result--;
		}

	}

	return result;
}

// checkGameState
//	Checks supply count of all cards, players' deck, hand, and discard count to ensure no changes in game state
//  Returns result -- 0 if all tests pass
int checkSadGameState(int numPlayers, int player, int cardNum, struct gameState *compare, struct gameState *test) {

	int result = 0;
	int j;
	int i;


	for (i = 0; i < 27; i++) {

		if (i != cardNum) {
			if (DEBUG_TEST) {
				printf("Supply Card %d - ", i);
			}

			result += assertTrue("Supply Count", test->supplyCount[i], compare->supplyCount[i]); // supply count not affected
			result--;
		}
		else {
			if (DEBUG_TEST) {
				printf("Supply Card %d -", i);
			}
			result += assertTrue("Supply Count of Treasure Card", test->supplyCount[cardNum], compare->supplyCount[cardNum]); // supply count was not decremented
			result--;
		}


	}

	if (DEBUG_TEST) {
		printf("Starting Player %d -", player);
	}

	result += assertTrue("Deck Count", test->deckCount[player], compare->deckCount[player]); // deck count stays the same
	result--;

	if (DEBUG_TEST) {
		printf("Starting Player %d -", player);
	}


	result += assertTrue("Hand Count", test->handCount[player], compare->handCount[player]);	// Hand count should not change if we're exiting out with -1
	result--;

	if (DEBUG_TEST) {
		printf("Starting Player %d -", player);
	}

	result += assertTrue("Discard Count", test->discardCount[player], compare->discardCount[player]); // Discard count should not change if we're exiting out with -1
	result--;

	for (j = 0; j < numPlayers; j++) {

		if (j != player) {
			if (DEBUG_TEST) {
				printf("Other Player %d - ", j);
			}
			result += assertTrue("Deck Count", test->deckCount[j], compare->deckCount[j]); // deck count of other player not affected
			result--;

			if (DEBUG_TEST) {
				printf("Other Player %d - ", j);
			}

			result += assertTrue("Discard Count", test->discardCount[j], compare->discardCount[j]); // discard count stays the same 
			result--;

			if (DEBUG_TEST) {
				printf("Other Player %d - ", j);
			}

			result += assertTrue("Hand Count", test->handCount[j], compare->handCount[j]); // hand count stays the same
			result--;
		}

	}

	return result;
}

int main() {


	if (DEBUG_TEST) {
		printf("\n\n>>>>>>> CARDTEST 4: REMODEL_EFFECT() <<<<<<<<\n\n");
	}

	// Keep track of how many tests are passing of those attempted
	int result = 0;  // if result is non0 then we fail

	// Initialize values 
	struct gameState test2, test3, test4, test5, test6, compare;
	int seed = 100;
	int k[10] = { adventurer, smithy, remodel, feast, mine, sea_hag, tribute, treasure_map, council_room, village };	// randomly chosen, only real importance is that it contains our adventurer card																												
	
	// Input for numPlayers
	int minPlayers = 2;
	int maxPlayers = 4; // based on fact that MAX_PLAYERS = 4
	
	// Input for handPos
	int handPos[2] = { 0, 4 };
	int remodelPos;

	// Input for choice 1 - card to trash 
	int choice1[2] = { 4, 0 }; // positions in hand 
	int trashPosition;

	// Input for choice 2 - treasure card no more than 3 coin greater than card trashed
	int choice2;

	// Input required for cardEffect, but not our function -- included so that the function can be called via cardEffect 
	//		and therefore implemented as a switch statement or separate function
	int choice3 = 0;
	int bonus = 0;

	// Iterators 
	int i, n;

	// Test each possible number of players		
	for (i = minPlayers; i < maxPlayers; i++) {
		if (DEBUG_TEST) {
			printf("TEST - %d PLAYERS\n\n", i);
		}

		// Run with both position sets of mine/trashcard
		for (n = 0; n < 2; n++) {

			// player 0 goes first based on initialize Game state
			trashPosition = choice1[n];
			remodelPos = handPos[n];
			test2.hand[0][remodelPos] = remodel;

			// SETUP: Happy Path - HandPos of Mine: MIN, HandPos of TrashCard = MAX, TrashCard = Smithy, Choice2 = Silver
			if (DEBUG_TEST) {
				printf("\n\nHAPPY PATH - Trash Smithy, Gain Gold - HandPos of Remodel: %d, HandPos of Trashcard: %d, Trash Card: %d, Treasure Card/Choice 2: %d\n\n", remodelPos, trashPosition, smithy, gold);
			}
			initializeGame(i, k, seed, &test2);
			test2.hand[0][trashPosition] = smithy;
			choice2 = gold;
			memcpy(&compare, &test2, sizeof(struct gameState));

			// Test return value 
			result += assertTrue("Return Value", cardEffect(remodel, trashPosition, choice2, choice3, &test2, remodelPos, &bonus), 0);
			result--;

			result += checkGameState(i, 0, choice2, &compare, &test2);


			// SETUP: Happy Path - HandPos of Mine: MIN, HandPos of TrashCard = MAX, TrashCard = Estate, Choice2 = Silver
			if (DEBUG_TEST) {
				printf("\n\nHAPPY PATH - Trash Estate, Gain Silver - HandPos of Remodel: %d, HandPos of Trashcard: %d, Trash Card: %d, Treasure Card/Choice 2: %d\n\n", remodelPos, trashPosition, estate, silver);
			}

			initializeGame(i, k, seed, &test3);
			test3.hand[0][trashPosition] = estate;
			choice2 = silver;
			memcpy(&compare, &test3, sizeof(struct gameState));

			// Test return value 
			result += assertTrue("Return Value", cardEffect(remodel, trashPosition, choice2, choice3, &test3, remodelPos, &bonus), 0);
			result--;

			result += checkGameState(i, 0, choice2, &compare, &test3);


			// SETUP: Sad Path - HandPos of Mine: MIN, HandPos of TrashCard = MAX, TrashCard = estate, Choice2 = gold
			if (DEBUG_TEST) {
				printf("\n\nSAD PATH - TREASURE TOO EXPENSIVE - HandPos of Remodel: %d, HandPos of Trashcard: %d, Trash Card: %d, Treasure Card/Choice 2: %d\n\n", remodelPos, trashPosition, estate, gold);
			}

			initializeGame(i, k, seed, &test4);
			test4.hand[0][trashPosition] = estate;
			choice2 = gold;
			memcpy(&compare, &test4, sizeof(struct gameState));

			// Test return value 
			result += assertTrue("Return Value", cardEffect(remodel, trashPosition, choice2, choice3, &test4, remodelPos, &bonus), -1);
			result--;

			result += checkSadGameState(i, 0, choice2, &compare, &test4);


			// SETUP: Sad Path - HandPos of Mine: MIN, HandPos of TrashCard = MAX, TrashCard = -1, Choice2 = gold
			if (DEBUG_TEST) {
				printf("\n\nSAD PATH - TRASH CARD INVALID - HandPos of Remodel: %d, HandPos of Trashcard: %d, Trash Card: %d, Treasure Card/Choice 2: %d\n\n", remodelPos, trashPosition, -1, gold);
			}
			initializeGame(i, k, seed, &test5);
			test5.hand[0][trashPosition] = -1;
			choice2 = gold;
			memcpy(&compare, &test5, sizeof(struct gameState));

			// Test return value 
			result += assertTrue("Return Value", cardEffect(remodel, trashPosition, choice2, choice3, &test5, remodelPos, &bonus), -1);
			result--;

			result += checkSadGameState(i, 0, choice2, &compare, &test5);


			// SETUP: Sad Path - HandPos of Mine: MIN, HandPos of TrashCard = MAX, TrashCard = -1, Choice2 = gold
			if (DEBUG_TEST) {
				printf("\n\nSAD PATH - TREASURE CARD INVALID - HandPos of Remodel: %d, HandPos of Trashcard: %d, Trash Card: %d, Treasure Card/Choice 2: %d\n\n", remodelPos, trashPosition, adventurer, smithy);
			}

			initializeGame(i, k, seed, &test6);
			test6.hand[0][trashPosition] = estate;
			choice2 = gold;
			memcpy(&compare, &test6, sizeof(struct gameState));

			// Test return value 
			result += assertTrue("Return Value", cardEffect(remodel, trashPosition, choice2, choice3, &test6, remodelPos, &bonus), -1);
			result--;

			result += checkSadGameState(i, 0, choice2, &compare, &test6);
		}
	}

	if (result == 0) {
		printf("\n\nRESULT: ALL TESTS PASS\n");
	}
	else {
		printf("\n\nRESULT: FAIL\n");
	}

	return 0; 
}