#pragma once

#ifndef GB_H
#define GB_H

#include<vector>
using std::vector;

class GameBoard {
	private:
		vector<vector<int>> board;
		const int BOARD_HEIGHT = 6;
		const int BOARD_WIDTH = 7;
	
	public:
		GameBoard();
		
		vector<vector<int>>& getBoard();
		void setBoardAt(int player, int row, int column);
		void setBoardRow(int row_num, vector<int> new_row);
		void setBoardCol(int col_num, vector<int> new_col);

		bool isDiagonalWin(int row, int column);
		bool isForwardDiagonalWin(int player, int row, int column);
		bool isBackwardDiagonalWin(int player, int row, int column);
		bool isVerticalWin(int player, int column);
		bool isHorizontalWin(int player, int row);
		bool isWin(int player, int row, int column);
		
		int dropChecker(int player, int column);
};

#endif // !GB_H
