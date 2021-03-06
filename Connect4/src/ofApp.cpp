#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	setupStartMenu();

	thud_sound.load(THUD_SOUND_FILE);
	error_sound.load(ERROR_SOUND_FILE);

	current_state = START_GAME;
	
	game_grid = vector<vector<ofRectangle>>(GRID_HEIGHT, vector<ofRectangle>(GRID_WIDTH));
	initializeGrid();

	arrow_pos = ofRectangle(BOARD_X, BOARD_Y, GRID_SQUARE_SIZE, GRID_SQUARE_SIZE);
	reorientArrow();
}

//--------------------------------------------------------------
void ofApp::update() {
	
}

//--------------------------------------------------------------
void ofApp::initializeGrid() {
	for (int y = 0; y < GRID_HEIGHT; y++) {
		for (int x = 0; x < GRID_WIDTH; x++) {
			game_grid[y][x] = ofRectangle(x * GRID_SQUARE_SIZE + BOARD_X,
				y * GRID_SQUARE_SIZE + BOARD_Y, GRID_SQUARE_SIZE, GRID_SQUARE_SIZE);
		}
	}
}

void ofApp::drawGrid() {	
	for (int y = 0; y < GRID_HEIGHT; y++) {
		for (int x = 0; x < GRID_WIDTH; x++) {
			ofSetColor(255, 0, 0);

			ofDrawRectangle(x * GRID_SQUARE_SIZE + BOARD_X,
				y * GRID_SQUARE_SIZE + BOARD_Y, GRID_SQUARE_SIZE, GRID_SQUARE_SIZE);

			ofSetColor(45, 45, 45);

			//Draws horizontal lines across grid
			ofDrawLine(x * GRID_SQUARE_SIZE + BOARD_X, y * GRID_SQUARE_SIZE + BOARD_Y,
				(x + 1) * GRID_SQUARE_SIZE + BOARD_X, y * GRID_SQUARE_SIZE + BOARD_Y);

			//Draws vertical lines across grid
			ofDrawLine(x * GRID_SQUARE_SIZE + BOARD_X, y * GRID_SQUARE_SIZE + BOARD_Y,
				x * GRID_SQUARE_SIZE + BOARD_X, (y + 1) * GRID_SQUARE_SIZE + BOARD_Y);
		}
	}
}

void ofApp::drawArrow() {
	//Conditionals switch arrow color depending on which player's turn it is
	if (current_state == PLAYER1_TURN) {
		ofSetColor(0, 0, 0);
	}
	else {
		ofSetColor(255, 255, 255);
	}
	
	ofDrawArrow(arrowtail_pos, arrowhead_pos, ARROWHEAD_SIZE);
}

//Returns whether or not player was able to sucessfully drop checker into a column
bool ofApp::addChecker() {
	int player_num = (current_state == PLAYER1_TURN) ? 1 : 2;
	int column = (arrow_pos.getMinX() - BOARD_X) / GRID_SQUARE_SIZE;
	int row = game_board.dropChecker(player_num, column);

	//If row == -1, then player tried to drop checker in full column which is an invalid move
	if (row == -1) {
		error_sound.play();
		return false;
	}

	thud_sound.play();
	
	//Checks if the player won or if the board is now full and the game is a tie
	if (game_board.isWin(player_num, row, column)) {
		finishGame(true);
	}
	else if (game_board.isBoardFull()) {
		finishGame(false);
	}

	return true;
}

void ofApp::drawCheckers() {
	for (int row = 0; row < GRID_HEIGHT; row++) {
		for (int column = 0; column < GRID_WIDTH; column++) {
			//Draws black checkers onto board for player 1 and white checkers for player 2
			if (game_board.getBoard()[row][column] == 1) {
				ofSetColor(0, 0, 0);
				ofDrawCircle(game_grid[row][column].getCenter().x, game_grid[row][column].getCenter().y, CHECKER_RADIUS);
			} 
			else if (game_board.getBoard()[row][column] == 2) {
				ofSetColor(255, 255, 255);
				ofDrawCircle(game_grid[row][column].getCenter().x, game_grid[row][column].getCenter().y, CHECKER_RADIUS);
			}
		}
	}
}

//Highlights the winning sequence after a game ends
void ofApp::drawWinningSequence() {
	for (auto board_spot : game_board.getWinningSequence()) {
		ofSetColor(255, 255, 0);
		ofDrawRectangle(game_grid[board_spot.row][board_spot.column]);
	}
}

void ofApp::setupStartMenu() {
	start_menu.setup();
	start_menu.setPosition(START_MENU_X, START_MENU_Y);
	start_menu.setSize(WIDGET_WIDTH, WIDGET_WIDTH);

	start_menu.add(welcome_msg.setup("", GREETINGS, WIDGET_WIDTH, WIDGET_HEIGHT));
	start_menu.add(instructions.setup("", DIRECTIONS, WIDGET_WIDTH, WIDGET_HEIGHT));

	start_menu.add(player1_info.setup("Player 1 Name: ", "Enter name here", "", "", WIDGET_WIDTH, WIDGET_HEIGHT));
	start_menu.add(player2_info.setup("Player 2 Name: ", "Enter name here", "", "", WIDGET_WIDTH, WIDGET_HEIGHT));

	start_menu.add(choose_N.setup("N Value", MIN_N, MIN_N, MAX_N, WIDGET_WIDTH, WIDGET_HEIGHT));

	start_menu.add(ok_button.setup("Ok!", WIDGET_WIDTH, WIDGET_HEIGHT));
}

