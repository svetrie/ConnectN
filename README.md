# ConnectN

PROJECT DESCRIPTION
ConnectN is a variation of Connect4 that allows players to choose the number of the consecutive checkers needed to win. N values range from 4 to 8.
Unlike traditional Connect4, ConnectN is played on a 8 x 8 grid instead of a 6 x 7 grid to accomodate larger N values. To win a game of ConnectN,
a player must build a diagonal, horizontal, or vertical sequence of checkers before the other player does. 

GAMEPLAY INSTRUCTIONS
The first thing that will be displayed upon running the program will be the start menu. Players should enter in their names, select an N value, and then
click "Ok!" to start playing. Once the game begins, players can switch between columns by using the left and right arrow keys. To drop a checker into a 
column, players should press the Enter key. The arrow above the columns will change color depending on which player's turn it is. A black arrow indicates
that it is player 1's turn while a white arrow indicates that it is player 2's turn. After a game finishes, the winning sequence will be highlighted and
a new menu similar to the start menu will appear. Players will have the option of choosing a new N value and starting another game by pressing the 
"Play Again!" button. Otherwise, players can press the esc key to exit the program.

LIBRARIES USED
This project was built entirely in C++ and heavily relied upon openFramework's open source libraries. The main two libraries used in this 
project were ofxGui and the graphics library. The graphics library was essential in creating a graphical display for the game board and checkers 
while ofxGui was equally important in creating user interfaces that would allow players to enter in input and interact with the program. Other 
additional libraries that were used were ofxInputField to accept text input from players, ofSoundPlayer to add sound effects for when players 
dropped checkers onto the board, and of3dUtils to draw the arrow above the columns.

BUILD INSTRUCTIONS
To build this project, first make sure that you have all the libraries mentioned above installed, especially openFrameworks itself. 
Next, clone the project's files from the following github repository: https://github.com/uiuc-sp18-cs126/final-project-svetrie.git.
Once you have downloaded this repository, use the openFrameworks project generator to create a new project using the cloned repository.
When using the project generator, make sure that the addons ofxInputField and ofxGui are selected. Then, open up the new project in an 
appropriate IDE compatible with openFrameworks (Xcode for Mac and Visual Studios for Windows) and run the program by running main.cpp
