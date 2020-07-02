#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <armadillo>
#include <string>
#include <vector>
using namespace std;

class Map {
    sf::Image map;
    sf::Vector2u start1;
    sf::Vector2u start2;
    vector<vector<int>> dist;

public:
    Map() { }
    Map(string path);

    sf::Vector2u getSize() const {
        return map.getSize();
    }

    arma::vec2 getStart1() const {
        return { start1.x, start1.y };
    }

    arma::vec2 getStart2() const {
        return { start2.x, start2.y };
    }

    bool isFree(int x, int y) const {
        return x >= 0 && y >= 0 && x < getSize().x && y < getSize().y &&
            map.getPixel(x, y) != sf::Color::Black && map.getPixel(x, y) != sf::Color::Blue;
    }

    int getDist(int x, int y) const {
        if(x < 0 || y < 0 || x >= getSize().x || y >= getSize().y) {
            return -1;
        }
        return dist[x][y];
    }

    double rayTest(arma::vec2 origin, arma::vec2 direction) const;

    bool checkCollision(arma::vec2 p1, arma::vec2 p2) const;
};

#endif