/* ******************************************************************************
Program: cardtest3.c
Author: Natasha Kvavle
Function Tested: mine_effect() via cardEffect() 
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
			printf("cardEffect() / mine_effect(): Pass - %s: Expected %d, Actual %d\n", details, value2, value1);
		}
		return 1;
	}
	else {
		if (DEBUG_TEST) {
			printf("cardEffect() / mine_effect(): Fail - %s: Expected %d, Actual %d		************\n", details, value2, value1);
		}
		return 0;
	}
}

// checkSadGameState
//	Checks supply count of treasure card, players' deck, hand, and discard count to ensure no changes in game state
//  Returns result -- 0 if all tests pass
int checkSadGameState(int numPlayers, int player, int treasure, struct gameState *compare, struct gameState *test) {
	int m, i;
	int result = 0; 

	for (i = 0; i < 27; i++) {

		if (i != treasure) {
			if (DEBUG_TEST) {
				printf("SUPPLY CARD %d - ", i);
			}

			result += assertTrue("Supply Count", test->supplyCount[i], compare->supplyCount[i]); // supply count not affected
			result--;
		}
		else {
			if (DEBUG_TEST) {
				printf("TREASURE CARD %d -", i);
			}
			result += assertTrue("Supply Count of TREASURE CARD", test->supplyCount[treasure], compare->supplyCount[treasure]); // supply count not affected
			result--;
		}
	}

	if (DEBUG_TEST) {
		printf("PLAYER %d - ", player);
	}

	// Test that this player's hand count didn't change (returned before got here)
	result += assertTrue("Hand Count", test->handCount[player], compare->handCount[player]);
	result--;

	if (DEBUG_TEST) {
		printf("PLAYER %d - ", player);
	}

	// Test the player's deck count remains the same (returned before got here)
	result += assertTrue("Deck Count", test->deckCount[player], compare->deckCount[player]);
	result--;

	if (DEBUG_TEST) {
		printf("PLAYER %d - ", player);
	}

	// Test that the player's discard count remains the same (returned before got here)
	result += assertTrue("Discard Count", test->discardCount[player], compare->discardCount[player]);
	result--;

	// Other player's game state stays the same 
	for (m = 0; m < numPlayers; m++) {

		// Don't perform for our current player
		if (m != player) {
			if (DEBUG_TEST) {
				printf("OTHER PLAYER %d - ", m); 
			}
			// HAND COUNT
			result += assertTrue("Hand Count", test->handCount[m], compare->handCount[m]);
			result--;

			if (DEBUG_TEST) {
				printf("OTHER PLAYER %d - ", m);
			}

			// DECK 
			result += assertTrue("Deck Count", test->deckCount[m], compare->deckCount[m]);
			result--;

			if (DEBUG_TEST) {
				printf("OTHER PLAYER %d - ", m);
			}

			// DISCARD COUNT
			result += assertTrue("Discard Count", test->discardCount[m], compare->discardCount[m]);
			result--;
		}
	}

	if (DEBUG_TEST) {
		printf("\n\n");
	}

	return result; 
}

// checkHappyGameState
//	Checks supply count of treasure card, players' deck, hand, and discard piles to ensure appropriate changes in game state based on card's effect
//  Returns result -- 0 if all tests pass
int checkHappyGameState(int numPlayers, int player, int treasure, struct gameState *compare, struct gameState *test) {
	int m, i;
	int result = 0;

	for (i = 0; i < 27; i++) {

		if (i != treasure) {
			if (DEBUG_TEST) {
				printf("SUPPLY CARD %d - ", i);
			}

			result += assertTrue("Supply Count", test->supplyCount[i], compare->supplyCount[i]); // supply count not affected
			result--;
		}
		else {
			if (DEBUG_TEST) {
				printf("TREASURE CARD %d -", i);
			}
			result += assertTrue("Supply Count of TREASURE CARD", test->supplyCount[treasure], compare->supplyCount[treasure] - 1); // supply count was decremented
			result--;
		}
	}

	if (DEBUG_TEST) {
		printf("TREASURE CARD %d - ", treasure);
	}
	// Test supply count for treasure card to be retrieved decremented 
	result += assertTrue("Supply Count", test->supplyCount[treasure], compare->supplyCount[treasure] - 1);
	result--;

	if (DEBUG_TEST) {
		printf("PLAYER %d - ", player);
	}

	// Test that the player's hand count is incremented (for treasure card added), then decremented for loss of trashed card & mine card 
	result += assertTrue("Hand Count", test->handCount[player], compare->handCount[player] - 1);
	result--;

	if (DEBUG_TEST) {
		printf("PLAYER %d - ", player);
	}

	// Test that the treasure card is in the hand 
	result += assertTrue("Card (Treasure) Last Hand Position", test->hand[player][4], treasure);		

	if (DEBUG_TEST) {
		printf("PLAYER %d - ", player);
	}

	// Test the player's deck count remains the same
	result += assertTrue("Deck Count", test->deckCount[player], compare->deckCount[player]);
	result--;

	if (DEBUG_TEST) {
		printf("PLAYER %d - ", player);
	}

	// Test that the player's discard count incremented (discard mine card) 
	result += assertTrue("Discard Count", test->discardCount[player], compare->discardCount[player] + 1);
	result--;

	// Other player's game state stays the same 
	for (m = 0; m < numPlayers; m++) {

		// Don't perform for our current player
		if (m != player) {
			if (DEBUG_TEST) {
				printf("OTHER PLAYER %d - ", m);
			}
			// HAND COUNT
			result += assertTrue("Hand Count", test->handCount[m], compare->handCount[m]);
			result--;

			if (DEBUG_TEST) {
				printf("OTHER PLAYER %d - ", m);
			}

			// DECK 
			result += assertTrue("Deck Count", test->deckCount[m], compare->deckCount[m]);
			result--;

			if (DEBUG_TEST) {
				printf("OTHER PLAYER %d - ", m);
			}

			// DISCARD COUNT
			result += assertTrue("Discard Count", test->discardCount[m], compare->discardCount[m]);
			result--;
		}
	}

	if (DEBUG_TEST) {
		printf("\n\n");
	}

	return result;
}

int main() {

	if (DEBUG_TEST) {
		printf("\n\n>>>>>>> CARD TEST 3: MINE_EFFECT() <<<<<<<<\n\n");
	}

	// Keep track of how many tests are passing of those attempted
	int result = 0;  // if result is non0 then we fail

	// Initialize values 
	struct gameState test2, test3, test4, test5, test6, test7, test8, test9, compare;
	int seed = 100;
	int k[10] = { adventurer, smithy, remodel, feast, mine, sea_hag, tribute, treasure_map, council_room, village };	// randomly chosen, only real importance is that it contains our adventurer card																												
	
																														// Input for numPlayers
	int minPlayers = 2;
	int midPlayers = 3;
	int maxPlayers = 4; // based on fact that MAX_PLAYERS = 4
	int numPlayers[3] = { minPlayers, midPlayers, maxPlayers };

	// Input for handPos
	int handPos[2] = { 0, 4 };
	int minePosition;

	// Input for choice 1 - card to trash 
	int choice1[2] = { 4, 0 }; // positions in hand 
	int trashPosition;

	// Input for choice 2 - treasure card no more than 3 coin greater than card trashed
	//int choice2[4] = {village, gold, gold };
	int choice2;

	// Input required for cardEffect, but not our function -- included so that the function can be called via cardEffect 
	//		and therefore implemented as a switch statement or separate function
	int choice3 = 0;
	int bonus = 0;

	// Iterators 
	int i, n;

	for (i = 0; i < 3; i++) {															// Test each possible number of players											
		if (DEBUG_TEST) {
			printf("TEST - %d PLAYERS\n\n", numPlayers[i]);
		}

		// Run with both position sets of mine/trashcard
		for (n = 0; n < 2; n++) {
			
				// player 0 goes first based on initialize Game state
				trashPosition = choice1[n];
				minePosition = handPos[n];
				test2.hand[0][minePosition] = mine;

				// SETUP: Happy Path - HandPos of Mine: MIN, HandPos of TrashCard = MAX, TrashCard = Copper, Choice2 = Silver
				if (DEBUG_TEST) {
					printf("\n\nHAPPY PATH - HandPos of Mine: %d, HandPos of Trashcard: %d, Trash Card: %d, Treasure Card/Choice 2: %d\n\n", minePosition, trashPosition, copper, silver);
				}
				initializeGame(numPlayers[i], k, seed, &test2);
				test2.hand[0][trashPosition] = copper; 
				choice2 = silver; 
				memcpy(&compare, &test2, sizeof(struct gameState));
		
					// Test return value 
					result += assertTrue("Return Value", cardEffect(mine, trashPosition, choice2, choice3, &test2, minePosition, &bonus), 0);
					result--; 

					result += checkHappyGameState(numPlayers[i], 0, choice2, &compare, &test2);

				// SETUP: Happy Path - HandPos of Mine: MIN, HandPos of TrashCard = MAX, TrashCard = Silver, Choice2 = Gold 
				if (DEBUG_TEST) {
					printf("\n\nHAPPY PATH - HandPos of Mine: %d, HandPos of Trashcard: %d, Trash Card: %d, Treasure Card/Choice 2: %d\n\n", minePosition, trashPosition, silver, gold);
				}
				initializeGame(numPlayers[i], k, seed, &test3);
				test3.hand[0][trashPosition] = silver;
				choice2 = gold;
				memcpy(&compare, &test3, sizeof(struct gameState));

					// Test return value 
					result += assertTrue("Return Value", cardEffect(mine, trashPosition, choice2, choice3, &test3, minePosition, &bonus), 0);
					result--; 

					result += checkHappyGameState(numPlayers[i], 0, choice2, &compare, &test3);

				// SETUP: Sad Path - TrashCard = Copper, Choice2 = Gold 
				if (DEBUG_TEST) {
					printf("\n\nSAD PATH - TREASURE TOO EXPENSIVE - HandPos of Mine: %d, HandPos of Trashcard: %d, Trash Card: %d, Treasure Card/Choice 2: %d\n\n", minePosition, trashPosition, copper, gold);
				}
				initializeGame(numPlayers[i], k, seed, &test4);
				test4.hand[0][trashPosition] = copper;
				choice2 = gold;
				memcpy(&compare, &test4, sizeof(struct gameState));

					// Test return value 
					result += assertTrue("Return Value", cardEffect(mine, trashPosition, choice2, choice3, &test4, minePosition, &bonus), -1);
					result--; 

					result += checkSadGameState(numPlayers[i], 0, choice2, &compare, &test4);

				// SETUP: Sad Path - TrashCard = -1 , Choice2 = Gold 
				if (DEBUG_TEST) {
					printf("\n\nSAD PATH - TRASH CARD INVALID - HandPos of Mine: %d, HandPos of Trashcard: %d, Trash Card: %d, Treasure Card/Choice 2: %d\n\n", minePosition, trashPosition, -1, gold);
				}

				initializeGame(numPlayers[i], k, seed, &test5);
				test5.hand[0][trashPosition] = -1;
				choice2 = gold;
				memcpy(&compare, &test5, sizeof(struct gameState));

					// Test return value 
					result += assertTrue("Return Value", cardEffect(mine, trashPosition, choice2, choice3, &test5, minePosition, &bonus), -1);
					result--; 

					result += checkSadGameState(numPlayers[i], 0, choice2, &compare, &test5);

				// SETUP: Sad Path - TrashCard = Curse , Choice2 = Gold 
				if (DEBUG_TEST) {
					printf("\n\nSAD PATH - TRASH CARD NOT TREASURE - HandPos of Mine: %d, HandPos of Trashcard: %d, Trash Card: %d, Treasure Card/Choice 2: %d\n\n", minePosition, trashPosition, curse, gold);
				}
				initializeGame(numPlayers[i], k, seed, &test6);
				test6.hand[0][trashPosition] = curse;
				choice2 = gold;
				memcpy(&compare, &test6, sizeof(struct gameState));

					// Test return value 
					result += assertTrue("Return Value", cardEffect(mine, trashPosition, choice2, choice3, &test6, minePosition, &bonus), -1);
					result--; 

					result += checkSadGameState(numPlayers[i], 0, choice2, &compare, &test6);


				// SETUP: Sad Path - TrashCard = Treasure_Map , Choice2 = Gold 
				if (DEBUG_TEST) {
					printf("\n\nSAD PATH - TRASH CARD NOT TREASURE - HandPos of Mine: %d, HandPos of Trashcard: %d, Trash Card: %d, Treasure Card/Choice 2: %d\n\n", minePosition, trashPosition, treasure_map, gold);
				}
				initializeGame(numPlayers[i], k, seed, &test7);
				test7.hand[0][trashPosition] = treasure_map;
				choice2 = gold;
				memcpy(&compare, &test7, sizeof(struct gameState));

					// Test return value 
					result += assertTrue("Return Value", cardEffect(mine, trashPosition, choice2, choice3, &test7, minePosition, &bonus), -1);
					result--; 

					result += checkSadGameState(numPlayers[i], 0, choice2, &compare, &test7);

				// SETUP: Sad Path - HandPos of Mine: MIN, HandPos of TrashCard = MAX, TrashCard = Copper , Choice2 = Village
				if (DEBUG_TEST) {
					printf("\n\nSAD PATH - TREASURE CARD NOT TREASURE - HandPos of Mine: %d, HandPos of Trashcard: %d, Trash Card: %d, Treasure Card/Choice 2: %d\n\n", minePosition, trashPosition, copper, village);
				}
				initializeGame(numPlayers[i], k, seed, &test8);
				test8.hand[0][trashPosition] = copper;
				choice2 = village;
				memcpy(&compare, &test8, sizeof(struct gameState));


					// Test return value 
					result += assertTrue("Return Value", cardEffect(mine, trashPosition, choice2, choice3, &test8, minePosition, &bonus), -1);
					result--;
					result += checkSadGameState(numPlayers[i], 0, choice2, &compare, &test8);


				// SETUP: Sad Path - HandPos of Mine: MIN, HandPos of TrashCard = MAX, TrashCard = Copper , Choice2 = Village
				if (DEBUG_TEST) {
					printf("\n\nSAD PATH - TREASURE CARD INVALID - HandPos of Mine: %d, HandPos of Trashcard: %d, Trash Card: %d, Treasure Card/Choice 2: %d\n\n", minePosition, trashPosition, copper, -1);
				}

				initializeGame(numPlayers[i], k, seed, &test9);
				test9.hand[0][trashPosition] = copper;
				choice2 = -1;
				memcpy(&compare, &test9, sizeof(struct gameState));

				// Test return value 
				result += assertTrue("Return Value", cardEffect(mine, trashPosition, choice2, choice3, &test9, minePosition, &bonus), -1);
				result--;
				result += checkSadGameState(numPlayers[i], 0, choice2, &compare, &test9);
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

