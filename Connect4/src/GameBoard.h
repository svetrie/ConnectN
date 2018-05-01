#pragma once

#ifndef GB_H
#define GB_H

#include<vector>
using std::vector;

class GameBoard {

	struct BoardSpot {
		int row;
		int column;

		BoardSpot() : row(-1), column(-1) {};
		BoardSpot(int r, int c) : row(r), column(c) {};
	};

	private:
		vector<vector<int>> board;
		vector<BoardSpot> winning_sequence;
		const int BOARD_HEIGHT = 8;
		const int BOARD_WIDTH = 8;
		const int DEFAULT_N = 4;
		int n_value;
	
	public:
		GameBoard();
		GameBoard(int connect_n);

		GameBoard& operator=(const GameBoard& source);

		vector<vector<int>>& getBoard();
		vector<typename GameBoard::BoardSpot>& getWinningSequence();

		void setBoardAt(int player, int row, int column);
		void setBoardRow(int row_num, vector<int> new_row);
		void setBoardCol(int col_num, vector<int> new_col);

		bool isForwardDiagonalWin(int player, int row, int column);
		bool isBackwardDiagonalWin(int player, int row, int column);
		bool isVerticalWin(int player, int column);
		bool isHorizontalWin(int player, int row);
		bool isWin(int player, int row, int column);
		bool isBoardFull();
		
		int dropChecker(int player, int column);

		void clearBoard();
};

#endif // !GB_H
