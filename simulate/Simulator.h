#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Map.h"
#include "Car.h"

class Simulator {
    Map m;
    double tmLimit;
    double tmStep;

public:
    typedef function<vec(vec)> decisionFunction;

    Simulator() { }
    Simulator(string mapPath, double timeLimit, int updatesPerSecond);

    //returns: (distance, average speed)
    pair<double, double> simulate(decisionFunction f, vector<Car> *log = nullptr) const;
};

#endif