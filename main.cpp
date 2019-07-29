#include <SFML/Graphics.hpp>
#include <iostream>
#include "src/animatedSprite.hpp"

void splashScreen(sf::RenderWindow&, sf::Font&);
void setSpriteOriginToCenter(sf::Sprite&);
void setTextOriginToCenter(sf::Text&);

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
	sf::Vector2f screenSize = sf::Vector2f(window.getSize()),
				 margin(screenSize.x * 1/15, screenSize.y * 1/15),
				 cursorPos;
	sf::Text enterText("Enter", fnt, 55),
			 mesaText("Mesa", fnt, 55);
	sf::Texture corner, ringTex, shadowTex; // Texture object used to draw images (from files, etc.)
	sf::RenderTexture canvas; // Use this to have a buffer frame before drawing to screen

	canvas.create(screenSize.x, screenSize.y); // Makes the buffer same size as screen

	if(!corner.loadFromFile("assets/corner.png")) // Loads image file into Texture object
		std::cerr << "ERROR: Corner texture not found. Exiting...";
	
	if(!ringTex.loadFromFile("assets/ring.png"))
		std::cerr << "ERROR: Ring texture not found. Exiting...";

	if(!shadowTex.loadFromFile("assets/ringShadow.png"))
		std::cerr << "ERROR: Shadow texture not found. Exiting...";

	sf::Sprite topLeft(corner); // Location defaults to top left corner of render
	setSpriteOriginToCenter(topLeft); // Due to origin change will need to change position
	topLeft.setPosition(corner.getSize().x / 2 + margin.x,
						corner.getSize().y / 2 + margin.y);

	sf::Sprite topRight(corner); // Will need to adjust location and rotation
	setSpriteOriginToCenter(topRight);
	topRight.rotate(90);
	topRight.setPosition(screenSize.x - (corner.getSize().x / 2 + margin.x), 
							corner.getSize().y / 2 + margin.y);      
								// Sets location to screen width        
								// minus the width of the image,
								// and same for height and y axis.
								// Division by 2 to account for
								// centered origin
						
	sf::Sprite bottomRight(corner);
	setSpriteOriginToCenter(bottomRight);
	bottomRight.rotate(180);
	bottomRight.setPosition(screenSize.x - (corner.getSize().x / 2 + margin.x),
				screenSize.y - (corner.getSize().y / 2 + margin.y));
	
	sf::Sprite bottomLeft(corner);
	setSpriteOriginToCenter(bottomLeft);
	bottomLeft.rotate(270);
	bottomLeft.setPosition(corner.getSize().x / 2 + margin.x,
						   screenSize.y - (corner.getSize().y / 2 + margin.y));

	sf::Sprite ring(ringTex);
	setSpriteOriginToCenter(ring);
	ring.setPosition(sf::Vector2f(screenSize.x / 2.0f, screenSize.y / 2.0f));

	sf::Sprite shadow(shadowTex);
	setSpriteOriginToCenter(shadow);
	shadow.setPosition(sf::Vector2f(screenSize.x / 2.0f, screenSize.y / 2.0f));

	sf::FloatRect textSize = enterText.getLocalBounds();

	setTextOriginToCenter(enterText);
	enterText.setPosition(sf::Vector2f(screenSize.x / 2.0f,
									   screenSize.y / 2.0f - (textSize.height / 2 + 5)));

	setTextOriginToCenter(mesaText);
	mesaText.setPosition(sf::Vector2f(screenSize.x / 2.0f,
									   screenSize.y / 2.0f + (textSize.height / 2 + 5)));

	sf::Event mainEvent; // New event object for this 'screen'
	while(window.isOpen())
	{
		cursorPos = sf::Vector2f(sf::Mouse::getPosition(window));
		if(ring.getGlobalBounds().contains(cursorPos))
			ring.rotate(2);
		else
			ring.rotate(1);
		

		while(window.pollEvent(mainEvent))
		{
			if (mainEvent.type == sf::Event::Closed)
				window.close();

			if (mainEvent.type == sf::Event::Resized)
			{
				screenSize = sf::Vector2f(window.getSize()); // In case of window resize
				canvas.clear();
				canvas.create(screenSize.x, screenSize.y);
			}
		}

		canvas.clear();

		canvas.draw(topLeft);
		canvas.draw(topRight);
		canvas.draw(bottomLeft);
		canvas.draw(bottomRight);
		canvas.draw(ring);
		canvas.draw(shadow);
		canvas.draw(enterText);
		canvas.draw(mesaText);

		canvas.display();
		sf::Sprite tex(canvas.getTexture());

		window.clear(); // Needs to be cleared every frame
		
		window.draw(tex); // Draws the sprite to the RenderTexture
		
		window.display(); // Displays current window buffer on screen

	}
}

void setSpriteOriginToCenter(sf::Sprite& spr)
{
	/* In SFML, objects have an origin that act as the center of all transformations, such as
	 * rotation and position. The default value is the top left corner of said object
	 * (essetentially 0,0 in its local coordinate space). I find centering the origin
	 * makes transformations much easier thus this function.
	 */

	sf::FloatRect bounds = spr.getLocalBounds();

	spr.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
}

void setTextOriginToCenter(sf::Text& txt)
{
	/* In SFML, objects have an origin that act as the center of all transformations, such as
	 * rotation and position. The default value is the top left corner of said object
	 * (essetentially 0,0 in its local coordinate space). I find centering the origin
	 * makes transformations much easier thus this function.
	 */

	sf::FloatRect bounds = txt.getLocalBounds();

	txt.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
}