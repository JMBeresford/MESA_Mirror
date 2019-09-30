#include <SFML/Graphics.hpp>
#include <iostream>
#include <experimental/filesystem>
#include "screen.h"
#include "splashScreen.h"
#include "clubList.h"
#include "signUpForm.h"

namespace fs = std::experimental::filesystem;

void splashScreen(sf::RenderWindow&);
void clubListScreen(sf::RenderWindow&);
void signUpFormScreen(sf::RenderWindow&, Club&);

int main()
{
	sf::RenderWindow window(sf::VideoMode(800,600), "Mesa Mirror", sf::Style::Default);

	while(window.isOpen()) // This is a loop for the program window to live in, each iter a frame
	{
		window.setFramerateLimit(60); // Limits framerate to 60

	/*	
	It is highly encouraged to read through the documentation for SFML events
	before attempting anything significant here. The event system is integral to
	the operation of an SFML window and the documentation on their website will prove
	quite insightful.
	*/

		sf::Event mirrorEvent; // This is the event object that all SFML events will be
		while(window.pollEvent(mirrorEvent)) // appended to, and the loop that iterates
		{				     // through them.

			if(mirrorEvent.type == sf::Event::Closed) // Terminates the outer
				window.close();			  // while loop when window is closed
		}
	
		splashScreen(window); // Call to the splashScreen function, passing it the window
	}
	return 0;
}

void splashScreen(sf::RenderWindow& window)
{
	Screen Corners(window); // Class used to draw the corner images
	SplashScreen Splash(window); // Class used to draw the splash screen ('enter mesa' ring)
	/*
	sf::Vectors are essentially pairs of values, and are objects provided by SFML
	Vector2fs contain 'floats', Vector2i 'ints' and Vector2u 'unsigned ints'
	These pairs can be indexed with .x and .y
	
	EXAMPLE: given a sf::Vector2i, named "coordinates", with values (4,5),
	printing coordinates.x to console will print 4, and coordinates.y will print 5.
	*/
	sf::Vector2f cursorPos, screenSize(sf::Vector2f(window.getSize()));

	sf::Event mainEvent; // New event object for this 'screen'
	while(window.isOpen())
	{
		// Updates location of mouse every frame
		cursorPos = sf::Vector2f(sf::Mouse::getPosition(window));

		// The ring will rotate 2 degrees per frame if the mouse is over it, else 1 per frame
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
				// In case of window resize
				sf::Vector2f screenSize = sf::Vector2f(window.getSize());
			}

			if (mainEvent.type == sf::Event::KeyPressed)
			{
				// Checks for alt+f4 and quits is pressed
				if (mainEvent.key.code == sf::Keyboard::F4)
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
						window.close();
			}

			if (mainEvent.type == sf::Event::MouseButtonPressed)
			{
				if (mainEvent.mouseButton.button == sf::Mouse::Left && Splash.getRingPos().contains(cursorPos))
				{
					clubListScreen(window);
					return;
				}
			}
		}

		// RenderTextures need to be cleared/updated/redrawn every frame
		// we give it a transparent color for the clear so that every texture can be
		// seen layered on top of each other
		Corners.clear(sf::Color::Transparent);
		Splash.clear(sf::Color::Transparent);

		Corners.animate(); // Check the animatedSprite source in the src folder
		Splash.doTime(screenSize); // Sets clock

		Splash.drawAll(); // Check relevant source files
		Corners.drawCorners();

		Corners.display(); // Makes the things drawn to the texture 'visable'
		Splash.display();

		sf::Sprite cornerTex(Corners.getTexture()); // Creates sprites of each texture
		sf::Sprite splashTex(Splash.getTexture());  // in prep for drawing to screen

		window.clear(); // Needs to be cleared every frame (defaults to black)
		
		window.draw(cornerTex); // Draws the sprites to the RenderWindow
		window.draw(splashTex);

		window.display(); // Displays current window buffer on screen
	}
}

void clubListScreen(sf::RenderWindow& window)
{
	Screen Corners(window);
	sf::Vector2f cursorPos, screenSize(sf::Vector2f(window.getSize()));

	sf::Event clubListEvent;
	ClubList CList(window);
	while (window.isOpen())
	{
		cursorPos = sf::Vector2f(sf::Mouse::getPosition(window));

		while (window.pollEvent(clubListEvent))
		{
			if (clubListEvent.type == sf::Event::MouseButtonReleased)
				if (clubListEvent.mouseButton.button == sf::Mouse::Left)
					for (unsigned i = 0; i < CList.size(); i++)
						if (CList.getTexts()[i].getLocalBounds().contains(cursorPos))
							signUpFormScreen(window, CList.getClub(i));
		}
		
		Corners.clear(sf::Color::Transparent);
		Corners.animate();
		Corners.drawCorners();
		Corners.display();

		CList.clear(sf::Color::Transparent);
		CList.drawClubs();
		CList.display();

		sf::Sprite cornerTex(Corners.getTexture());
		sf::Sprite clubsTex(CList.getTexture());

		window.clear();
		window.draw(cornerTex);
		window.draw(clubsTex);
		window.display();
	}

}

void signUpFormScreen(sf::RenderWindow& window, Club& _club)
{
	Screen corners(window);
	SignUpForm signUp(window, _club);

	sf::Event signUpEvent;
	while(window.isOpen())
	{
		while(window.pollEvent(signUpEvent))
		{

		}

	corners.clear(sf::Color::Transparent);
	corners.animate();
	corners.drawCorners();
	corners.display();

	signUp.clear(sf::Color::Transparent);
	signUp.drawElements();
	signUp.display();

	sf::Sprite cornerSpr(corners.getTexture());
	sf::Sprite signUpSpr(signUp.getTexture());

	window.clear();
	window.draw(cornerSpr);
	window.draw(signUpSpr);

	}
}