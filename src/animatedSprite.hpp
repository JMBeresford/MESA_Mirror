#include <SFML/Graphics.hpp>
#include "../include/animatedSprite.h"
#include <random>
#include <iostream>
#include <chrono>

AnimatedSprite::AnimatedSprite()
{
	this->fade = false;
	this->flicker = false;
}

AnimatedSprite::AnimatedSprite(const sf::Texture &tex)
{
	this->setTexture(tex);
	this->fade = false;
	this->flicker = false;
}

int AnimatedSprite::getOpacity()
{
	return this->opacity;
}

void AnimatedSprite::setOpacity(int opacity)
{
	this->opacity = opacity;
}

void AnimatedSprite::setOriginToCenter()
{
	sf::FloatRect temp = this->getLocalBounds();

	this->setOrigin(temp.left + temp.width / 2.0f,
			temp.top + temp.height / 2.0f);
}

void AnimatedSprite::animate()
{
	if (!this->flicker)
	{
		srand(time(NULL));
		int num = rand() % 100 + 1;
		//std::cout << "num is: " << num;
		if (0 < num && num < 20) { this->flicker=true; }
	}
	else
		this->fade = true;

	if(this->fade)
	{
		if (this->getColor().toInteger() <= 4294967040)
		{
			this->setColor(sf::Color(this->getColor()+sf::Color(0,0,0,255)));
			this->opacity = 0;
			this->setTexture(this->t);
			this->flicker = false;
			this->fade = false;
		}
		else
		{
			sf::Color old = this->getColor();
			this->setColor(old - sf::Color(0,0,0,5));
			std::cout << this->getColor().toInteger() << std::endl;
		}
		
	}
}
