ISSUES

* I had difficulty creating a method to check for diagonal winning sequences. I was unable to check for diagonal sequences with a 
positive slope and diagonal sequences with a negative slope in the same method. I resolved this issue by creating two helper functions, 
one for each type of diagonal sequence

* I was unsure how to test the methods I created for my GameBoard class since my methods needed the board to have different states
to fully test all aspects of their functionality. Since it is tedious to manually create 2D vectors and assign them to my board 
variable, I created helper functions that allow me to easily modify the state of my board by changing individual rows, columns, or
even elements

* I struggled a lot to debug my methods that check for diagonal win sequences. I kept encountering out of bounds errors but could not 
find any problems in the general logic of my algorithms. I finally realized that my first while loop in my methods increments or decrements
my row and column variables one element past the bounds of my board vector. When I tried accessing elements in the board in the second 
while loop, I was trying to access invalid bounds on the first iteration. I resolved this issue by changing the bounds back from
the last iteration of the first while loop so that the bounds would be valid when I entered my second while loop.

* Creating my game board using openFrameworks' graphics library was more time consuming and problematic than I expected. The coordinate system 
was set up differently than I am used to and it took me a lot of trial and error to find the right dimensions for my board and center it properly.
I also had trouble separating the different squares in my game board. My board would look like a giant rectangle rather than a grid resembling 
a Connect4 board. I solved this issue by using the drawLine method to draw vertical and horizontal lines on the boundaries between different 
squares on the grid. Thus, it is now easy to identify the individual squares that the grid is composed of.