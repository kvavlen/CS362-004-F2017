/*****************************************************
** randomtestcard2.c
** Author: Natasha Kvavle
** Course: CS 362
** Assignment: #4
** Date: 11/5/2017
** Function Tested: mine_effect() via cardEffect()
******************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define DEBUG_TEST 1

// assert
// Parameters: message (char*) - message to print in debug statement
//			   expected (int) - expected value, or lvalue
//			   actual (int) - actual value, or rvalue 
//			   relationship (int) - toggles type of relationship; 1 =, 2 >, 3 <, 4 != 
//			   num (int) - identifying number for message (i.e. card it is referring to, player referring to)
// Returns: 1/0 aka true/false (int)
int assert(char *message, int num, int expected, int actual, int relationship) {

	// Assert Equals
	if (relationship == 1) {
		if (expected == actual) {
			return 1;

		}
		else {
			if (DEBUG_TEST) {
				printf("\n mine_effect(): FAIL - %s %d; Expected - %d; Actual - %d", message, num, expected, actual);
			}
			return 0;
		}
	}

	// Assert Greater Than 
	else if (relationship == 2) {
		if (actual >= expected) {
			return 1;

		}
		else {
			if (DEBUG_TEST) {
				printf("\n mine_effect(): FAIL - %s %d; %d >= %d is not true", message, num, actual, expected);
			}
			return 0;
		}
	}

	// Assert Less Than 
	else if (relationship == 3) {
		if (actual <= expected) {
			return 1;

		}
		else {
			if (DEBUG_TEST) {
				printf("\n mine_effect(): FAIL - %s %d; %d <= %d is not true", message, num, actual, expected);
			}
			return 0;
		}
	}

	// Assert Not Equals
	else if (relationship == 4) {
		if (expected != actual) {
			return 1;

		}
		else {
			if (DEBUG_TEST) {
				printf("\n mine_effect(): FAIL - %s %d; %d not != %d", message, num, expected, actual);
			}
			return 0;
		}
	}
	else {
		return 0; 
	}
}

// randomGenerator
// Parameters: lowerBound (int) - lower bound of range to find random number
//			   upperBound (int) - upper bound of range to find random number
// Returns:	random number (int)
int randomGenerator(int lowerBound, int upperBound) {
	return lowerBound + rand() % (upperBound - lowerBound);
}

// printGameState
// Parameters: struct gameState *rGame - game state to be printed 
// Assumes that debug test is on. 
// Returns: void -- simply prints the state of the game 
void printGameState(struct gameState *rGame) {

	int i;

	printf("Player Count: %d; ", rGame->numPlayers);
	for (i = 0; i < rGame->numPlayers; i++) {
		printf("\nPlayer %d - ", i);

		// Print Deck Count, and last (up-to) 3 cards in deck 
		printf("Deck Count: %d, ", rGame->deckCount[i]);
		if (rGame->deckCount[i] >= 3) {
			printf("Last 3 Cards in Deck (rightmost is last): %d, %d, %d; ", rGame->deck[i][rGame->deckCount[i] - 3], rGame->deck[i][rGame->deckCount[i] - 2], rGame->deck[i][rGame->deckCount[i] - 1]);
		}
		else if (rGame->deckCount[i] == 2) {
			printf("Last 2 Cards in Deck (rightmost is last): %d, %d; ", rGame->deck[i][rGame->deckCount[i] - 2], rGame->deck[i][rGame->deckCount[i] - 1]);
		}
		else if (rGame->deckCount[i] == 1) {
			printf("Last Card in Deck: %d; ", rGame->deck[i][rGame->deckCount[i] - 1]);
		}

		// Print Discard Count, and last (up-to) 3 cards in discard 
		printf("Discard Count: %d, ", rGame->discardCount[i]);
		if (rGame->discardCount[i] >= 3) {
			printf("Last 3 Cards in Discard (rightmost is last): %d, %d, %d, ", rGame->discard[i][rGame->discardCount[i] - 3], rGame->discard[i][rGame->discardCount[i] - 2], rGame->discard[i][rGame->discardCount[i] - 1]);
		}
		else if (rGame->discardCount[i] == 2) {
			printf("Last 2 Cards in Discard (rightmost is last): %d, %d; ", rGame->discard[i][rGame->discardCount[i] - 2], rGame->discard[i][rGame->discardCount[i] - 1]);
		}
		else if (rGame->discardCount[i] == 1) {
			printf("Last Card in Deck: %d; ", rGame->discard[i][rGame->discardCount[i] - 1]);
		}

		// Print Hand Count, and last (up-to) 3 cards in hand 
		printf("Hand Count: %d, ", rGame->handCount[i]);
		if (rGame->handCount[i] >= 3) {
			printf("Last 3 Cards in Hand (rightmost is last): %d, %d, %d; ", rGame->hand[i][rGame->handCount[i] - 3], rGame->hand[i][rGame->handCount[i] - 2], rGame->hand[i][rGame->handCount[i] - 1]);
		}
		else if (rGame->handCount[i] == 2) {
			printf("Last 2 Cards in Hand (rightmost is last): %d, %d; ", rGame->hand[i][rGame->handCount[i] - 2], rGame->hand[i][rGame->handCount[i] - 1]);
		}
		else if (rGame->handCount[i] == 1) {
			printf("Last Card in Hand: %d; ", rGame->hand[i][rGame->handCount[i] - 1]);
		}
	}
}

// randomizeGameState
// Parameters: struct gameState *rGame - initialized game to randomize 
// Returns: *rGame, randomized game state 

struct gameState* randomizeGameState(struct gameState *rGame) {
	int i, j; 
	int randomCard; 

	// HAND
	for (i = 0; i < rGame->numPlayers; i++) {
		for (j = 0; j < rGame->handCount[i]; j++) {							
			randomCard = randomGenerator(0, 26);							// Fill hand with supply that is not -1 
			while (rGame->supplyCount[randomCard] == -1) {
				randomCard = randomGenerator(-1, 26);
			}
			rGame->hand[i][j] = randomCard;
		}
	}
	
	// DECK
	for (i = 0; i < rGame->numPlayers; i++) {
		rGame->deckCount[i] = randomGenerator(0, MAX_DECK);				// Randomize deck count of players between 0 and MAX_DECK

		for (j = 0; j < rGame->deckCount[i]; j++) {
			randomCard = randomGenerator(0, 26);						// Fill deck with supply that is not -1 
			while (rGame->supplyCount[randomCard] == -1) {
				randomCard = randomGenerator(0, 26);
			}
			rGame->deck[i][j] = randomCard;
		}
	}

	// DISCARD
	for (i = 0; i < rGame->numPlayers; i++) {
		rGame->discardCount[i] = randomGenerator(0, MAX_DECK);			// Randomize discard count of players between 0 and MAX_DECK

		for (j = 0; j < rGame->discardCount[i]; j++) {
			randomCard = randomGenerator(0, 26);						// Fill discard with supply that is not -1 
			while (rGame->supplyCount[randomCard] == -1) {
				randomCard = randomGenerator(0, 26);
			}
			rGame->discard[i][j] = randomCard;
		}
	}

	return rGame;
}

// checkMineGameState
// Parameters: struct gameState *rGame - game state to be checked after the use of mine_effect() 
//			   struct gameState *compare - game state to compare rGame to
//			   int returnVal - value expected to be returned; tells us if this is a "happy" or "sad" path, and therefore
//								what game state is expected
//			   int treasure - treasure card current player gained by playing mine
// Returns: result - 0 if passes, -1 if fails
int checkMineGameState(struct gameState *rGame, struct gameState *compare, int returnVal, int treasure) {
	int result = 0;
	int i;

	// HAPPY PATH
	if (returnVal == 0) {
		// Check hand count is decremented (lost trashed card, mine card, gained treasure card)
		result += assert("Hand Count of Player", rGame->whoseTurn, compare->handCount[compare->whoseTurn] - 1, rGame->handCount[rGame->whoseTurn], 1) - 1; // - 1 to allow result to be 0 if passes
		
		// Check that the last added card to the hand is our treasure card
		result += assert("Last Hand Card of Player", rGame->whoseTurn, treasure, rGame->hand[rGame->whoseTurn][rGame->handCount[rGame->whoseTurn] - 1], 1) - 1;

		// Check that the discard of current player is incremented with mine card
		result += assert("Discard Count of Player", rGame->whoseTurn, compare->discardCount[rGame->whoseTurn] + 1, rGame->discardCount[rGame->whoseTurn], 1) - 1;
		result += assert("Last Card in Discard of Player", rGame->whoseTurn, mine, rGame->discard[rGame->whoseTurn][rGame->discardCount[rGame->whoseTurn] - 1], 1) - 1; 

		for (i = 0; i < 26; i++) {
			if (i == treasure) {
				// Check that treasure card supply decremented
				result += assert("Supply Count for Treasure Card", i, compare->supplyCount[i] - 1, rGame->supplyCount[i], 1) - 1;
			}
			else {
				// Check that supply counts are not affected (even those not in game)
				result += assert("Supply Count for Card", i, compare->supplyCount[i], rGame->supplyCount[i], 1) - 1;			

			}
		}

		for (i = 0; i < rGame->numPlayers; i++) {
			// Check that all player's decks not affected;
			result += assert("Deck Count of Player", i, compare->deckCount[i], rGame->deckCount[i], 1) - 1;
			
			// Check that non-current player's hand/discard count not affected
			if (i != rGame->whoseTurn) {
				result += assert("Discard Count of Player", i, compare->discardCount[i], rGame->discardCount[i], 1) - 1;
				result += assert("Hand Count of Player", i, compare->handCount[i], rGame->handCount[i], 1) - 1;
			}
		}
		if (DEBUG_TEST) {
			printf("\nHappy Path");
		}
	}

	// SAD PATH
	else if (returnVal == -1) {
		// Check that supply counts are not affected - even those not used in game
		for (i = 0; i < 26; i++) {
			result += assert("Supply Count for Card", i, compare->supplyCount[i], rGame->supplyCount[i], 1) - 1;		
		}

		for (i = 0; i < rGame->numPlayers; i++) {
			// Check that all player's deck/discards not affected;
			result += assert("Deck Count of Player", i, compare->deckCount[i], rGame->deckCount[i], 1) - 1;
			result += assert("Discard Count of Player", i, compare->discardCount[i], rGame->discardCount[i], 1) - 1;
			result += assert("Hand Count of Player", i, compare->handCount[i], rGame->handCount[i], 1) - 1;
		}
		if (DEBUG_TEST) {
			printf("\nSad Path");
		}
	}

	return result; 
}

int main() {

	// Initialize values as needed for cardEffect function call and initializeGame() function
	int i;
	int result = 0; 
	int choice1, choice2, minePos, numPlayers, returnVal; 
	int choice3 = 0;
	int bonus = 0;
	int kingdomCards[10] = { 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	int seed; 

	// Seed rand
	int testSeed = time(NULL);
	srand(testSeed);

	// Title 
	printf("\n \n RANDOM TEST CARD 2: MINE_EFFECT()"); 

	for (i = 0; i < 5000; i++) {

		// Define values as needed for cardEffect & mine_effect() function call 
		choice2 = randomGenerator(-1, 27);												// Randomly choose card to buy -- even if has an empty supply or card is invalid 							
		seed = randomGenerator(1, 100);

		// Create randomized game state for use in smithy_effect/cardEffect
		struct gameState rGame; 

		// Randomize the appropriate input for initializeGame
		numPlayers = randomGenerator(2, 4);
	
		// Initialize game, than randomize game state based on initialized state
		initializeGame(numPlayers, kingdomCards, seed, &rGame); 
		randomizeGameState(&rGame);

		choice1 = randomGenerator(0, 4);												// Randomly choose position of card to trash
		do {
			minePos = randomGenerator(0, 4);											// Randomly choose position of mine card in hand, cannot be position of trash card
		} while (minePos == choice1);
		rGame.hand[rGame.whoseTurn][minePos] = mine;									// Override minePos position in current player's hand with mine

		// Copy randomized game state to another variable for comparison
		struct gameState compare;
		memcpy(&compare, &rGame, sizeof(struct gameState));

		// Print inputs that matter
		if (DEBUG_TEST) {
			printf("\n\n TEST CASE #%d: ", i); 
			printf("Seed for Random() = %d; Seed for initializeGame = %d; ", testSeed, seed);
			printf("Mine Position in Current Player's Hand = %d; ", minePos);
			printf("Choice 1 / Trash Card Position in Current Player's Hand = %d; ", choice1);
			printf("Choice 1 Card = %d; ", rGame.hand[rGame.whoseTurn][choice1]);
			printf("Choice 2 / Treasure Card = %d; ", choice2);
			printGameState(&rGame);
		}

		// Play mine card, check that return value is 0 if trashed card == treasure card, or if trashed card is only 3 coins or less vlaue than treasure card
		if ((rGame.hand[rGame.whoseTurn][choice1] == copper && choice2 == silver) || (rGame.hand[rGame.whoseTurn][choice1] == silver && choice2 == gold) || (rGame.hand[rGame.whoseTurn][choice1] == copper && choice2 == copper) || (rGame.hand[rGame.whoseTurn][choice1] == silver && choice2 == silver) || (rGame.hand[rGame.whoseTurn][choice1] == gold && choice2 == gold)) {
			result += assert("Return Value", 0, 0, cardEffect(mine, choice1, choice2, choice3, &rGame, minePos, &bonus), 1) - 1; // + 0 for pass, -1 for fail
			returnVal = 0;	// Record appropriate return val for better checking of game state 
		}
		// If invalid pair of trash/treasure cards, then return -1
		else {
			result += assert("Return Value", -1, -1, cardEffect(mine, choice1, choice2, choice3, &rGame, minePos, &bonus), 1) - 1; 
			returnVal = -1; 
		}

		// Check game state afterward to see if test passes
		result += checkMineGameState(&rGame, &compare, returnVal, choice2) - 1; // + 0 for pass, -1 for fail 
	}

	// Print results
	if (result == 0) {
		printf("\n \n RESULT: TESTS PASSED \n");
	}
	else {
		printf("\n \n RESULT: TEST(S) FAILED \n");			
	}

	return 0; 
}
