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

TEST_CASE("NotVerticalWinTest") {
	GameBoard gameboard = GameBoard();
	vector<int> col{ 1,2,1,2,1,2 };

	gameboard.setBoardCol(4, col);

	REQUIRE(!gameboard.isVerticalWin(1, 4));
	REQUIRE(!gameboard.isVerticalWin(2, 4));
}

TEST_CASE("BackwardDiagonalWinTest") {
	GameBoard gameboard = GameBoard();
	
	for (int i = 0; i < gameboard.getBoard().size(); i++) {
		gameboard.setBoardAt(2, i, i);
	}

	REQUIRE(gameboard.isBackwardDiagonalWin(2, 0, 0));
	REQUIRE(gameboard.isBackwardDiagonalWin(2, 5, 5));
}

TEST_CASE("NotBackwardsDiagonalWinTest") {
	GameBoard gameboard = GameBoard();
	gameboard.setBoardAt(2, 0, 3);
	gameboard.setBoardAt(1, 1, 4);
	
	REQUIRE(!gameboard.isBackwardDiagonalWin(1, 3, 6));
	REQUIRE(!gameboard.isBackwardDiagonalWin(2, 3, 6));
}

TEST_CASE("CornersBackwardDiagonalTest") {
	GameBoard gameboard = GameBoard();
	
	REQUIRE(!gameboard.isBackwardDiagonalWin(0, 5, 0));
	REQUIRE(!gameboard.isBackwardDiagonalWin(0, 0, 6));
	REQUIRE(gameboard.isBackwardDiagonalWin(0, 5, 6));
}

TEST_CASE("ForwardDiagonalWinTest") {
	GameBoard gameboard = GameBoard();

	for (int i = 5; i > 0; i--) {
		gameboard.setBoardAt(2, i, 6 - (i + 1));
	}

	REQUIRE(gameboard.isForwardDiagonalWin(2, 5, 0));
	REQUIRE(gameboard.isForwardDiagonalWin(2, 0, 5));
}

TEST_CASE("NotFowardDiagonalWinTest") {
	GameBoard gameboard = GameBoard();
	gameboard.setBoardAt(2, 3, 0);
	gameboard.setBoardAt(1, 2, 1);

	REQUIRE(!gameboard.isForwardDiagonalWin(1, 0, 3));
	REQUIRE(!gameboard.isForwardDiagonalWin(2, 0, 3));
}

TEST_CASE("CornersForwardDiagonalTest") {
	GameBoard gameboard = GameBoard();

	REQUIRE(!gameboard.isForwardDiagonalWin(0, 0, 0));
	REQUIRE(!gameboard.isForwardDiagonalWin(0, 5, 6));
	REQUIRE(gameboard.isForwardDiagonalWin(0, 0, 6));
}

TEST_CASE("DropCheckerEmptyColumnTest") {
	GameBoard gameboard = GameBoard();
	gameboard.dropChecker(2, 0);

	REQUIRE(gameboard.getBoard()[5][0] == 2);
}

TEST_CASE("DropCheckerTest") {
	GameBoard gameboard = GameBoard();
	gameboard.setBoardAt(2, 5, 0);
	gameboard.dropChecker(2, 0);

	REQUIRE(gameboard.getBoard()[4][0] == 2);
}

TEST_CASE("DropCheckerFullColumnTest") {
	GameBoard gameboard = GameBoard();
	vector<int> column{ 0,1,1,1,1,1 };
	gameboard.setBoardCol(0, column);
	
	//REQUIRE(gameboard.dropChecker(2, 0) == 0);
	REQUIRE(gameboard.getBoard()[0][0] == 2);
}
