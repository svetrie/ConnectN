#include "GameBoard.h"

GameBoard::GameBoard() {
	board = vector<vector<int>>(6, vector<int>(7, 0));
}

bool GameBoard::dropChecker(int player, int column) {

}

bool GameBoard::isBackwardDiagonalWin(int row, int column) {
	int player = board[row][column];
	int count = 0;

	while (row < board.size() && column < board[row].size()) {
		row++;
		column++;
	}

	while (row > 0 && column > 0) {
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

bool GameBoard::isForwardDiagonalWin(int row, int column) {
	int player = board[row][column];
	int count = 0;

	while (row < board.size() && column > 0) {
		row++;
		column--;
	}

	while (row > 0 && column < board[row].size()) {
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

}

bool GameBoard::isDiagonalWin(int row, int column) {
	int count = 0;
	
	return (isForwardDiagonalWin(row, column) || isBackwardDiagonalWin(row, column));
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
		if (board[i][column == player]) {
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