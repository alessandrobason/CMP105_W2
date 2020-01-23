#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	ismouseldown = false;
	mouserpressed = false;

	newmouse = {};
	oldmouse = {};

	circle.setRadius(50);
	circle.setOrigin(sf::Vector2f(50, 50));
	//circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineColor(sf::Color::White);

	// initialise game objects
	if (!font.loadFromFile("font/arial.ttf")) {
		std::cout << "Couldn't load font from file\n";
	}

	text.setFont(font);
	text.setString("Hello world");
	text.setCharacterSize(24);
	text.setPosition(sf::Vector2f(0, 0));
}

Level::~Level()
{
	input = nullptr;
}

// handle user input
void Level::handleInput()
{
	if (input->isKeyDown(sf::Keyboard::W)) {
		std::cout << "Key w is pressed\n";
	}
	if (input->isKeyDown(sf::Keyboard::J) && input->isKeyDown(sf::Keyboard::K) && input->isKeyDown(sf::Keyboard::L)) {
		std::cout << "Keys j k l are all pressed at the same time\n";
	}
	if (input->isKeyDown(sf::Keyboard::Escape)) {
		window->close();
	}
	// mouseL is down
	if (input->isMouseLDown()) {
		newmouse.x = input->getMouseX();
		newmouse.y = input->getMouseY();
		ismouseldown = true;
	}
	// mouseL was just released
	else if (ismouseldown) {
		double d = std::pow(newmouse.x - oldmouse.x, 2) + std::pow(newmouse.y - oldmouse.y, 2);
		d = std::sqrt(d);
		std::cout << d << "\n";
		ismouseldown = false;
	}
	// mouseL is up
	else {
		oldmouse.x = input->getMouseX();
		oldmouse.y = input->getMouseY();
	}

	if (input->isMouseRDown() && !mouserpressed) {
		mouserpressed = true;
		circle.setPosition(sf::Vector2f(input->getMouseX(), input->getMouseY()));
	}
	else if(!input->isMouseRDown()) {
		mouserpressed = false;
	}
}

// Update game objects
void Level::update()
{
	text.setString(std::to_string(input->getMouseX()) + " " + std::to_string(input->getMouseY()));
	if (ismouseldown) {
		line[0].position = sf::Vector2f(oldmouse.x, oldmouse.y);
		line[1].position = sf::Vector2f(newmouse.x, newmouse.y);
	}
}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(text);
	if (ismouseldown) {
		window->draw(line, 2, sf::Lines);
	}
	window->draw(circle);
	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}