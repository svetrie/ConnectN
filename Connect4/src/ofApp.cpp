#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	setupStartMenu();

	//scoreboard.setup();
	//scoreboard.setPosition(SCOREBOARD_X, SCOREBOARD_Y);

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
	ofDrawArrow(arrowtail_pos, arrowhead_pos, ARROWHEAD_SIZE);
}

bool ofApp::addChecker() {
	int player_num = (current_state == PLAYER1_TURN) ? 1 : 2;
	int column = (arrow_pos.getMinX() - BOARD_X) / GRID_SQUARE_SIZE;
	int row = game_board.dropChecker(player_num, column);

	//Check that row isn't equal to -1 before trying to access it 
	//Check if player won using isWin() method in GameBoard class and change state to finished if true

	if (row > -1 && game_board.isWin(player_num, row, column)) {
		winner = (current_state == PLAYER1_TURN) ? player1 : player2;
		winner->wins = winner->wins + 1;
		current_state = FINISHED;
		setupDisplayResults();
	}

	//Returns whether or not current player was able to sucessfully drop a checker 
	return (row > -1);
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

void ofApp::setupStartMenu() {
	//ofSetVerticalSync(true);

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

	//ofDrawBitmapString(player1->name + ":" + to_string(player1->wins), 100, 100);
	//ofDrawBitmapString(player2->name + ":" + to_string(player2->wins), 100, 150);
}

void ofApp::setupDisplayResults() {
	display_results.setup();
	display_results.setPosition(DISPLAY_RESULTS_X, DISPLAY_RESULTS_Y);
	
	display_results.add(winner_msg.setup(winner->name + " won the game!!", WIDGET_WIDTH, WIDGET_HEIGHT));
	display_results.add(choose_N.setup("N Value", MIN_N, MIN_N, MAX_N, WIDGET_WIDTH, WIDGET_HEIGHT));
	display_results.add(play_again.setup("Play Again!", WIDGET_WIDTH, WIDGET_HEIGHT));
	display_results.add(exit_msg.setup(HOW_TO_EXIT, WIDGET_WIDTH, WIDGET_HEIGHT));
}

void ofApp::initializeGameSettings() {
	game_board = GameBoard(choose_N);

	if (player1 == nullptr && player2 == nullptr) {
		player1 = new Player(player1_info);
		player2 = new Player(player2_info);
	}
}

void ofApp::draw() {
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
	if (current_state == PLAYER1_TURN || current_state == PLAYER2_TURN) {
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
