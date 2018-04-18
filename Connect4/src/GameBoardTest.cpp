#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "GameBoard.h"

TEST_CASE("HorizontalWinTest") {
	GameBoard gameboard = GameBoard();
	vector<int> row{1,2,2,2,2,1,1};

	gameboard.setBoardRow(2, row);
	
	REQUIRE(gameboard.isHorizontalWin(2,2));
}

TEST_CASE("NotHorizontalWinTest") {
	GameBoard gameboard = GameBoard();
	vector<int> row{ 1,2,2,2,1,1,1 };

	gameboard.setBoardRow(3, row);

	REQUIRE(!gameboard.isHorizontalWin(2, 3));
	REQUIRE(!gameboard.isHorizontalWin(1, 3));
}

TEST_CASE("VerticalWinTest") {
	GameBoard gameboard = GameBoard();
	vector<int> col{ 1,2,2,2,2,1 };

	gameboard.setBoardCol(4, col);

	REQUIRE(gameboard.isVerticalWin(2, 4));
}

TEST_CASE("NotVerticalTest") {
	GameBoard gameboard = GameBoard();
	vector<int> col{ 1,2,1,2,1,2 };

	gameboard.setBoardCol(4, col);

	REQUIRE(!gameboard.isVerticalWin(1, 4));
	REQUIRE(!gameboard.isVerticalWin(2, 4));
}
