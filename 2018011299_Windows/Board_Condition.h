#ifndef STRATEGY_BOARD_CONDITION_H
#define STRATEGY_BOARD_CONDITION_H

struct Board_Condition
{
	int M = 0, N = 0;
	int* top = nullptr;
	int** board = nullptr;
	int lastX = 0, lastY = 0, noX = 0, noY = 0;
	int turn = 0;

	Board_Condition() = default;
	Board_Condition(const int _M, const int _N, int* _top, int** _board,
	                const int _lastX, const int _lastY, const int _noX, const int _noY, const int _turn):
	                M(_M), N(_N), top(_top), board(_board),
	                lastX(_lastX), lastY(_lastY), noX(_noX), noY(_noY), turn(_turn) {};

	int end_game();
	int must_move();
	void make_move(int col, int* memoX, int* memoY);
	void return_move(int col, int memoX, int memoY);
};

#endif
