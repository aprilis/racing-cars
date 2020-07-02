#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "visualise/Render.h"
#include "simulate/Map.h"
#include "simulate/Car.h"

int main(int argc, char *argv[])
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Game");

    string mapPath = argv[1];
    sf::Texture mapTexture;
    mapTexture.loadFromFile(mapPath);
    Map m(mapPath);
    Car c(m.getStart1(), m.getStart2());

    auto timeStep = sf::seconds(1 / 30.f);

    sf::Clock clock;
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        render(window, c, m, mapTexture);

        // end the current frame
        window.display();

        auto elapsed = clock.restart();
        if(elapsed < timeStep) {
            sf::sleep(timeStep - elapsed);
        }
        double acc = 0, turn = 0;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            acc = 1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            acc = -1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            turn = 1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            turn = -1;
        }
        c.step(timeStep.asSeconds(), acc, turn);
    }

    return 0;
}