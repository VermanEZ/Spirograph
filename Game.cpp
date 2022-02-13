#include "Game.h"


// Initialization
void Game::initVars()
{
	this->window = nullptr;
}

void Game::input()
{
	std::cout << "Enter the number of arms: ";
	std::cin >> this->numberOfArms;
	for (int i = 1; i <= this->numberOfArms; i++) {
		std::cout << "Enter the length (pixels) of arm " << i << " : ";
		float in;
		std::cin >> in;
		this->length_of_arms.push_back(in);
	}
	for (int i = 1; i <= this->numberOfArms; i++) {
		std::cout << "Enter the speed (deg/s) of arm " << i << " : ";
		float in;
		std::cin >> in;
		in = in * PI / 180;
		this->speed_of_arms.push_back(in);
	}
}

void Game::initWindow()
{
	this->framerate = 60;
	this->videoMode.width = 1500;
	this->videoMode.height = 800;
	this->window = new RenderWindow(this->videoMode, "Spirograph", Style::Titlebar | Style::Close);
	this->window->setFramerateLimit(this->framerate);
}

void Game::initSpirograph()
{
	// Init colors
	this->armsColor = Color::Green;
	this->linesColor = Color::White;
	this->circlesColor = Color::Blue;
	// Init angles vector
	for (int i = 0; i < this->numberOfArms; i++) {
		this->current_angles.push_back(0);
	}
	// Init arms
	this->arms.setPrimitiveType(Lines);
	for (int i = 1; i < this->numberOfArms * 2; i += 2) {
		static int k = 0;
		if (k == 0) {
			this->arms.append(Vertex(Vector2f(this->window->getSize().x / 2, this->window->getSize().y / 2), this->armsColor));
			this->arms.append(Vertex(Vector2f(this->window->getSize().x / 2, this->window->getSize().y / 2 - this->length_of_arms[k]), this->armsColor));
		}
		else {
			this->arms.append(this->arms[i - 2]);
			this->arms.append(Vertex(Vector2f(this->arms[i - 1].position.x, this->arms[i - 1].position.y - this->length_of_arms[k]), this->armsColor));
		}
		k++;
	}
	// Init lines
	this->lines.setPrimitiveType(LineStrip);
	// Init circles
	this->showCircles = false;
	for (int i = 0; i < this->numberOfArms; i++) {
		CircleShape temp;
		temp.setRadius(this->length_of_arms[i]);
		temp.setFillColor(Color::Transparent);
		temp.setOutlineColor(this->circlesColor);
		temp.setOutlineThickness(1.f);
		this->circles.push_back(temp);
	}
}

// Constructors & Destructors
Game::Game()
{
	this->input();
	this->initVars();
	this->initWindow();
	this->initSpirograph();
}

Game::~Game()
{
	delete this->window;
}

// Accessors
bool Game::running() const
{
	return this->window->isOpen();
}

// Functions
void Game::pollEvents()
{
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case Event::Closed:
			this->window->close();
			break;
		case Event::KeyPressed:
			if (this->event.key.code == Keyboard::Escape)
				this->window->close();
			if (this->event.key.code == Keyboard::Space)
				this->showCircles = !this->showCircles;
			break;
		}
	}
}

void Game::updateSpirograph()
{
	for (int i = 1; i < this->numberOfArms * 2; i += 2) {
		if (i/2 == 0) {
			this->arms[i].position.x = this->arms[i - 1].position.x + this->length_of_arms[i/2] * std::cos(this->current_angles[i/2]);
			this->arms[i].position.y = this->arms[i - 1].position.y + this->length_of_arms[i/2] * std::sin(this->current_angles[i/2]);
		}
		else {
			this->arms[i - 1] = this->arms[i - 2];
			this->arms[i].position.x = this->arms[i - 1].position.x + this->length_of_arms[i/2] * std::cos(this->current_angles[i/2]);
			this->arms[i].position.y = this->arms[i - 1].position.y + this->length_of_arms[i/2] * std::sin(this->current_angles[i/2]);
		}
		this->current_angles[i/2] += (this->speed_of_arms[i/2] / this->framerate);
		this->circles[i / 2].setPosition(this->arms[i - 1].position.x - this->circles[i / 2].getRadius(),
										 this->arms[i - 1].position.y - this->circles[i / 2].getRadius());
	}
	this->lines.append(Vertex(this->arms[numberOfArms*2 - 1].position, this->linesColor));
}

void Game::update()
{
	this->pollEvents();
	this->updateSpirograph();
}

void Game::renderSpirograph()
{
	this->window->draw(this->lines);
	this->window->draw(this->arms);
	if (showCircles) {
		for (auto circle : this->circles) {
			this->window->draw(circle);
		}
	}
}

void Game::render()
{
	this->window->clear();
	//
	this->renderSpirograph();
	//
	this->window->display();
}

