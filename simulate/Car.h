#ifndef CAR_H
#define CAR_H

#include <cmath>
#include <armadillo>
#include <array>
using namespace std;
using namespace arma;

class Car {
    double speed = 0;
    vec2 direction;
    vec2 position;

public:
    static constexpr double MAX_ACC = 100;
    static constexpr double MAX_BRAKE = 300;
    static constexpr double MAX_TURN = M_PI / 4;
    
    static constexpr int WIDTH = 20;
    static constexpr int LENGTH = 40;
    static constexpr double HW = WIDTH / 2;
    static constexpr double HL = LENGTH / 2;

    static constexpr int RAYS = 7;

    Car() { }
    Car(vec2 pos, vec2 look) { setPosition(pos, look); }

    void setPosition(vec2 pos, vec2 look);
    vec2 getPosition() const { return position; }
    vec2 getDirection() const { return direction; }
    double getSpeed() const { return speed; }

    void step(double timeStep, double acc, double turn);

    array<vec2, RAYS> rays();

    vec2 rayOrigin();

    pair<vec2, vec2> front();
};

#endif