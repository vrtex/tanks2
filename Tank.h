#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <cmath>
#include "resourcemanager.h"

class Tank
{
private:
	class Turret
	{
	public:
		Turret(sf::RenderWindow *w, sf::Vector2f position, int baseRotation);
		~Turret();
		bool getInput(sf::Event &e);
		void draw();
		void setPosition(sf::Vector2f pos);
		void setRotation(int newRot);
	private:
		sf::RenderWindow *window;
		sf::Vector2f position;
		int rotation;
		sf::Sprite gun;
		int lean;
	};
public:
	Tank(sf::RenderWindow *w, sf::Vector2f pos, float rotation, int index);
	~Tank();
	bool getInput(sf::Event &e);
	void update();
	void draw();
private:
	void setPosition(sf::Vector2f &pos);
	void setDirection(sf::Vector2f newSpeed);
	sf::RenderWindow *window;
	sf::Vector2f position;
	float rotation;
	int index;
	const sf::Vector2f maxSpeed;
	sf::Vector2f currentSpeed; //x for movespeed, y for rotspeed
	sf::Sprite base;

	static double PI;
	sf::Vector2f currentDirection;
	std::vector<Tank *> seenTanks;
	//Tank::Turret gun;
};

