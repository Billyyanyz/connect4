#ifndef STRATEGY_H_
#define	STRATEGY_H_

#include "Point.h"

Point* getPoint(const int M, const int N, const int* _top, const int* _board,
	const int lastX, const int lastY, const int noX, const int noY);
void clearPoint(Point* p);
void clearArray(int M, int N, int** board);

#endif