void ofApp::setupScoreboard() {
	scoreboard.setup();
	scoreboard.setPosition(SCOREBOARD_X, SCOREBOARD_Y);
	
	scoreboard.add(description_label.setup(DESCRIPTION, 2 * SCOREBOARD_WIDTH, SCOREBOARD_HEIGHT / 3));
	scoreboard.add(player1_wins.setup(player1->name + " : " + to_string(player1->wins), 2 * SCOREBOARD_WIDTH, SCOREBOARD_HEIGHT / 3));
	scoreboard.add(player2_wins.setup(player2->name + " : " + to_string(player2->wins), 2 * SCOREBOARD_WIDTH, SCOREBOARD_HEIGHT / 3));
}

void ofApp::setupDisplayResults(bool isWin) {
	display_results.setup();
	display_results.setPosition(DISPLAY_RESULTS_X, DISPLAY_RESULTS_Y);
	
	if (isWin) {
		display_results.add(end_game_msg.setup(winner->name + " won the game!!", WIDGET_WIDTH, WIDGET_HEIGHT));
	}
	else {
		display_results.add(end_game_msg.setup(TIE_GAME_MSG, WIDGET_WIDTH, WIDGET_HEIGHT));
	}
	
	display_results.add(choose_N.setup("N Value", MIN_N, MIN_N, MAX_N, WIDGET_WIDTH, WIDGET_HEIGHT));
	display_results.add(play_again.setup("Play Again!", WIDGET_WIDTH, WIDGET_HEIGHT));
	display_results.add(exit_msg.setup(HOW_TO_EXIT, WIDGET_WIDTH, WIDGET_HEIGHT));
}

void ofApp::initializeGameSettings() {
	game_board = GameBoard(choose_N);

	//Avoid resetting players' info every time a new game starts 
	if (player1 == nullptr && player2 == nullptr) {
		player1 = new Player(player1_info);
		player2 = new Player(player2_info);
	}
}

//Sets the game state to finished and updates the winner's info if the game wasn't a tie
void ofApp::finishGame(bool isWin) {
	if (isWin) {
		winner = (current_state == PLAYER1_TURN) ? player1 : player2;
		winner->wins = winner->wins + 1;
	}
	
	current_state = FINISHED;
	setupDisplayResults(isWin);
}

void ofApp::draw() {
	ofSetBackgroundColor(140, 140, 140);

	if (current_state == START_GAME) {
		start_menu.draw();
		
		if (ok_button) {
			initializeGameSettings();
			setupScoreboard();
			current_state = PLAYER1_TURN;
		}
	} 
	else if (current_state == PLAYER1_TURN || current_state == PLAYER2_TURN){
		drawGrid();
		drawArrow();
		drawCheckers();
		scoreboard.draw();
	}
	else if (current_state == FINISHED) {
		display_results.draw();
		drawGrid();
		drawWinningSequence();
		drawCheckers();

		if (play_again) {
			initializeGameSettings();
			setupScoreboard();
			current_state = (winner == player1) ? PLAYER2_TURN : PLAYER1_TURN;
		}
	}
}

void ofApp::shiftArrowPos(bool shift_right) {
	if (shift_right && arrow_pos.getMinX() < (BOARD_X + GRID_SQUARE_SIZE * (GRID_WIDTH - 1))) {
		arrow_pos = ofRectangle(arrow_pos.x + GRID_SQUARE_SIZE, arrow_pos.y, GRID_SQUARE_SIZE, GRID_SQUARE_SIZE);
	} 
	else if (arrow_pos.x != BOARD_X) {
		arrow_pos = ofRectangle(arrow_pos.x - GRID_SQUARE_SIZE, arrow_pos.y, GRID_SQUARE_SIZE, GRID_SQUARE_SIZE);
	}

	reorientArrow();
}

void ofApp::reorientArrow() {
	arrowtail_pos = ofVec3f(arrow_pos.getCenter().x, arrow_pos.getMinY() - GRID_SQUARE_SIZE, 0);
	arrowhead_pos = ofVec3f(arrow_pos.getCenter().x, arrow_pos.getMinY() - GRID_SQUARE_SIZE + ARROW_HEIGHT, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (current_state != PLAYER1_TURN && current_state != PLAYER2_TURN) {
		return;
	}
		
	if (key == OF_KEY_LEFT) {
		shiftArrowPos(false);
	}
	else if (key == OF_KEY_RIGHT) {
		shiftArrowPos(true);
	}
	else if (key == OF_KEY_RETURN) {
		//Ends current player's turn only if current player was able to drop a checker succesfully
		if (addChecker() && current_state != FINISHED) {
			current_state = (current_state == PLAYER1_TURN) ? PLAYER2_TURN : PLAYER1_TURN;
		}
	}

	update();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
