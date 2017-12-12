#pragma once
#include <SFML\Graphics.hpp>
#include <list>
#include "resourcemanager.h"
class Simulation
{
private:
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
		STank(float startingX, float startingY, int index);
		~STank();
		bool getInput(sf::Event &e);
		void draw(sf::RenderWindow *w);
	private:
		sf::Vector2f position;
		int rotation;
		int index;
	};
public:
	Simulation(sf::RenderWindow *w, int players);
	~Simulation();
	bool getInput(sf::Event &e);
	bool update();
	void draw();
private:
	sf::RenderWindow *window;
	std::list<STank> tanks;
	res::ResourceManager<sf::Texture> &textures;
	sf::Sprite background;
};

