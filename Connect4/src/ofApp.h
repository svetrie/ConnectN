#pragma once

#include "ofMain.h"
#include "GameBoard.h"

#include "ofxGui.h"
#include "ofxInputField\src\ofxInputField.h"

#include <vector>
using std::vector;

#include <string>
using std::string;

class ofApp : public ofBaseApp{

	enum GameState {
		START_GAME,
		PLAYER1_TURN,
		PLAYER2_TURN,
		FINISHED
	};
	
	struct Player {
		string name;
		int wins;
		bool red_checker;

		Player(string player_name) : name(player_name), wins(0), red_checker(false) {};
	};

	private:
		GameState current_state;
		GameBoard game_board;
		Player* player1;
		Player* player2;

		vector<vector<ofRectangle>> game_grid;
		const int GRID_HEIGHT = 6;
		const int GRID_WIDTH = 7;
		const int GRID_SQUARE_SIZE = 100;
		const float INITIAL_Y = 200;
		const float INITIAL_X = 600;

		const int ARROW_HEIGHT = 50;
		const int ARROWHEAD_SIZE = 15;
		ofRectangle arrow_pos;
		ofVec3f arrowhead_pos;
		ofVec3f arrowtail_pos;

		const int CHECKER_RADIUS = 30;

		ofxButton ok_button;
		ofxTextField player1_name;
		ofxTextField player2_name;
		ofxPanel gui;
		//ofxBaseGui gui;


	public:
		void setup();
		void update();
		void draw();

		void initializeGrid();
		void drawGrid();

		void shiftArrowPos(bool shift_right);
		void reorientArrow();
		void drawArrow();
		
		void addChecker();
		void drawCheckers();

		void setupGui();
		void drawGui();

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
		
		void getPlayersInfo();
};
