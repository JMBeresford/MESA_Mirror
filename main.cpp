#include <SFML/Graphics.hpp>
#include <iostream>
#include <experimental/filesystem>
#include <fstream>
#include "nlohmann/json.hpp"
#include "screen.h"
#include "splashScreen.h"
#include "clubList.h"
#include "signUpForm.h"
using nlohmann::json;

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
	std::vector<sf::Text> _text = CList.getTexts();
	sf::Cursor cur;

	while (window.isOpen())
	{
		cursorPos = sf::Vector2f(sf::Mouse::getPosition(window));

		if (CList.hovering(cursorPos))
		{
			cur.loadFromSystem(sf::Cursor::Hand);
			window.setMouseCursor(cur);
		}
		else
		{
			cur.loadFromSystem(sf::Cursor::Arrow);
			window.setMouseCursor(cur);
		}

		while (window.pollEvent(clubListEvent))
		{
			if (clubListEvent.type == sf::Event::MouseButtonPressed)
				if (clubListEvent.mouseButton.button == sf::Mouse::Left)
					for (size_t i = 0; i < _text.size(); i++)
						if (_text[i].getGlobalBounds().contains(cursorPos))
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
	sf::Vector2f screenSize = sf::Vector2f(window.getSize());
	sf::Font font;
	font.loadFromFile("assets/font.ttf");
	Screen corners(window);
	SignUpForm signUp(window, _club);
	sf::Vector2i cursorPos;
	sf::Event signUpEvent;
	sf::Cursor cur;
	std::vector<sf::Text> _texts(4);
	bool typing = false;
	int selection = 0;

	sf::FloatRect pos = signUp.submit.getGlobalBounds();

	for (size_t i = 0; i < _texts.size(); i++)
	{
		signUp.setTextOriginToCenter(_texts[i]);
		_texts[i].setFont(font);
		_texts[i].setCharacterSize(25);
		_texts[i].setPosition(signUp.textBoxes[i].getPosition().x, signUp.textBoxes[i].getPosition().y - 5);
		_texts[i].setFillColor(sf::Color::Black);
	}

	while(window.isOpen())
	{
		cursorPos = sf::Mouse::getPosition(window);
		if (pos.contains(cursorPos.x,cursorPos.y))
			signUp.submit.setFillColor(sf::Color::White);
		else
			signUp.submit.setFillColor(sf::Color(150,150,150,255));

		if (signUp.hovering(sf::Vector2f(cursorPos)))
		{
			cur.loadFromSystem(sf::Cursor::Hand);
			window.setMouseCursor(cur);
		}
		else
		{
			cur.loadFromSystem(sf::Cursor::Arrow);
			window.setMouseCursor(cur);
		}
		
		while(window.pollEvent(signUpEvent))
		{
			if (signUpEvent.type == sf::Event::MouseButtonPressed)
			{
				cursorPos = sf::Mouse::getPosition(window);
				std::cout << "clicked" << std::endl;
				if (signUpEvent.mouseButton.button == sf::Mouse::Left)
				{
					if (signUp.textBoxes[0].getGlobalBounds().contains(cursorPos.x, cursorPos.y))
					{
						signUp.activateText(0);
						typing = true;
						selection = 0;
						std::cout << "clicked box 0" << std::endl;
					}
					else if (signUp.textBoxes[1].getGlobalBounds().contains(cursorPos.x, cursorPos.y))
					{
						signUp.activateText(1);
						typing = true;
						selection = 1;
						std::cout << "clicked box 1" << std::endl;
					}
					else if (signUp.textBoxes[2].getGlobalBounds().contains(cursorPos.x, cursorPos.y))
					{
						signUp.activateText(2);
						typing = true;
						selection = 2;
						std::cout << "clicked box 2" << std::endl;
					}
					else if (signUp.textBoxes[3].getGlobalBounds().contains(cursorPos.x, cursorPos.y))
					{
						signUp.activateText(3);
						typing = true;
						selection = 3;
						std::cout << "clicked box 3" << std::endl;
					}
					else if (pos.contains(cursorPos.x, cursorPos.y))
					{
						Member m(	signUp.textBoxes[0].str,signUp.textBoxes[1].str,
									signUp.textBoxes[2].str,signUp.textBoxes[3].str);
						signUp.submitMember(m);
						return;
					}
					else
					{
						signUp.deactivate();
						typing = false;
					}
				}
			}
		
			if (signUpEvent.type == sf::Event::TextEntered && typing)
			{
				if (signUpEvent.text.unicode < 128 && signUpEvent.text.unicode > 31)
				{
					std::cout << "typing..." << std::endl;
					
					if (signUp.textBoxes[selection].active)
					{
						std::cout << "typed" << std::endl;
						signUp.textBoxes[selection].str += static_cast<char>(signUpEvent.text.unicode);
						_texts[selection].setString(signUp.textBoxes[selection].str);
						}
				}
				if (signUpEvent.text.unicode == 8 && typing)
				{
					if (signUp.textBoxes[selection].active && !signUp.textBoxes[selection].str.empty())
					{
						signUp.textBoxes[selection].str.pop_back();
						_texts[selection].setString(signUp.textBoxes[selection].str);
					}
				}
				if (signUpEvent.text.unicode == 9 && typing)
				{
					selection++;
					if (selection > 3)
						selection = 0;

					signUp.activateText(selection);
				}
			}
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

		window.clear(sf::Color::Transparent);
		window.draw(cornerSpr);
		window.draw(signUpSpr);
		for (auto i : _texts)
			window.draw(i);
		window.display();
	}
}