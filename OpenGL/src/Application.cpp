//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
#include "Graphics2D.h"
#include "maths.h"

#include <iostream>

using namespace std;

Graphics2D engine = Graphics2D(1000, 1000, "Trigonometry", false);
int amount = 24; //number of circles
bool colour = false;
bool showLines = false;

bool input() {
	switch (engine.getCurrentKey()) {
		case GLFW_KEY_UP:
			amount += 1;
			return true;

		case GLFW_KEY_DOWN:
			if (amount > 1) {
				amount -= 1;
			}
			return true;

		case 'C':
			colour = !colour;
			return false;

		case 'L':
			showLines = !showLines;
			return false;

		case 'R':
			amount = 24;
			return true;

		case GLFW_KEY_ESCAPE:
			engine.closeWindow();
			return false;
	}
}





//for now the coordinates system goes from (-aspectRatio, -1) to (aspectRatio, 1)
int main() {
	double colours[6][3] = {{1, 0, 0}, {1, 0.5, 0}, {1, 1, 0}, {0, 1, 0}, {0, 0, 1}, {1, 0, 1}};
	
	double increment = PI / amount; //distance between each angle (in radians)
	double currentDist;
	double time = 0;
	double currentAngle;
	double sinAngle, cosAngle;

	while (engine.shouldClose() == false) {
		currentAngle = 0;
		engine.setFillColour(1, 1, 1, 1);

		if (showLines == true) {
			for (int i = 0; i < amount; i++) {
				sinAngle = sin(currentAngle, 1000);
				cosAngle = cos(currentAngle, 1000);
				engine.line(-cosAngle, -sinAngle, cosAngle, sinAngle);
				currentAngle += increment;
			}
			currentAngle = 0;
		}

		for (int i = 0; i < amount; i++) {
			currentDist = sin(currentAngle + time, 1000) * 0.9;
			sinAngle = sin(currentAngle, 1000);
			cosAngle = cos(currentAngle, 1000);

			if (colour == true) {
				engine.setFillColour(colours[i % 6][0], colours[i % 6][1], colours[i % 6][2], 1);
			}

			engine.circle(currentDist * cosAngle, currentDist * sinAngle, 0.05);
			currentAngle += increment;
		}

		engine.clear();
		time += 0.01;

		if (input() == true) {
			increment = PI / amount;
		}
	}
}