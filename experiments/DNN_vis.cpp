#include "../visualise/Render.h"
#include "../ai/DNN.h"
#include "../simulate/Simulator.h"
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <fstream>
#include <pagmo/types.hpp>
using namespace std;
using namespace pagmo;

const int UPDATES_PER_SECOND = 30;

int main(int argc, char *argv[]) {
    if(argc != 4) {
        cerr << "3 parameters required: map path, population path, time limit" << endl;
        return 0;
    }
    string path = argv[1];
    string popPath = argv[2];
    int timeLimit = atoi(argv[3]);

    DNN d({ Car::RAYS + 1, 2 });
    Simulator s(path, timeLimit, UPDATES_PER_SECOND);

    vector<vector_double> params;
    ifstream file(popPath);
    boost::archive::text_iarchive ar(file);
    ar >> params;
    file.close();

    vector<vector<Car>> log(params.size());
    for(int i = 0; i < params.size(); i++) {
        d.loadParams(params[i]);
        s.simulate(d.decisionFunction(Car::LENGTH), &log[i]);
    }

    showSimulation(path, UPDATES_PER_SECOND, log);
}