#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800,600), "Mesa Mirror"); // SFML window object
	sf::Vector2u screenSize = window.getSize();
	sf::Font fnt;
	sf::RenderTexture canvas; // Placeholder to draw things to, prior to drawing to screen
	canvas.create(screenSize.x/3,screenSize.y/3);

	if (!fnt.loadFromFile("assets/bladeRunner.ttf"))
		std::cerr << "ERROR: Font failed to load. Exiting...";


	while(window.isOpen()) // This is a loop for the program window to live in, each iter a frame
	{
		screenSize = window.getSize(); // 2-dimensional unsigned #'s
			  		       // representing screen size
		canvas.clear();


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



	}

	return 0;
}
