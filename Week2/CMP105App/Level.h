#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <math.h>
#include "Framework/Input.h"


class Level{
public:
	Level(sf::RenderWindow* hwnd, Input* in);
	~Level();

	void handleInput();
	void update();
	void render();

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;

	sf::Font font;
	sf::Text text;

	struct mouseinput {
		int x;
		int y;
	};

	mouseinput oldmouse;
	mouseinput newmouse;
	bool  ismouseldown;
	bool  mouserpressed;

	sf::Vertex line[2];
	sf::CircleShape circle;

	// Add your object here

};