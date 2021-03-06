#include "simulation.h"
#include "Tank.h"


int main()
{
	sf::RenderWindow window;
	window.setFramerateLimit(60);
	Simulation test(&window, 2);
	Tank hurr(&window, {100, 200}, 20, 0);
	hurr.connect(&test);
	sf::Event e;
	while(window.isOpen())
	{
		while(window.pollEvent(e))
		{
			if(e.type == sf::Event::Closed)
				window.close();
			if(test.getInput(e)) continue;
			if(hurr.getInput(e)) continue;
		}
		test.update();
		hurr.update();
		window.clear();
		test.draw();
		hurr.draw();
		window.display();
	}
	return 42;
}
