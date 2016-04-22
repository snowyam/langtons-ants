#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <iostream>

using namespace cv;
using namespace std;

#define BASEWIDTH 512
#define BASELENGTH 512

// 9 Color States; Max language/command string of 9 currently.
const int state[][3] = { {255,255,255}, {0,0,0}, {60,20,220},
						 {128,0,128}, {112,25,25}, {100,120,0},
						 {0,128,0}, {0,215,255}, {143,143,188},
						 {255,0,0}, {0,255,0}, {0,128,128}, 
						 {100,100,100}, {100,200,200}, {150,60,8} };

const int movement[4][2] = { {-1,0},   // Move ant north. Height - 1.
							 {0,1},    // Move ant east. Width + 1.
							 {1,0},    // Move ant south. Height + 1.
							 {0,-1} }; // Move ant west. Width - 1.

struct ant_orientation {
	int x;		// Row and height position.
	int y;		// Col and width position.
	int face;	// Direction ant is facing.
};

int main (int argc, char** argv)
{
	// Default grid size.
	int width = BASEWIDTH;
	int height = BASELENGTH;

	if (argc != 3)	// Test the CLI input.
	{
		cout << " Usage: $ ./langton [Language] [Steps]" << endl;
		cout << " Example: ./langton LLRR 100000" << endl;
		return -1;
	}

	// The language of the ant.
	string language = argv[1];
	int max_state = language.length();

	// Amount of steps the ant will travel.
	int steps = atoi(argv[2]);

	// OpenCV image grid for visualization. RGB.
	Mat grid(height, width, CV_8UC3, Scalar(255,255,255));	

	// Create grid color lookup table.
	int grid_c [BASELENGTH][BASEWIDTH];
	for (int row = 0; row < height; row++)
		for (int col = 0; col < width; col++)
			grid_c[row][col] = 0;	//Initialize to state 0 white.

	// Create the ant.
	ant_orientation ant;
	ant.x = height/2;
	ant.y = width/2;
	ant.face = 0;

	int pos_state;
	int next_state;

	// Main algorithm loop for # of steps.
	for (int i = 0; i < steps; i++)
	{
		// Current square color state.
		pos_state = grid_c[ant.x][ant.y];
		// Next color state.
		next_state = (pos_state + 1) % max_state;

		// Lookup language corresponding to current color.
		// Turn the ant.
		if (language.at(pos_state) == 'R')
			ant.face = (ant.face + 1) % 4; // Turn ant right.	
		else
		{
			ant.face = (ant.face - 1) % 4; // Turn ant left.
			if (ant.face < 0) // Cannot mod negatives.
				ant.face = 3;
		}

		// Change the current square color.
		grid_c[ant.x][ant.y] = next_state;
		// Change the corresponding image color. OpenCV is flipped x, y.
		grid.at<Vec3b>(Point(ant.y, ant.x))[0] = state[next_state][0];
		grid.at<Vec3b>(Point(ant.y, ant.x))[1] = state[next_state][1];
		grid.at<Vec3b>(Point(ant.y, ant.x))[2] = state[next_state][2];

		// Move the ant forward.
		ant.x += movement[ant.face][0];
		ant.y += movement[ant.face][1];

		// In bounds check.
		if (ant.x < height && ant.x >= 0 && ant.y > 0 && ant.y <= width)
		{
			// Mark where ant is.
			grid.at<Vec3b>(Point(ant.y, ant.x))[0] = 0;
			grid.at<Vec3b>(Point(ant.y, ant.x))[1] = 0;
			grid.at<Vec3b>(Point(ant.y, ant.x))[2] = 255;
		}

		// Out of bounds check.
		if (ant.x >= height || ant.x < 0 || ant.y < 0 || ant.y >= width)
		{
			i = steps + 1;
		}
	}

	namedWindow("Langton's Ant", WINDOW_NORMAL | WINDOW_FREERATIO);
	imshow("Langton's Ant", grid );
	resizeWindow("Langton's Ant", width, height);
	
	waitKey(0);

	return 0;
}