#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	setupGui();

	current_state = START_GAME;
	
	game_grid = vector<vector<ofRectangle>>(GRID_HEIGHT, vector<ofRectangle>(GRID_WIDTH));
	initializeGrid();

	arrow_pos = ofRectangle(INITIAL_X_BOARD, INITIAL_Y_BOARD, GRID_SQUARE_SIZE, GRID_SQUARE_SIZE);
	reorientArrow();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::initializeGrid() {
	for (int y = 0; y < GRID_HEIGHT; y++) {
		for (int x = 0; x < GRID_WIDTH; x++) {
			game_grid[y][x] = ofRectangle(x * GRID_SQUARE_SIZE + INITIAL_X_BOARD,
				y * GRID_SQUARE_SIZE + INITIAL_Y_BOARD, GRID_SQUARE_SIZE, GRID_SQUARE_SIZE);
		}
	}
}

void ofApp::drawGrid() {	
	for (int y = 0; y < GRID_HEIGHT; y++) {
		for (int x = 0; x < GRID_WIDTH; x++) {
			ofSetColor(255, 0, 0);

			ofDrawRectangle(x * GRID_SQUARE_SIZE + INITIAL_X_BOARD,
				y * GRID_SQUARE_SIZE + INITIAL_Y_BOARD, GRID_SQUARE_SIZE, GRID_SQUARE_SIZE);

			ofSetColor(45, 45, 45);

			//Draws horizontal lines across grid
			ofDrawLine(x * GRID_SQUARE_SIZE + INITIAL_X_BOARD, y * GRID_SQUARE_SIZE + INITIAL_Y_BOARD,
				(x + 1) * GRID_SQUARE_SIZE + INITIAL_X_BOARD, y * GRID_SQUARE_SIZE + INITIAL_Y_BOARD);

			//Draws vertical lines across grid
			ofDrawLine(x * GRID_SQUARE_SIZE + INITIAL_X_BOARD, y * GRID_SQUARE_SIZE + INITIAL_Y_BOARD,
				x * GRID_SQUARE_SIZE + INITIAL_X_BOARD, (y + 1) * GRID_SQUARE_SIZE + INITIAL_Y_BOARD);
		}
	}
}

void ofApp::drawArrow() {
	ofDrawArrow(arrowtail_pos, arrowhead_pos, ARROWHEAD_SIZE);
}

bool ofApp::addChecker() {
	int player_num = (current_state == PLAYER1_TURN) ? 1 : 2;
	int column = (arrow_pos.getMinX() - INITIAL_X_BOARD) / GRID_SQUARE_SIZE;
	int row = game_board.dropChecker(player_num, column);

	//Check that row isn't equal to -1 before trying to access it 
	//Check if player won using isWin() method in GameBoard class and change state to finished if true

	//Returns whether or not curernt player was able to sucessfully drop a checker 
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

void ofApp::setupGui() {
	//ofSetVerticalSync(true);
	
	gui.setup();
	gui.setPosition(INITIAL_X_GUI, INITIAL_Y_GUI);
	gui.setSize(WIDGET_WIDTH, WIDGET_WIDTH);

	gui.add(welcome_msg.setup("", GREETINGS, WIDGET_WIDTH, WIDGET_HEIGHT));
	gui.add(instructions.setup("", DIRECTIONS, WIDGET_WIDTH, WIDGET_HEIGHT));

	gui.add(player1_info.setup("Player 1 Name: ", "Enter name here", "", "", WIDGET_WIDTH, WIDGET_HEIGHT));
	gui.add(player2_info.setup("Player 2 Name: ", "Enter name here", "", "", WIDGET_WIDTH, WIDGET_HEIGHT));

	gui.add(choose_N.setup("N Value", MIN_N, MIN_N, MAX_N, WIDGET_WIDTH, WIDGET_HEIGHT));

	gui.add(ok_button.setup("Ok!", WIDGET_WIDTH, WIDGET_HEIGHT));
}

void ofApp::useGuiInfo() {
	game_board = GameBoard(choose_N);
	
	*player1 = Player(player1_info);
	*player2 = Player(player2_info);
}

void ofApp::draw() {
	if (current_state == START_GAME) {
		gui.draw();
		
		if (ok_button) {
			
			current_state = PLAYER1_TURN;
		}

		//current_state = PLAYER1_TURN;
		
		//ofSystemTextBoxDialog("Player 1 Name: ", "Type here");
		//player1_name.draw(100, 100, 100, 100);
	} 
	else if (current_state == PLAYER1_TURN || current_state == PLAYER2_TURN){
		drawGrid();
		drawArrow();
		drawCheckers();
	}
}

void ofApp::shiftArrowPos(bool shift_right) {
	if (shift_right && arrow_pos.getMinX() < (INITIAL_X_BOARD + GRID_SQUARE_SIZE * (GRID_WIDTH - 1))) {
		arrow_pos = ofRectangle(arrow_pos.x + GRID_SQUARE_SIZE, arrow_pos.y, GRID_SQUARE_SIZE, GRID_SQUARE_SIZE);
	} 
	else if (arrow_pos.x != INITIAL_X_BOARD) {
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
			if (addChecker()) {
				current_state = (current_state == PLAYER1_TURN) ? PLAYER2_TURN : PLAYER1_TURN;
			}
		}
		update();
	}
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
