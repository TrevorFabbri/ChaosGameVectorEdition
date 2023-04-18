#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Triangle {
	private:
		RectangleShape fill;			// Shape being displayed
		Vector2f position;				// X & Y coordinates of where the shape is on the window display
	public:
		Triangle(Vector2f);				// Constructor with X & Y coordinates
		RectangleShape getShape();		// Returns the shape to display
		Vector2f getPosition();			// Returns the assigned coordinates of the shape
		int getPointCount();			// Returns how many points of the shape there are
		int getX();						// Returns the X coordinate of the shape
		int getY();						// Returns the Y coordinate of the shape
};