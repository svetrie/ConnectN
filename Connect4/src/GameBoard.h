#pragma once

#ifndef GB_H
#define GB_H

#include<vector>
using std::vector;

class GameBoard {
	private:
		vector<vector<int>> board;
	
	public:
		GameBoard();
		bool isDiagonalWin(int row, int column);
		bool isForwardDiagonalWin(int row, int column);
		bool isBackwardDiagonalWin(int row, int column);
		bool isVerticalWin(int player, int column);
		bool isHorizontalWin(int player, int row);
		bool dropChecker(int player, int column);
};

#endif // !GB_H
