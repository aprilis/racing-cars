#include <SFML/Graphics.hpp>
#include "../simulate/Car.h"
#include "../simulate/Map.h"

void render(sf::RenderWindow &window, vector<Car> cars, sf::Texture map, int carOpacity);
void render(sf::RenderWindow &window, Car c, Map m, sf::Texture map);

void showSimulation(string mapPath, int updatesPerSecond, vector<vector<Car>> cars);