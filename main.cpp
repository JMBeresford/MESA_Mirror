#include <SFML/Graphics.hpp>
#include <iostream>
#include "src/animatedSprite.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800,600), "Mesa Mirror"); // SFML window object
	sf::Sprite canvasTex;
	sf::Vector2u screenSize = window.getSize();
	sf::Font fnt;
	sf::Texture corner;
	sf::RenderTexture canvas; // Placeholder to draw things to, prior to drawing to screen
	canvas.create(screenSize.x/3,screenSize.y/3);

	if (!corner.loadFromFile("assets/bottomLeft.png"))
		std::cerr << "ERROR: Texture not found. Exiting...";

	if (!fnt.loadFromFile("assets/bladeRunner.ttf"))
		std::cerr << "ERROR: Font failed to load. Exiting...";
	
	sf::Sprite topLeft(corner);

	while(window.isOpen()) // This is a loop for the program window to live in, each iter a frame
	{
		window.setFramerateLimit(60);
		screenSize = window.getSize(); // 2-dimensional unsigned #'s
					       // representing screen size
		
		// It is highly encouraged to read through the documentation for SFML events
		// before attempting anything significant here. The event system is integral to
		// the operation of an SFML window and the documentation on their website will prove
		// quite insightful.

		sf::Event mirrorEvent; // This is the event object that all SFML events will be
		while(window.pollEvent(mirrorEvent)) // appended to, and the loop that iterates
		{				     // through them.

			if(mirrorEvent.type == sf::Event::Closed) // Terminates the outer
				window.close();			  // while loop when window is closed
		}
		
		canvas.clear();
		canvas.draw(topLeft);
		canvasTex.setTexture(canvas.getTexture());
		window.clear();
		window.draw(canvasTex);
		window.display();
	}

	return 0;
}
