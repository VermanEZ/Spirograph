#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Game.h"
using namespace sf;


int main()
{
    Game game;

    while (game.running())
    {
        game.update();

        game.render();
    }
}