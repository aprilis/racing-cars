#include "Car.h"
#include <algorithm>

vec2 rotate(vec2 v, double alpha) {
    return mat22 { { cos(alpha), sin(alpha) }, { -sin(alpha), cos(alpha) } } * v;
}

void Car::setPosition(vec2 pos, vec2 look) {
    position = pos;
    direction = normalise(look - position);
}

void Car::step(double timestep, double acc, double turn) {
    acc = clamp(acc, -1.0, 1.0);
    turn = clamp(turn, -1.0, 1.0);
    if(acc > 0) acc *= MAX_ACC;
    else acc *= MAX_BRAKE;
    turn *= MAX_TURN;
    vec2 front = position + direction * HL;
    auto frontDirection = rotate(direction, turn);
    speed = max(0.0, speed + timestep * acc);
    front += frontDirection * (speed * timestep);
    direction = normalise(front - position);
    position = front - direction * HL;
}

array<vec2, Car::RAYS> Car::rays() {
    auto alphas = linspace(-datum::pi / 2, datum::pi / 2, RAYS);
    array<vec2, RAYS> ans;
    for(int i = 0; i < RAYS; i++) {
        ans[i] = rotate(direction, alphas[i]);
    }
    return ans;
}

vec2 Car::rayOrigin() {
    return position + direction * HL;
}

pair<vec2, vec2> Car::front() {
    vec2 directionT = { -direction[1], direction[0] };
    return { position + direction * HL + directionT * HW,
        position + direction * HL - directionT * HW };
}