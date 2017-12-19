#include "simulation.h"



//---------------------------SOBSTACLE--------------------------------

Simulation::SObstacle::SObstacle()
{

}

Simulation::SObstacle::~SObstacle()
{

}


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

Simulation::STank::STank(TankInfo starting) :
	position(starting.position), rotation(starting.rotation), index(starting.index)
{
	res::ResourceManager<sf::Texture> &textures(res::getResources<sf::Texture>());

	int w = textures.get("Tank_base").getSize().x / 2;
	w *= w;
	int h = textures.get("Tank_base").getSize().y / 2;
	h *= h;

	radius = sqrt(w + h);
}




// Simulation::STank::STank(float startingX, float startingY, int index)
// {
// 	res::ResourceManager<sf::Texture> &textures(res::getResources<sf::Texture>());
// 	position = {startingX, startingY};
// 	rotation = 0;
// 	this->index = index;
//
// 	int w = textures.get("Tank_base").getSize().x / 2;
// 	w *= w;
// 	int h = textures.get("Tank_base").getSize().y / 2;
// 	h *= h;
//
// 	radius = sqrt(w + h);
// 	std::cout << radius << "\n";
// }


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

bool Simulation::STank::collidesWith(Simulation::STank &other)
{
	sf::Vector2f difference = position - other.position;
	float lel = sqrt(difference.x * difference.x + difference.y * difference.y);
	if(lel < radius + other.radius) return true;
	return false;
}


//--------------------------------SIMULATION---------------------------

Simulation::Simulation(sf::RenderWindow *w, int players) :
	window(w), textures(res::getResources<sf::Texture>())
{
	res::ResourceManager<sf::Font> &fonts(res::getResources<sf::Font>());
	textures.addContent("background", "Res/backgound.png");
	background.setTexture(textures.get("background"));
	unsigned int width = textures.get("background").getSize().x;
	unsigned int height = textures.get("background").getSize().y;
	window->create(sf::VideoMode(width + 200, height), "Tanks");
	window->setFramerateLimit(60);
	background.setPosition(0, 0);


	textures.addContent("Tank_base", "Res/coon_base_small_small.png");
	textures.addContent("Tank_turret", "Res/turret_small_small.png");

	gameBounds = {width, height};

	fonts.addContent("ui_font", "Res/font.otf");
	ui.setFont(fonts.get("ui_font"));
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

bool Simulation::update()
{
	return false;
}

void Simulation::draw()
{
	std::string s = "";
	window->draw(background);
	for(auto &t : tanks)
		s += std::to_string((int)t.position.x) + "\t" + std::to_string((int)t.position.y);
	ui.setString(s);
	window->draw(ui);
}

void Simulation::addTank(TankInfo starting)
{
	tanks.emplace_back(starting);
}
