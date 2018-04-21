#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	game_grid = vector<vector<ofRectangle>>(GRID_HEIGHT, vector<ofRectangle>(GRID_WIDTH));
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	
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

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
