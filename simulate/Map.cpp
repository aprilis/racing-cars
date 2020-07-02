#include "Map.h"
#include <armadillo>
#include <queue>
using namespace arma;
using namespace std;

Map::Map(string path) {
    map.loadFromFile(path);
    auto [w, h] = map.getSize();
    for(unsigned i = 0; i < w; i++)
        for(unsigned j = 0; j < h; j++) {
            if(map.getPixel(i, j) == sf::Color::Red) {
                start1 = { i, j };
            }
            if(map.getPixel(i, j) == sf::Color::Green) {
                start2 = { i, j };
            }
        }
    const int inf = w * h + 1;
    dist.resize(w, vector<int>(h, inf));
    queue<sf::Vector2u> q;
    dist[start1.x][start1.y] = 0;
    q.push(start1);
    while(!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for(int i = -1; i <= 1; i++)
            for(int j = -1; j <= 1; j++) {
                int x1 = x + i, y1 = y + j;
                if(isFree(x1, y1) && dist[x1][y1] == inf) {
                    dist[x1][y1] = dist[x][y] + 1;
                    q.push({(unsigned)x1, (unsigned)y1});
                }
            }
    }
}

double Map::rayTest(vec2 origin, vec2 direction) const {
    constexpr double STEP = 0.5;
    direction *= STEP / norm(direction);
    double ans = 0;
    while(true) {
        auto r = round(origin);
        if(!isFree(r[0], r[1])) break;
        origin += direction;
        ans += STEP;
    }
    return ans;
}

bool Map::checkCollision(arma::vec2 p1, arma::vec2 p2) const {
    return rayTest(p1, p2 - p1) <= norm(p2 - p1);
}