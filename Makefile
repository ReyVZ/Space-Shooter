all:
	g++ main.cpp entity.cpp player.cpp stone.cpp explosion.cpp laser.cpp -o app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -std=c++11