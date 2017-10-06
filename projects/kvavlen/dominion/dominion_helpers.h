#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state, 
		int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3, 
	       struct gameState *state, int handPos, int *bonus);

/* Assignment 2 */
int adventurer_effect(int z, int currentPlayer, int cardDrawn, int drawntreasure, int *temphand, struct gameState *state);
int feast_effect(int i, int x, int currentPlayer, int *temphand, int choice1, struct gameState *state);
int mine_effect(int i, int j, int currentPlayer, int choice1, int choice2, int handPos, struct gameState *state);
int remodel_effect(int i, int j, int currentPlayer, int choice1, int choice2, int handPos, struct gameState *state);
int smithy_effect(int i, int currentPlayer, int handPos, struct gameState *state);
#endif
