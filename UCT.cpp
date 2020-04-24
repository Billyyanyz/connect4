#include <cmath>
#include <cstdlib>
#include <iostream>

#include "UCT.h"

UCT_Node* node_list;
int node_list_count;
Board_Condition board_condition;


double UCT_Node::UCB1()
{
	if (!attempts) return POS_INF;
	return (double)(attempts - wins) / (double)attempts
	+ sqrt(2 * log(node_list[parent].attempts) / (double)attempts);
}

int column_choice(int k)
{
	bool all_chosen = true;
	double max_ucb = NEG_INF;
	int res = board_condition.must_move();
	if (res != -1) return res;
	for (int i = 0; i < board_condition.N; i++)
	{
		if (board_condition.top[i] > 0)
		{
			if (node_list[k].children[i] == 0)
			{
				all_chosen = false;
				break;
			}
			else
			{
				if (max_ucb < node_list[node_list[k].children[i]].UCB1())
				{
					max_ucb = node_list[node_list[k].children[i]].UCB1();
					res = i;
				}
			}
		}
	}
	if (all_chosen) return res;

	while(true)
	{
		res = rand() % board_condition.N;
		if (board_condition.top[res] > 0 && node_list[k].children[res] == 0) return res;
	}

}

int MCTS(int k)
{
	int board_end_game = board_condition.end_game();
	if (board_end_game != 0)
	{
		node_list[k].attempts += 1;
		if (board_end_game == board_condition.turn) node_list[k].wins += 1;
		return board_end_game;
	}

	int col = column_choice(k);
	if (node_list[k].children[col] == 0)
	{
		node_list_count++;
		node_list[k].children[col] = node_list_count;
		node_list[node_list_count].parent = k;
	}

	int memoX, memoY;
	board_condition.make_move(col, &memoX, &memoY);
	int final_res = MCTS(node_list[k].children[col]);
	board_condition.return_move(col, memoX, memoY);

	node_list[k].attempts += 1;
	if (final_res == board_condition.turn) node_list[k].wins += 1;
	return final_res;
}