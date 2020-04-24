#include <iostream>
#include <chrono>

#include "Point.h"
#include "Strategy.h"
#include "UCT.h"
#include "Board_Condition.h"
#include "Const.h"
#include "Judge.h"

using namespace std;
Point* getPoint(const int M, const int N, const int* _top, const int* _board,
		const int lastX, const int lastY, const int noX, const int noY){
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	int x = -1, y = -1;
	int** board = new int*[M];
	for(int i = 0; i < M; i++){
		board[i] = new int[N];
		for(int j = 0; j < N; j++){
			board[i][j] = _board[i * N + j];
		}
	}
	int* top = new int[N];
	for (int i = 0; i < N; i++)
	{
		top[i] = _top[i];
	}

	if (lastX == -1)
	{
		if (noX >= M - 4 && noY == N / 2)
		{
			x = top[N / 2 - 1] - 1;
			y = N / 2 - 1;
			clearArray(M, N, board);
			delete[] top;
			return new Point(x, y);
		}
		else
		{
			x = top[N / 2] - 1;
			y = N / 2;
			clearArray(M, N, board);
			delete[] top;
			return new Point(x, y);
		}
	}

	srand(lastX * N + lastY * M);
	board_condition = Board_Condition(M, N, top, board, lastX, lastY, noX, noY, 2);
	int board_end_game = board_condition.end_game();
	std::cerr << board_end_game << std::endl;
	if (board_end_game == 0)
	{
		int board_must_move = board_condition.must_move();
		if (board_must_move != -1)
		{
			y = board_must_move;
			x = top[board_must_move] - 1;
		}
		else
		{
			node_list = new UCT_Node [MAX_NODE_COUNT];
			node_list_count = 0;
			while (std::chrono::steady_clock::now() - start < std::chrono::milliseconds(MAX_SEARCH_TIME))
			{
				MCTS(0);
				if (node_list_count > MAX_NODE_COUNT - 200) break;
			}

			int most_chosen = 0;
			int selected_move = 0;
			for (int i = 0; i < N; i++)
			{
				if (node_list[0].children[i] != 0 && node_list[node_list[0].children[i]].attempts > most_chosen)
				{
					most_chosen = node_list[node_list[0].children[i]].attempts;
					selected_move = i;
				}
			}
			x = top[selected_move] - 1;
			y = selected_move;
			if (node_list) delete[] node_list;
		}
	}
	else if (board_end_game == 2)
	{
		for (int i = 0; i < N; i++)
		{
			if (board_condition.top[i] > 0)
			{
				board[top[i] - 1][i] = 2;
				if (machineWin(top[i] - 1, i, M, N, board))
				{
					y = i;
					board[top[i] - 1][i] = 0;
					break;
				}
				else if (board_condition.end_game() == 2)
				{
					y = i;
				}
				board[top[i] - 1][i] = 0;
			}
		}
		x = top[y] - 1;
	}
	else
	{
		y = rand() % N;
		x = top[y] - 1;
	}


	clearArray(M, N, board);
	delete[] top;
	return new Point(x, y);
}

void clearPoint(Point* p){
	delete p;
	return;
}

void clearArray(int M, int N, int** board){
	for(int i = 0; i < M; i++){
		delete[] board[i];
	}
	delete[] board;
}
