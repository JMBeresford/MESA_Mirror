#include <SFML/Graphics.hpp>
#include "../include/animatedObject.h"
#include <random>
#include <chrono>

AnimatedRect::AnimatedRect(const sf::Vector2f& size)
{
	setSize(size);
	fade = false;
	flicker = false;
}

int AnimatedRect::getOpacity()
{
	return opacity;
}

void AnimatedRect::setOpacity(int opacity)
{
	this->opacity = opacity;
}

void AnimatedRect::setOriginToCenter()
{
	sf::FloatRect temp = this->getLocalBounds();

	this->setOrigin(temp.left + temp.width / 2.0f,
			temp.top + temp.height / 2.0f);
}

void AnimatedRect::animate()
{
	if (!this->flicker)
	{
		unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
		std::mt19937 mt1(seed1 % 100 + 1);

		unsigned num = mt1();

		if (0 < num && num < 8) { this->flicker=true; }
	}
	else
		this->fade = true;

	if(this->fade)
	{
		if (this->opacity <= 0)
		{
			this->opacity = 255;
			this->flicker = false;
			this->fade = false;
		}
		else
		{
			this->opacity -= 5;
			if (this->opacity < 0) { this->opacity = 0; }
		}
	}
}
