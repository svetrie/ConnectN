#include "GameBoard.h"

#include <iostream>
using std::cout;
using std::endl;

GameBoard::GameBoard() {
	board = vector<vector<int>>(6, vector<int>(7, 0));
}

vector<vector<int>>& GameBoard::getBoard() {
	return board;
}

void GameBoard::setBoardAt(int player, int row, int column) {
	board[row][column] = player;
}

void GameBoard::setBoardRow(int row_num, vector<int> new_row) {
	board[row_num] = new_row;
}

void GameBoard::setBoardCol(int col_num, vector<int> new_col) {
	for (int i = 0; i < board.size(); i++) {
		board[i][col_num] = new_col[i];
	}
}

bool GameBoard::dropChecker(int player, int column) {
	int  i;

	for (i = 0; i < board.size(); i++) {
		if (i > 0 && board[i][column] != 0) {
			board[i - 1][column] = player;
			i--;
		} else if (i == board.size() - 1) {
			board[i][column] = player;
		}
	}

	return (isDiagonalWin(i, column) || isHorizontalWin(player, i) 
		|| isVerticalWin(player, column)); 
}

bool GameBoard::isBackwardDiagonalWin(int player, int row, int column) {
	int count = 0;

	while (row < board.size() && column < board[row].size()) {
		row++;
		column++;
	}

	row--;
	column--;

	while (row >= 0 && column >= 0) {
		if (board[row][column] == player) {
			count++;
		} else {
			count = 0;
		}
		
		if (count >= 4) {
			return true;
		}

		row--;
		column--;
	}

	return false;
}

bool GameBoard::isForwardDiagonalWin(int player, int row, int column) {
	int count = 0;

	cout << "works before loop" << endl;

	while (row < board.size() && column >= 0) {
		row++;
		column--;
	}

	row--;
	column++;

	while (row >= 0 && column < board[row].size()) {
		if (board[row][column] == player) {
			count++;
		} else {
			count = 0;
		}

		if (count >= 4) {
			return true;
		}

		row--;
		column++;
	}

	cout << "works after second loop" << endl;

	return false;
}

bool GameBoard::isDiagonalWin(int row, int column) {
	int player = board[row][column];
	return (isForwardDiagonalWin(player, row, column) || isBackwardDiagonalWin(player, row, column));
}

bool GameBoard::isHorizontalWin(int player, int row) {
	int count = 0;

	for (int i = 0; i < board[row].size(); i++) {
		if (board[row][i] == player) {
			count++;
		} else {
			count = 0;
		}

		if (count >= 4) {
			return true;
		}
	}

	return false;
 }

bool GameBoard::isVerticalWin(int player, int column) {
	int count = 0;

	for (int i = 0; i < board.size(); i++) {
		if (board[i][column] == player) {
			count++;
		} else {
			count = 0;
		}

		if (count >= 4) {
			return true;
		}
	}

	return false;
}