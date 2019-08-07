#include <SFML/Graphics.hpp>
#include <iostream>
#include "src/splashScreen.hpp"

void splashScreen(sf::RenderWindow&);
void setSpriteOriginToCenter(sf::Sprite&);
void setTextOriginToCenter(sf::Text&);

int main()
{
	sf::RenderWindow window(sf::VideoMode(800,600), "Mesa Mirror", sf::Style::Default);
	
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
	
		splashScreen(window);
	}
	return 0;
}

void splashScreen(sf::RenderWindow& window)
{
	Screen Corners(window);
	SplashScreen Splash(window);
	sf::Vector2f cursorPos;

	sf::Event mainEvent; // New event object for this 'screen'
	while(window.isOpen())
	{
		cursorPos = sf::Vector2f(sf::Mouse::getPosition(window));
		if(Splash.getRingPos().contains(cursorPos))
			Splash.rotateRing(2);
		else
			Splash.rotateRing(1);
		

		while(window.pollEvent(mainEvent))
		{
			if (mainEvent.type == sf::Event::Closed)
				window.close();

			if (mainEvent.type == sf::Event::Resized)
			{
				sf::Vector2f screenSize = sf::Vector2f(window.getSize()); // In case of window resize
				Corners.clear();
				Corners.create(screenSize.x, screenSize.y);
			}
		}

		Corners.clear();
		Splash.clear(sf::Color::Transparent);

		Corners.animate();

		Corners.drawCorners();
		Splash.drawRing();

		Corners.display();
		Splash.display();

		sf::Sprite cornerTex(Corners.getTexture());
		sf::Sprite splashTex(Splash.getTexture());
		window.clear(); // Needs to be cleared every frame
		
		window.draw(cornerTex); // Draws the sprite to the RenderTexture
		window.draw(splashTex);

		window.display(); // Displays current window buffer on screen
	}
}

