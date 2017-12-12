#include "simulation.h"


//-------------------------STURRET---------------------------------

Simulation::STank::STurret::STurret()
{
	rotation = 0;
	lean = 0;
}


Simulation::STank::STurret::~STurret()
{
}




//--------------------------------STANK------------------------------

Simulation::STank::STank(float startingX, float startingY, int index)
{
	res::ResourceManager<sf::Texture> &textures(res::getResources<sf::Texture>());
	position = {startingX, startingY};
	rotation = 0;
	this->index = index;
}


Simulation::STank::~STank()
{
}

bool Simulation::STank::getInput(sf::Event & e)
{
	return false;
}

void Simulation::STank::draw(sf::RenderWindow * w)
{
}

//--------------------------------SIMULATION---------------------------

Simulation::Simulation(sf::RenderWindow *w, int players) :
	window(w), textures(res::getResources<sf::Texture>())
{
	textures.addContent("background", "Res/backgound.png");
	background.setTexture(textures.get("background"));
	unsigned int width = textures.get("background").getSize().x;
	unsigned int height = textures.get("background").getSize().y;
	window->create(sf::VideoMode(width, height), "Tanks");
	window->setFramerateLimit(60);
	background.setPosition(0, 0);


	textures.addContent("Tank_base", "Res/coon_base_small_small.png");
	textures.addContent("Tank_turret", "Res/turret_small_small.png");
}


Simulation::~Simulation()
{
	textures.deleteContent("background");
	textures.deleteContent("Tank_base");
	textures.deleteContent("Tank_turret");
}

bool Simulation::getInput(sf::Event & e)
{
	for(STank & t : tanks)
		if(t.getInput(e)) return true;

	return false;
}

void Simulation::draw()
{
	window->draw(background);
}
