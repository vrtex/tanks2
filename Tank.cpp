#include "Tank.h"


//----------------------TANK----------------------------------------

Tank::Tank(sf::RenderWindow *w, sf::Vector2f pos, float rotation, int index) :
	window(w), position(pos), rotation(rotation), index(index), 
	maxSpeed(5, 4), currentSpeed(0, 0)
{
	base.setTexture(res::getResources<sf::Texture>().get("Tank_base"));
	base.setOrigin((float)base.getTexture()->getSize().x / 2, (float)base.getTexture()->getSize().y / 2);
	setPosition(position);
	setDirection({0, 0});
}

double Tank::PI = acos(-1);

Tank::~Tank()
{
}

bool Tank::getInput(sf::Event & e)
{
	if(e.type == sf::Event::KeyPressed)
	{
		switch(e.key.code)
		{
		case sf::Keyboard::W:
			setDirection({maxSpeed.x, currentSpeed.y});
			return true;
		case sf::Keyboard::S:
			setDirection({-maxSpeed.x * 0.75f, currentSpeed.y});
			return true;
		case sf::Keyboard::A:
			setDirection({currentSpeed.x, -maxSpeed.y});
			return true;
		case sf::Keyboard::D:
			setDirection({currentSpeed.x, maxSpeed.y});
			return true;
		default:
			break;
		}
	}

	else if(e.type == sf::Event::KeyReleased)
	{
		switch(e.key.code)
		{
		case sf::Keyboard::W:
			if(!sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				setDirection({0, currentSpeed.y});
			return true;
		case sf::Keyboard::S:
			if(!sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				setDirection({0, currentSpeed.y});
		case sf::Keyboard::A:
			setDirection({currentSpeed.x, 0});
			return true;
		case sf::Keyboard::D:
			setDirection({currentSpeed.x, 0});
			return true;
		default:
			break;
		}
	}
	return false;
}

void Tank::update()
{
	setPosition(position + currentDirection);
}

void Tank::draw()
{
	window->draw(base);
}

void Tank::setPosition(sf::Vector2f &pos)
{
	rotation += currentSpeed.y;
	if(currentSpeed.y != 0) setDirection(currentSpeed);
	base.setRotation(rotation);
	base.setPosition(position = pos);
}

void Tank::setDirection(sf::Vector2f newSpeed)
{
	//base.setRotation(rotation);
	currentSpeed = newSpeed;
	currentDirection.x = static_cast<float>(cos(rotation * PI / 180)) * currentSpeed.x;
	currentDirection.y = static_cast<float>(sin(rotation * PI / 180)) * currentSpeed.x;
}
