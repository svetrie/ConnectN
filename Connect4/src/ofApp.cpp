#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//current_state = START_GAME;
	current_state = PLAYER1_TURN;

	game_grid = vector<vector<ofRectangle>>(GRID_HEIGHT, vector<ofRectangle>(GRID_WIDTH));
	initializeGrid();

	arrow_pos = ofRectangle(INITIAL_X, INITIAL_Y, GRID_SQUARE_SIZE, GRID_SQUARE_SIZE);
	reorientArrow();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::initializeGrid() {
	for (int y = 0; y < GRID_HEIGHT; y++) {
		for (int x = 0; x < GRID_WIDTH; x++) {
			game_grid[y][x] = ofRectangle(x * GRID_SQUARE_SIZE + INITIAL_X,
				y * GRID_SQUARE_SIZE + INITIAL_Y, GRID_SQUARE_SIZE, GRID_SQUARE_SIZE);
		}
	}
}

void ofApp::drawGrid() {	
	for (int y = 0; y < GRID_HEIGHT; y++) {
		for (int x = 0; x < GRID_WIDTH; x++) {
			ofSetColor(255, 0, 0);

			ofDrawRectangle(x * GRID_SQUARE_SIZE + INITIAL_X,
				y * GRID_SQUARE_SIZE + INITIAL_Y, GRID_SQUARE_SIZE, GRID_SQUARE_SIZE);

			ofSetColor(45, 45, 45);

			//Draws horizontal lines across grid
			ofDrawLine(x * GRID_SQUARE_SIZE + INITIAL_X, y * GRID_SQUARE_SIZE + INITIAL_Y,
				(x + 1) * GRID_SQUARE_SIZE + INITIAL_X, y * GRID_SQUARE_SIZE + INITIAL_Y);

			//Draws vertical lines across grid
			ofDrawLine(x * GRID_SQUARE_SIZE + INITIAL_X, y * GRID_SQUARE_SIZE + INITIAL_Y,
				x * GRID_SQUARE_SIZE + INITIAL_X, (y + 1) * GRID_SQUARE_SIZE + INITIAL_Y);
		}
	}
}

void ofApp::drawArrow() {
	ofDrawArrow(arrowtail_pos, arrowhead_pos, ARROWHEAD_SIZE);
}

void ofApp::addChecker() {
	int player_num = (current_state == PLAYER1_TURN) ? 1 : 2;
	int column = (arrow_pos.getMinX() - INITIAL_X) / GRID_SQUARE_SIZE;
	int row = game_board.dropChecker(player_num, column);

	//Check that row isn't equal to -1 before trying to access it 
}

void ofApp::drawCheckers() {
	for (int r = 0; r < GRID_HEIGHT; r++) {
		for (int c = 0; c < GRID_WIDTH; c++) {
			//Should make this an if else statement depending on which player it is
			/*if (game_board.getBoard()[r][c] != 0) {
				ofDrawCircle(game_grid[r][c].getCenter().x, game_grid[r][c].getCenter().y, CHECKER_RADIUS);
			}*/
			if (game_board.getBoard()[r][c] == 1) {
				ofSetColor(0, 0, 0);
				ofDrawCircle(game_grid[r][c].getCenter().x, game_grid[r][c].getCenter().y, CHECKER_RADIUS);
			} else if (game_board.getBoard()[r][c] == 2) {
				ofSetColor(255, 255, 255);
				ofDrawCircle(game_grid[r][c].getCenter().x, game_grid[r][c].getCenter().y, CHECKER_RADIUS);
			}
		}
	}
}

void ofApp::setupGui() {
	ofSetVerticalSync(true);

	gui.setup("panel");
	gui.setup();
	gui.add(ok_button.setup("ok", 100, 100));
	
	//gui.draw()
	//gui.
	//gui.add(ok_button.setup("ok"));
	//gui.add(player1_name.setup("Player 1 Name: ", "type here"));
	//gui.add(player2_name.setup("PLayer 2 Name: ", "type here"));

}

void ofApp::draw() {
	if (current_state == START_GAME) {
		gui.draw();
	} else if (current_state == PLAYER1_TURN || current_state == PLAYER2_TURN){
		drawGrid();
		drawArrow();
		drawCheckers();
	}
}

void ofApp::shiftArrowPos(bool shift_right) {
	if (shift_right && arrow_pos.getMinX() < (INITIAL_X + GRID_SQUARE_SIZE * (GRID_WIDTH - 1))) {
		arrow_pos = ofRectangle(arrow_pos.x + GRID_SQUARE_SIZE, arrow_pos.y, GRID_SQUARE_SIZE, GRID_SQUARE_SIZE);
	} else if (arrow_pos.x != INITIAL_X) {
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
	if ((current_state == PLAYER1_TURN || current_state == PLAYER2_TURN) && key == OF_KEY_LEFT) {
		shiftArrowPos(false);
		update();
	} else if ((current_state == PLAYER1_TURN || current_state == PLAYER2_TURN) && key == OF_KEY_RIGHT) {
		shiftArrowPos(true);
		update();
	} else if ((current_state == PLAYER1_TURN || current_state == PLAYER2_TURN) && key == OF_KEY_RETURN) {
		addChecker();
		update();

		//End current player's turn and begin other player's turn 
		current_state = (current_state == PLAYER1_TURN) ? PLAYER2_TURN : PLAYER1_TURN;
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
