#include "Render.h"

void render(sf::RenderWindow &window, Car c, Map m, sf::Texture map) {
    sf::Sprite spr(map);
    sf::View view(spr.getGlobalBounds());
    window.setView(view);

    window.draw(spr);

    sf::RectangleShape shape;
    vec2 pos = c.getPosition(), dir = c.getDirection();
    auto rot = 180 / M_PI * atan2(dir[1], dir[0]);
    
    shape.setPosition({ pos[0], pos[1] });
    shape.setOrigin({ Car::HL, Car::HW });
    shape.setSize({ Car::LENGTH, Car::WIDTH });
    shape.setRotation(rot);
    shape.setFillColor(sf::Color(127, 127, 127));
    window.draw(shape);

    const float thick = 3.f;
    shape.setOrigin({ 0,  thick / 2 });
    shape.setFillColor(sf::Color::Red);
    auto rotations = linspace(rot + 90, rot - 90, Car::RAYS);
    auto rays = c.rays();
    auto rayOrigin = c.rayOrigin();
    shape.setPosition({ rayOrigin[0], rayOrigin[1] });
    for(int i = 0; i < Car::RAYS; i++) {
        shape.setRotation(rotations[i]);
        shape.setSize({ m.rayTest(rayOrigin, rays[i]), thick });
        window.draw(shape);
    }
    window.draw(shape);

    window.setView(window.getDefaultView());
}

void render(sf::RenderWindow &window, vector<Car> cars, sf::Texture map, int carOpacity) {
    sf::Sprite spr(map);
    sf::View view(spr.getGlobalBounds());
    window.setView(view);

    window.draw(spr);

    for(auto c: cars) {
        sf::RectangleShape shape;
        vec2 pos = c.getPosition(), dir = c.getDirection();
        auto rot = 180 / M_PI * atan2(dir[1], dir[0]);
        
        shape.setPosition({ pos[0], pos[1] });
        shape.setOrigin({ Car::HL, Car::HW });
        shape.setSize({ Car::LENGTH, Car::WIDTH });
        shape.setRotation(rot);
        shape.setFillColor(sf::Color(127, 127, 127, carOpacity));
        window.draw(shape);
    }

    window.setView(window.getDefaultView());
}

void showSimulation(string mapPath, int updatesPerSecond, vector<vector<Car>> cars) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Game");

    sf::Texture mapTexture;
    mapTexture.loadFromFile(mapPath);
    auto timeStep = sf::seconds(1.f / updatesPerSecond);
    int currentFrame = 0;

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
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
                currentFrame = 0;
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        vector<Car> current;
        for(auto &c: cars) {
            current.push_back(c[min(currentFrame, (int)c.size()-1)]);
        }
        render(window, current, mapTexture, 127);
        currentFrame++;

        // end the current frame
        window.display();

        auto elapsed = clock.restart();
        if(elapsed < timeStep) {
            sf::sleep(timeStep - elapsed);
        }
        
    }
}