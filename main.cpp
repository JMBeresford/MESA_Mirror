#include <SFML/Graphics.hpp>
#include <iostream>
#include "src/animatedSprite.hpp"

void splashScreen(sf::RenderWindow&, sf::Font&);
void setOriginToCenter(sf::Sprite&);

int main()
{
	sf::RenderWindow window(sf::VideoMode(800,600), "Mesa Mirror"); // SFML window object
	sf::Font fnt; // Font object, font files (.ttf, etc) can be loaded to change font

	if (!fnt.loadFromFile("assets/bladeRunner.ttf")) // Loading font file
		std::cerr << "ERROR: Font failed to load. Exiting...";
	
	while(window.isOpen()) // This is a loop for the program window to live in, each iter a frame
	{
		window.setFramerateLimit(60);
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
	
		splashScreen(window, fnt);
	}

	return 0;
}

void splashScreen(sf::RenderWindow& window, sf::Font& fnt)
{
	sf::Vector2u screenSize = window.getSize();
	sf::Texture corner; // Texture object used to draw images (from files, etc.)
	sf::Vector2u position; // 2 dimensional unsigned int for use in changing position

	if (!corner.loadFromFile("assets/corner.png"))
		std::cerr << "ERROR: Texture not found. Exiting...";
	
	sf::Sprite topLeft(corner); // Location defaults to top left corner of render
	setOriginToCenter(topLeft); // Due to origin change will need to change position
	topLeft.setPosition(corner.getSize().x / 2, corner.getSize().y / 2);

	sf::Sprite topRight(corner); // Will need to adjust location and rotation
	setOriginToCenter(topRight);
	topRight.rotate(90);
	position = (sf::Vector2u(screenSize.x - corner.getSize().x / 2, 
				 corner.getSize().y / 2));      // Sets location to screen width        
								// minus the width of the image
								// for x coordinate,
								// division by 2 to account for
								// centered origin
								    
	// Need to do some fancy type conversions between sf::Vector2u and sf::Vector2f
	// due to argument restrictions of these function calls; thus the Vector constructions
	// in the above and below function calls (f meaning 'float' and u 'unsigned int')
	// TODO: These conversions are unneccessary, remove them.
	topRight.setPosition(sf::Vector2f(position.x, position.y));

	sf::Sprite bottomRight(corner);
	setOriginToCenter(bottomRight);
	bottomRight.rotate(180);
	bottomRight.setPosition(screenSize.x - corner.getSize().x / 2,
				screenSize.y - corner.getSize().y / 2);
	
	sf::Sprite bottomLeft(corner);
	setOriginToCenter(bottomLeft);
	bottomLeft.rotate(270);
	position = sf::Vector2u(corner.getSize().x / 2,
				screenSize.y - corner.getSize().y / 2);

	bottomLeft.setPosition(sf::Vector2f(position.x, position.y));


	sf::Event mainEvent; // New event object for this 'screen'
	while(window.isOpen())
	{

		while(window.pollEvent(mainEvent))
		{
			if (mainEvent.type == sf::Event::Closed)
				window.close();

			if (mainEvent.type == sf::Event::Resized)
				screenSize = window.getSize(); // In case of window resize
		}

		window.clear(); // Needs to be cleared every frame
		
		window.draw(topLeft); // Draws the sprite to the RenderTexture
		window.draw(topRight);
		window.draw(bottomRight);
		window.draw(bottomLeft);
		
		window.display(); // Displays current window buffer on screen

	}
}

void setOriginToCenter(sf::Sprite& spr)
{
	/* In SFML, objects have an origin that act as the center of all transformations, such as
	 * rotation and position. The default value is the top left corner of said object
	 * (essetentially 0,0 in its local coordinate space). I find centering the origin
	 * makes transformations much easier thus this function.
	 */

	sf::FloatRect bounds = spr.getLocalBounds();

	spr.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
}
