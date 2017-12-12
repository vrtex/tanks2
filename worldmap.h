#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <vector>
#include <fstream>
class WorldMap
{
public:
	WorldMap(std::string obstacles);
	~WorldMap();
private:
	std::vector<sf::ConvexShape> obstacles;
};

