#include "Simulator.h"

Simulator::Simulator(string mapPath, double timeLimit, int updatesPerSecond)
 : m(mapPath), tmLimit(timeLimit), tmStep(1.0 / updatesPerSecond) {

}

pair<double, double> Simulator::simulate(Simulator::decisionFunction f, vector<Car> *log) const {
    double time = 0;
    Car c(m.getStart1(), m.getStart2());
    if(log) *log = { c };
    while(true) {
        if(time >= tmLimit) break;
        auto pos = c.getPosition();
        auto [f1, f2] = c.front();
        if(m.checkCollision(f1, f2)) break;
        auto rays = c.rays();
        auto rayOrigin = c.rayOrigin();
        vec::fixed<Car::RAYS + 1> input;
        input[0] = c.getSpeed();
        for(int i = 0; i < Car::RAYS; i++) {
            input[i+1] = m.rayTest(rayOrigin, rays[i]);
        }
        vec output = f(input);
        c.step(tmStep, output[0], output[1]);
        time += tmStep;
        if(log) log->push_back(c);
    }
    auto pos = c.getPosition();
    auto dist = m.getDist(pos[0], pos[1]);
    return { dist, dist / time };
}