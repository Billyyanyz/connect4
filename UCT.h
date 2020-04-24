#ifndef STRATEGY_UCT_H
#define STRATEGY_UCT_H

#include "Const.h"
#include "Board_Condition.h"

struct UCT_Node
{
	int specific_action = 0;
	int attempts = 0, wins = 0;
	int parent = -1;
	int children[MAXN] {0};

	double UCB1();
};

extern UCT_Node* node_list;
extern int node_list_count;
extern Board_Condition board_condition;

int column_choice(int k);
int MCTS(int k);

#endif
