#pragma once

#include "ofMain.h"
#include "GameBoard.h"

#include "ofxGui.h"
#include "ofxInputField\src\ofxInputField.h"
//#include "ofxTextField\ofxTextField\ofSystemUtils.h"

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
		Player* winner;

		vector<vector<ofRectangle>> game_grid;
		const int GRID_HEIGHT = 8;
		const int GRID_WIDTH = 8;
		const int GRID_SQUARE_SIZE = 100;
		const float BOARD_Y = 200;
		const float BOARD_X = 550;

		const int ARROW_HEIGHT = 50;
		const int ARROWHEAD_SIZE = 15;
		ofRectangle arrow_pos;
		ofVec3f arrowhead_pos;
		ofVec3f arrowtail_pos;

		const int CHECKER_RADIUS = 30;

		const int START_MENU_X = 700;
		const int START_MENU_Y = 300;
		const int WIDGET_HEIGHT = 100;
		const int WIDGET_WIDTH = 400;
		const int MIN_N = 4;
		const int MAX_N = 8;
		const string DIRECTIONS = "Select an N value and click ok to start playing!";
		const string GREETINGS = "Welcome to ConnectN!";
		ofxPanel start_menu;
		ofxTextField player1_info;
		ofxTextField player2_info;
		ofxIntSlider choose_N;
		ofxButton ok_button;
		ofxLabel welcome_msg;
		ofxLabel instructions;
		
		const int SCOREBOARD_X = 100;
		const int SCOREBOARD_Y = 100;
		const int SCOREBOARD_WIDTH = 100;
		const int SCOREBOARD_HEIGHT = 150;
		const string DESCRIPTION = "SCOREBOARD";
		ofxPanel scoreboard;
		ofxLabel description_label;
		ofxLabel player1_wins;
		ofxLabel player2_wins;

		const int DISPLAY_RESULTS_X = 100;
		const int DISPLAY_RESULTS_Y = 100;
		const string HOW_TO_EXIT = "(To exit the game, press ESC)";
		//const int DISPLAY_RESULTS_WIDTH = 400;
		//const int DISPLAY_RESULTS_HEIGHT = 100;;
		ofxPanel display_results;
		ofxLabel winner_msg;
		ofxLabel exit_msg;
		ofxButton play_again;
	
	public:
		void setup();
		void update();
		void draw();

		void initializeGrid();
		void drawGrid();

		void shiftArrowPos(bool shift_right);
		void reorientArrow();
		void drawArrow();
		
		bool addChecker(); 
		void drawCheckers();

		void setupStartMenu();
		void initializeGameSettings();

		void setupScoreboard();

		void setupDisplayResults();

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
