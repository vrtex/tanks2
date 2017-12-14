tanks: main.o simulation.o Tank.o worldmap.o
	g++ main.o simulation.o Tank.o worldmap.o -o tanks -lsfml-graphics -lsfml-window -lsfml-system -std=c++11
simulation.o: simulation.cpp
	g++ -c simulation.cpp -std=c++11
Tank.o: Tank.cpp
	g++ -c Tank.cpp -std=c++11
worldmap.o: worldmap.cpp
	g++ -c worldmap.cpp -std=c++11
clean:
	-rm *.o
	-rm tanks
