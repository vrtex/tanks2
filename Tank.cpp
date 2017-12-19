#include "Tank.h"
#include "simulation.h"

//------------------------TURRET--------------------------

Tank::Turret::Turret(sf::RenderWindow *w, sf::Vector2f position, int baseRotation) :
	window(w), position(position), baseRotation(baseRotation), rotation(0),
	rotateSpeed(2), currentSpeed(0)
{
	gun.setTexture(res::getResources<sf::Texture>().get("Tank_turret"));
	gun.setOrigin(20 , gun.getTexture()->getSize().y / 2);
	gun.setPosition(position);
	gun.rotate(baseRotation);
}

Tank::Turret::~Turret()
{
}

bool Tank::Turret::getInput(sf::Event &e)
{
	if(e.type == sf::Event::KeyPressed)
	{
		switch(e.key.code)
		{
		case sf::Keyboard::Q:
			currentSpeed = -rotateSpeed;
			return true;
		case sf::Keyboard::E:
			currentSpeed = rotateSpeed;
			return true;
		default:
			break;
		}
	}

	else if(e.type == sf::Event::KeyReleased)
	{
		switch(e.key.code)
		{
		case sf::Keyboard::Q:
			if(!sf::Keyboard::isKeyPressed(sf::Keyboard::E))
				currentSpeed = 0;
			return true;
		case sf::Keyboard::E:
			if(!sf::Keyboard::isKeyPressed(sf::Keyboard::E))
				currentSpeed = 0;
			return true;
		default:
			break;
		}
	}

	return false;
}

void Tank::Turret::update()
{
	if(currentSpeed != 0) rotate();
}


void Tank::Turret::draw()
{
	window->draw(gun);
}

void Tank::Turret::setPosition(const sf::Vector2f &pos)
{
	gun.setPosition(pos);
}

void Tank::Turret::setRotation(int newRot)
{
	baseRotation = newRot;
	gun.setRotation(baseRotation + rotation);
}

void Tank::Turret::rotate()
{
	rotation += currentSpeed;
	if(rotation < -90)
	{
		rotation = -90;
		return;
	}
	if(rotation > 90)
	{
		rotation = 90;
		return;
	}
	gun.rotate(currentSpeed);
}


//----------------------TANK----------------------------------------

Tank::Tank(sf::RenderWindow *w, sf::Vector2f pos, float rotation, int index) :
	window(w), position(pos), rotation(rotation), index(index),
	maxSpeed(5, 4), currentSpeed(0, 0),
	gun(window, position, rotation), parent(nullptr)
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

	if(e.type == sf::Event::KeyReleased)
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
			return true;
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

	if(gun.getInput(e)) return true;
	return false;
}

void Tank::update()
{
	setPosition(position + currentDirection);
	gun.update();
}

void Tank::draw()
{
	window->draw(base);
	gun.draw();
}

void Tank::connect(Simulation *s)
{
	parent = s;
	TankInfo startup =
	{
		index,
		position,
		rotation,
		0, 0
	};
	parent->addTank(startup);
}

void Tank::setPosition(const sf::Vector2f &pos)
{
	rotation += currentSpeed.y;
	if(currentSpeed.y != 0)
	{
		setDirection(currentSpeed);
		gun.setRotation(rotation);
	}
	base.setRotation(rotation);
	base.setPosition(position = pos);
	gun.setPosition(pos);
}

void Tank::setDirection(const sf::Vector2f &newSpeed)
{
	//base.setRotation(rotation);
	currentSpeed = newSpeed;
	currentDirection.x = static_cast<float>(cos(rotation * PI / 180)) * currentSpeed.x;
	currentDirection.y = static_cast<float>(sin(rotation * PI / 180)) * currentSpeed.x;
}
