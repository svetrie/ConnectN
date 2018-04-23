#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	current_state = START_GAME;

	game_grid = vector<vector<ofRectangle>>(GRID_HEIGHT, vector<ofRectangle>(GRID_WIDTH));
	initializeGrid();

	arrow_pos = ofRectangle(INITIAL_X, INITIAL_Y, GRID_SQUARE_SIZE, GRID_SQUARE_SIZE);
	reorientArrow();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
//split method into draw grid and initialize grid 
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
	int column = (arrow_pos.getMinX() - INITIAL_X) / GRID_SQUARE_SIZE;
	int row = game_board.dropChecker(1, column);

	//Check that row isn't equal to -1 before trying to access it 
}

void ofApp::drawCheckers() {
	for (int r = 0; r < GRID_HEIGHT; r++) {
		for (int c = 0; c < GRID_WIDTH; c++) {
			//Should make this an if else statement depending on which player it is
			if (game_board.getBoard()[r][c] != 0) {
				ofDrawCircle(game_grid[r][c].getCenter().x, game_grid[r][c].getCenter().y, CHECKER_RADIUS);
			}
		}
	}
}

void ofApp::draw() {
	drawGrid();
	drawArrow();
	drawCheckers();
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
	if (key == OF_KEY_LEFT) {
		shiftArrowPos(false);
		update();
	} else if (key == OF_KEY_RIGHT) {
		shiftArrowPos(true);
		update();
	} else if (key == OF_KEY_RETURN) {
		//should_draw = true;
		addChecker();
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
