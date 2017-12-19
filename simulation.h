#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>
#include <list>
#include "resourcemanager.h"
#include "connections.h"
class Simulation
{
private:
	class SObstacle
	{
	public:
		SObstacle();
		~SObstacle();
		sf::ConvexShape shape;
	};

	class STank
	{
	private:
		struct STurret
		{
			STurret();
			~STurret();
			int rotation;
			int lean;
		};
	public:
		STank(TankInfo starting);
		STank(float startingX, float startingY, int index);
		~STank();
		bool getInput(sf::Event &e);
		void draw(sf::RenderWindow *w);
		bool collidesWith(Simulation::STank &other);
	// private:
		sf::Vector2f position;
		int rotation;
		int index;

		int radius;
	};
public:
	Simulation(sf::RenderWindow *w, int players);
	~Simulation();
	bool getInput(sf::Event &e);
	bool update();
	void draw();
	void addTank(TankInfo starting);
private:
	sf::RenderWindow *window;
	std::list<STank> tanks;
	res::ResourceManager<sf::Texture> &textures;
	sf::Sprite background;
	sf::Vector2u gameBounds;
	sf::Text ui;
};
