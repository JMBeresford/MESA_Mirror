#include <SFML/Graphics.hpp>
#include "animatedSprite.h"
#include <random>
#include <iostream>
#include <chrono>

AnimatedSprite::AnimatedSprite(const sf::Texture &tex, unsigned index)
{
	srand(index + 1); // Seeds the random num generator
	for(size_t i = 0; i < 10; i++)
		this->patricksIdea[i] = (rand() % 25) + 5;
		// array of random nums 5-30 to be used as intervals for animation

	this->setTexture(tex); // sets the sprites texture to the corner image
	this->flicker = false; // flag used for animation
	this->index = index; // used to index the above array
}

void AnimatedSprite::animate()
{
	/*
	When this class is instantiazted, the sf::Clock object immediately begins counting
	(in system time, thus milli- or nano-seconds depending on your system). Once this
	timer passes the interval we have indexed from the array of random nums (5-30),
	we trigger the animation with the 'flicker' boolean. Then we reduce the opacity
	of the sprite -- read the docs on sf::Color objects in SFML's api reference for more
	info on this -- by 17 (a factor of 255, the max and default opacity) until opacity
	hits zero. We check for this in the nested if statement which, when executed, resets
	the object for another random interval to trigger another animation
	*/
	if(this->timer.getElapsedTime().asSeconds() > this->patricksIdea[this->index])
	{
		this->flicker = true;
	}

	if(flicker)
	{
		if (this->getColor() == sf::Color(255,255,255,0)) // Checks for full transparency to end the animation
		{
			this->setColor(this->getColor() + sf::Color(0,0,0,255));
			this->flicker = false;
			srand(this->patricksIdea[index]);
			this->index = rand() % 10;
			for(size_t i = 0; i < 10; i++)
				this->patricksIdea[i] = (rand() % 25) + 5;
				
			this->timer.restart();
		}
		else
		{
			this->setColor(this->getColor() - sf::Color(0,0,0,17));
		}
	}
}