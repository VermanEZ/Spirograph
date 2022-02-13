#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
using namespace sf;

const float PI = 3.14159265;

class Game
{
private:
	RenderWindow* window;
	VideoMode videoMode;
	int framerate;
	Event event;
	// Colors
	Color armsColor;
	Color linesColor;
	Color circlesColor;
	// Objects
	int numberOfArms;
	VertexArray arms;
	VertexArray lines;
	std::vector<CircleShape*> circles;
	bool showCircles;
	std::vector<float> length_of_arms;
	std::vector<float> speed_of_arms;
	std::vector<float> current_angles;
	// Private functions
	void initVars();
	void initWindow();
	void initSpirograph();
	void useKeyboard();
	void useConfig();
	void input();
public:
	// Constructors & Destructors
	Game();
	virtual ~Game();

	// Accessors
	bool running() const;

	// Functions
	void pollEvents();
	void updateSpirograph();
	void update();
	void renderSpirograph();
	void render();
};

