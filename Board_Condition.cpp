#include "Board_Condition.h"
#include "Judge.h"

void Board_Condition::make_move(int col, int* memoX, int* memoY)
{
	*memoX = lastX;
	*memoY = lastY;
	lastX = top[col] - 1;
	lastY = col;
	board[top[col] - 1][col] = turn;
	top[col] -= 1;
	if (col == noY && top[col] - 1 == noX) top[col] -= 1;
	turn = 3 - turn;
}

void Board_Condition::return_move(int col, int memoX, int memoY)
{
	turn = 3 - turn;
	if (col == noY && top[col] == noX) top[col] += 1;
	top[col] += 1;
	board[top[col] - 1][col] = 0;
	lastX = memoX;
	lastY = memoY;
}

int Board_Condition::end_game()
{
	if (turn == 1 && machineWin(lastX, lastY, M, N, board)) return 2;
	else if (turn == 2 && userWin(lastX, lastY, M, N, board)) return 1;
	else if (isTie(N, top)) return 3 - turn;
	int res = 0;
	int poss_res = 0;
	for (int i = 0; i < N; i++)
	{
		if (top[i] != 0)
		{
			board[top[i] - 1][i] = 1;
			if (userWin(top[i] - 1, i, M, N, board))
			{
				if (turn == 1)
				{
					res = 1;
				}
				else if (turn == 2)
				{
					if (poss_res == 0)
					{
						poss_res = -1;
					}
					else if (poss_res == -1)
					{
						poss_res = 1;
					}
				}
			}
			board[top[i] - 1][i] = 0;
		}
		if (res != 0) return res;
	}
	if (poss_res == 1) return poss_res;
	poss_res == 0;
	for (int i = 0; i < N; i++)
	{
		if (top[i] != 0)
		{
			board[top[i] - 1][i] = 2;
			if (machineWin(top[i] - 1, i, M, N, board))
			{
				if (turn == 2)
				{
					res = 2;
				}
				else if (turn == 1)
				{
					if (poss_res == 0)
					{
						poss_res = -2;
					}
					else if (poss_res == -2)
					{
						poss_res = 2;
					}
				}
			}
			board[top[i] - 1][i] = 0;
		}
		if (res != 0) return res;
	}
	if (poss_res == 2) return poss_res;
	return 0;
}

int Board_Condition::must_move()
{
	int res = -1;
	for (int i = 0; i < N; i++)
	{
		if (top[i] != 0)
		{
			board[top[i] - 1][i] = 1;
			if (userWin(top[i] - 1, i, M, N, board))
			{
				if (turn == 2)
				{
					res = i;
				}
			}
			board[top[i] - 1][i] = 0;
		}
		if (res != -1) return res;
	}
	for (int i = 0; i < N; i++)
	{
		if (top[i] != 0)
		{
			board[top[i] - 1][i] = 2;
			if (machineWin(top[i] - 1, i, M, N, board))
			{
				if (turn == 1)
				{
					res = i;
				}
			}
			board[top[i] - 1][i] = 0;
		}
		if (res != -1) return res;
	}
	return -1;
}