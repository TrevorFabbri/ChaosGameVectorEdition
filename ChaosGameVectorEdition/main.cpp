#include "Triangle.h"
#include <sstream>
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

int main()
{
	// Create a video mode object
	VideoMode vm(1600, 900);

	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game", Style::Default);

	// Create a Text object to display instructions
	Text messageText;

	// Choose a font, color, size, and instructions displayed
	Font font;
	font.loadFromFile("DS-DIGI.ttf"); 
	messageText.setFont(font);
	messageText.setString("Click on 3 places to start");
	messageText.setCharacterSize(35);

	// Position the text at the top middle of the window
	FloatRect textRect2 = messageText.getLocalBounds();
	messageText.setOrigin(textRect2.left +
		textRect2.width / 2.0f,
		textRect2.top +
		textRect2.height / 2.0f);
	messageText.setPosition(1600 / 2.0f, 35);

	// Text window to show the user how many inputs they have done
	Text inputText;
	inputText.setFont(font);
	inputText.setString("Points created = 0");
	inputText.setCharacterSize(25);
	inputText.setPosition(20, 70);		// Set this text to the top left of the screen

	// Variable to store the amount of current points created
	int inputs = 0;

	// To check for furthur input, none needed after first 4 clicks
	bool acceptInput = true;
	bool startInput = false;

	// Vector to hold all the shapes to be displayed
	vector<Triangle> output;

	// Vector to hold all the current output positions
	vector<Vector2f> outputPositions;

	while (window.isOpen())
	{
		//********************************
		// TAKE INPUTS FROM USER IF NEEDED
		//********************************

		//Handle the player input
		Event event;
		while (window.pollEvent(event))
		{
			// Close window when the red X is pressed or ESC key pressed
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}

			// Input user mouse clicks into a vector of Vector2f's
			if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
			{
				if (acceptInput && !startInput)
				{
					// Display where the mouse inputs occur on the console
					cout << "Input " << inputs + 1 << ": " << endl;
					cout << "X: " << event.mouseButton.x << endl;
					cout << "Y: " << event.mouseButton.y << endl;
					cout << endl;

					// Create a temp Vector2f to store the mouse click, then push into the vector to store it
					Vector2f temp;
					temp.x = event.mouseButton.x;
					temp.y = event.mouseButton.y;
					outputPositions.push_back(temp);
					inputs++;

					// Create a shape at the designated position then store in the vector
					Triangle tempSquare(temp);
					output.push_back(tempSquare);
				}
			}
			
			if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left && startInput && acceptInput)
			{
				// Display where the starting input on the console
				cout << "Starting Input: " << endl;
				cout << "X: " << event.mouseButton.x << endl;
				cout << "Y: " << event.mouseButton.y << endl;
				cout << endl;

				// Create a temp Vector2f to store the mouse click, then push into the vector to store it
				Vector2f temp;
				temp.x = event.mouseButton.x;
				temp.y = event.mouseButton.y;
				outputPositions.push_back(temp);
				inputs++;

				// Create an output at the designated starting position
				Triangle tempSquare(temp);
				output.push_back(tempSquare);

				// No longer accept input
				startInput = false;
				acceptInput = false;
			}
		}
	
		// *********************
		// UPDATE WINDOW DISPLAY
		// *********************

		window.clear();

		// Display instructions if input needed
		if (acceptInput)
		{
			window.draw(messageText);
		}

		// After the 3rd mouse click, change prompt to get the starting position
		if (inputs == 3)
		{
			startInput = true;
			messageText.setString("Click on a starting position");
		}
		
		// Update the score text
		std::stringstream ss;
		ss << "Points created = " << inputs;
		inputText.setString(ss.str());

		// If no longer taking input
		if (!acceptInput && !startInput)
		{
			// Create a new shape to output at a position between a random endpoint and last displayed shape's position
			int r = rand() % (output.at(output.size() - 1).getPointCount() - 1 - 1 + 1);
			Vector2f temp;
			temp.x = (output.at(r).getX() * (0.5f) + output.at(output.size() - 1).getX() * 0.5f);
			temp.y = (output.at(r).getY() * (0.5f) + output.at(output.size() - 1).getY() * 0.5f);
			outputPositions.push_back(temp);
			inputs++;
			Triangle tempSquare(temp);
			output.push_back(tempSquare);

			// Output all the shapes that have been created
			for (int i = 0; i < output.size(); i++)
			{
				window.draw(output.at(i).getShape());
			}
		}

		// Output the number of inputs
		window.draw(inputText);

		window.display();
	}

	return 0;
}
