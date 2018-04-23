#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	current_state = START_GAME;

	game_grid = vector<vector<ofRectangle>>(GRID_HEIGHT, vector<ofRectangle>(GRID_WIDTH));

	arrow_pos = ofRectangle(INITIAL_X, INITIAL_Y, GRID_SQUARE_SIZE, GRID_SQUARE_SIZE);
	arrowtail_pos = ofVec3f(arrow_pos.getCenter().x, arrow_pos.getMinY() - GRID_SQUARE_SIZE, 0);
	arrowhead_pos = ofVec3f(arrow_pos.getCenter().x, arrow_pos.getMinY() - GRID_SQUARE_SIZE + ARROW_HEIGHT, 0);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::drawGrid(){	
	for (int y = 0; y < GRID_HEIGHT; y++) {
		for (int x = 0; x < GRID_WIDTH; x++) {
			ofSetColor(255, 0, 0);

			ofDrawRectangle(x * GRID_SQUARE_SIZE + INITIAL_X,
				y * GRID_SQUARE_SIZE + INITIAL_Y, GRID_SQUARE_SIZE, GRID_SQUARE_SIZE);
			
			game_grid[y][x] = ofRectangle(x * GRID_SQUARE_SIZE + INITIAL_X,
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
	
	//ofDrawRectangle(INITIAL_X, INITIAL_Y, GRID_SQUARE_SIZE, GRID_SQUARE_SIZE);
	//ofDrawRectangle(6 * GRID_SQUARE_SIZE + INITIAL_X, 5 * GRID_SQUARE_SIZE + INITIAL_Y, GRID_SQUARE_SIZE, GRID_SQUARE_SIZE);
}

void ofApp::drawArrow() {
	ofDrawArrow(arrowtail_pos, arrowhead_pos, ARROWHEAD_SIZE);
}

void ofApp::draw() {
	drawGrid();
	drawArrow();
}

void ofApp::shiftArrowPos(bool shift_right) {
	//Add and conditional to make sure arrow can't be shifted off the screen. Shouldn't be able to
	// move past inital X + Grid-square-size * grid-width or initial X
	if (shift_right && arrow_pos.x < (INITIAL_X + GRID_SQUARE_SIZE * (GRID_WIDTH - 1))) {
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
