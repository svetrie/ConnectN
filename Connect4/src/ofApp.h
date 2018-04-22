#pragma once

#include "ofMain.h"

#include <vector>
using std::vector;

class ofApp : public ofBaseApp{
	private:
		vector<vector<ofRectangle>> game_grid;
		const int GRID_HEIGHT = 6;
		const int GRID_WIDTH = 7;
		const int GRID_SQUARE_SIZE = 100;
		const float INITIAL_Y = 200;
		const float INITIAL_X = 500;

		ofRectangle arrow_pos;
		const int ARROW_HEIGHT = 50;
		//const int ARROWHEAD_WIDTH = 25;
		ofVec3f arrowhead_pos;
		ofVec3f arrowtail_pos;
		const int ARROWHEAD_SIZE = 15;

	public:
		void setup();
		void update();
		void draw();
		void drawGrid();
		void drawArrow();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
