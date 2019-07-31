#include <SFML/Graphics.hpp>
#include "../include/animatedSprite.h"
#include <random>
#include <iostream>
#include <chrono>

AnimatedSprite::AnimatedSprite(const sf::Texture &tex, unsigned index)
{
	srand(this->patricksIdea[index]);
	this->setTexture(tex);
	this->t = tex;
	this->flicker = false;
	this->index = index;
	for(size_t i = 0; i < sizeof(this->patricksIdea)/sizeof(this->patricksIdea[0]); i++)
		this->patricksIdea[i] = (rand() % 30) + 6;
}

void AnimatedSprite::animate()
{
	if(this->timer.getElapsedTime().asSeconds() > this->patricksIdea[this->index])
		this->flicker = true;

	if(flicker)
	{
		if (this->getColor().toInteger() <= 4294967040) // Checks for full transparency to end the animation
		{
			this->setColor(sf::Color(this->getColor()+sf::Color(0,0,0,255)));
			//this->setTexture(this->t);
			this->flicker = false;
			this->index = rand() % 10;
			for(size_t i = 0; i < sizeof(this->patricksIdea)/sizeof(this->patricksIdea[0]); i++)
				this->patricksIdea[i] = (rand() % 25) + 6;
			this->timer.restart();
		}
		else
		{
			sf::Color old = this->getColor();
			this->setColor(old - sf::Color(0,0,0,25));
		}
	}
}
