#include <SFML/Graphics.hpp>
#include "../include/animatedSprite.h"
#include <random>
#include <iostream>
#include <chrono>

AnimatedSprite::AnimatedSprite()
{
	srand(time(NULL));
	this->fade = false;
	this->flicker = false;
	for(size_t i = 0; i < sizeof(this->patricksIdea); i++)
		this->patricksIdea[i] = rand() % 30 + 1;

}

AnimatedSprite::AnimatedSprite(const sf::Texture &tex)
{
	srand(time(NULL));
	this->setTexture(tex);
	this->t = tex;
	this->fade = false;
	this->flicker = false;
	for(size_t i = 0; i < sizeof(this->patricksIdea); i++)
		this->patricksIdea[i] = rand() % 30 + 1;

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
		int num = (rand() + int(this->getPosition().x) + int(this->getPosition().y)) % 100 + 1;
		//std::cout << "num is: " << num;
		if (0 < num && num < 8) { this->flicker=true; }
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
			this->setColor(old - sf::Color(0,0,0,25));
			std::cout << this->getColor().toInteger() << std::endl;
		}
		
	}
}
