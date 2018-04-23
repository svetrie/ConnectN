#include "GameBoard.h"

#include <iostream>
using std::cout;
using std::endl;

GameBoard::GameBoard() {
	board = vector<vector<int>>(BOARD_HEIGHT, vector<int>(BOARD_WIDTH, 0));
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

// Returns the row the checker was dropped in or -1 if the entire column was full
int GameBoard::dropChecker(int player, int column) {
	if (board[0][column] != 0) {
		return -1;
	}

	for (int i = 0; i < board.size(); i++) {
		if (i > 0 && board[i][column] != 0) {
			i--;
			board[i][column] = player;
			return i;
		} else if (i == board.size() - 1) {
			board[i][column] = player;
			return i;
		}
	}
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

bool GameBoard::isWin(int player, int row, int column) {
	return (isDiagonalWin(row, column), isHorizontalWin(player, row), isVerticalWin(player, column));
}