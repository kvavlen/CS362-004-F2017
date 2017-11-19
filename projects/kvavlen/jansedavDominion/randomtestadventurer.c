/*****************************************************
** randomtestadventurer.c
** Author: Natasha Kvavle
** Course: CS 362
** Assignment: #4
** Date: 11/5/2017
** Function Tested: adventurer_effect() via cardEffect()
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
//			   relationship (int) - toggles type of relationship; 1 =, 2 >=, 3 <=, 4 != 
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
				printf("\n adventurer_effect(): FAIL - %s %d; Expected - %d; Actual - %d", message, num, expected, actual);
			}
			return 0;
		}
	}

	// Assert Greater Than 
	else if (relationship == 2) {
		if (actual >= expected) {
			//if (DEBUG_TEST) {
			//	printf("\n smithy_effect(): PASS - %s; %d > %d", message, expected, actual);
			//}
			return 1;

		}
		else {
			if (DEBUG_TEST) {
				printf("\n adventurer_effect(): FAIL - %s %d; %d >= %d is not true", message, num, actual, expected);
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
				printf("\n adventurer_effect(): FAIL - %s %d; %d <= %d is not true", message, num, actual, expected);
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
				printf("\n adventurer_effect(): FAIL - %s %d; %d not != %d", message, num, expected, actual);
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
			randomCard = randomGenerator(0, 26);						// Fill hand of players with supply that is not -1 
			while (rGame->supplyCount[randomCard] == -1) {
				randomCard = randomGenerator(0, 26);
			}
			rGame->hand[i][j] = randomCard;
		}
	}

	// DECK
	for (i = 0; i < rGame->numPlayers; i++) {

		rGame->deckCount[i] = randomGenerator(0, MAX_DECK);				// Randomize deck count between 0 and MAX_DECK for all players

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
		rGame->discardCount[i] = randomGenerator(0, MAX_DECK);			// Randomize discard count between 0 and MAX_DECK for all players

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

// checkAdventurerGameState
// Parameters: struct gameState *rGame - game state to be checked after the use of adventurer_effect() 
//			   struct gameState *compare - game state to compare rGame to
// Returns: result - 0 if passes, -1 if fails
int checkAdventurerGameState(struct gameState *rGame, struct gameState *compare) {
	int result = 0;
	int i;

	// Check hand count is incremented by 1 (gained 2 treasure card, lost adventurer card)
	result += assert("Hand Count of Player", rGame->whoseTurn, compare->handCount[compare->whoseTurn] + 1, rGame->handCount[rGame->whoseTurn], 1) - 1; // - 1 to allow result to be 0 if passes
	
	// Check that the last 2 added cards to the hand are treasure cards
	result += assert("Last Hand Card >= Copper for Player", rGame->whoseTurn, copper, rGame->hand[rGame->whoseTurn][rGame->handCount[rGame->whoseTurn] - 1], 2) - 1;
	result += assert("Second to Last Hand Card >= Copper for Player", rGame->whoseTurn, copper, rGame->hand[rGame->whoseTurn][rGame->handCount[rGame->whoseTurn] - 2], 2) - 1;
	
	result += assert("Last Hand Card <= Gold for Player", rGame->whoseTurn, gold, rGame->hand[rGame->whoseTurn][rGame->handCount[rGame->whoseTurn] - 1], 3) - 1;
	result += assert("Second to Last Hand Card <= Gold for Player", rGame->whoseTurn, gold, rGame->hand[rGame->whoseTurn][rGame->handCount[rGame->whoseTurn] - 2], 3) - 1;

	// Check that the number of cards taken from deck matches the (number of cards added to discard - 1 [for adventurer]) + number of cards added to hand 
	result += assert("Cards taken from Deck = (Cards added to Discard - 1) + (Cards added to Hand) for Player", rGame->whoseTurn, (compare->deckCount[compare->whoseTurn] - rGame->deckCount[rGame->whoseTurn]), ((rGame->discardCount[rGame->whoseTurn] - compare->discardCount[compare->whoseTurn] - 1) + (rGame->handCount[rGame->whoseTurn] - compare->handCount[compare->whoseTurn])), 1) - 1;

	// Check discard of current player increases by 1 for adventurer
	result += assert("Discard Count of Player", rGame->whoseTurn, compare->discardCount[compare->whoseTurn] + 1, rGame->discardCount[rGame->whoseTurn], 1) - 1;

	for (i = 0; i < 26; i++) {
		// Check that supply counts are not affected (even those not used in game)
		result += assert("Supply Count for Card", i, compare->supplyCount[i], rGame->supplyCount[i], 1) - 1;			
	}

	for (i = 0; i < rGame->numPlayers; i++) {
		// Check that non-current players' hand / deck / discard count not affected
		if (i != rGame->whoseTurn) {
			result += assert("Deck Count of Player", i, compare->deckCount[i], rGame->deckCount[i], 1) - 1;
			result += assert("Discard Count of Player", i, compare->discardCount[i], rGame->discardCount[i], 1) - 1;
			result += assert("Hand Count of Player", i, compare->handCount[i], rGame->handCount[i], 1) - 1;
		}
	}

	return result;
}

int main() {

	// Declare values as needed for cardEffect function call and initializeGame function
	int i;
	int result = 0;
	int choice1, choice2, choice3, adventurerPos, bonus, numPlayers;
	int kingdomCards[10] = { 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	int seed;

	int testSeed = time(NULL);
	srand(testSeed);

	// Title 
	printf("\n \n RANDOM TEST CARD: ADVENTURER_EFFECT()");

	for (i = 0; i < 1000; i++) {
		// Define values as needed for cardEffect function call 							
		choice1 = 0;																	
		choice2 = 0;
		choice3 = 0;
		bonus = 0;
		seed = randomGenerator(1, 100);

		// Create randomized game state for use in smithy_effect/cardEffect
		struct gameState rGame;

		// Randomize the appropriate input for initializeGame
		numPlayers = randomGenerator(2, 4);

		// Initialize game, than randomize game state based on initialized state
		initializeGame(numPlayers, kingdomCards, seed, &rGame);
		randomizeGameState(&rGame);
		adventurerPos = randomGenerator(0, 5);								// Randomly choose position of adventurer card in hand, cannot be position of trash card
		rGame.hand[rGame.whoseTurn][adventurerPos] = adventurer;

		// Copy randomized game state to another variable for comparison
		struct gameState compare;
		memcpy(&compare, &rGame, sizeof(struct gameState));
																								
		// Print inputs that matter
		if (DEBUG_TEST) {
			printf("\n\n TEST CASE #%d: ", i);
			printf("Seed for Random() = %d; Seed for initializeGame = %d; ", testSeed, seed);
			printf("Adventurer Position in Current Player's Hand = %d; ", adventurerPos);
			printGameState(&rGame);
		}

		// Play adventurer card & check return value is 0
		result += assert("Return Value", 0, 0, cardEffect(adventurer, choice1, choice2, choice3, &rGame, adventurerPos, &bonus), 1) - 1; // + 0 for pass, -1 for fail

		// Check game state afterward to see if test passes
		result += checkAdventurerGameState(&rGame, &compare) - 1; // + 0 for pass, -1 for fail 
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


