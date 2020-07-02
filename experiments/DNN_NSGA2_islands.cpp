#include "../ai/Problems.h"

#include <pagmo/algorithm.hpp>
#include <pagmo/algorithms/nsga2.hpp>
#include <pagmo/population.hpp>
#include <pagmo/problem.hpp>
#include <pagmo/archipelago.hpp>
using namespace pagmo;

#include <boost/archive/text_oarchive.hpp>
#include <fstream>
#include <ctime>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

const int UPDATES_PER_SECOND = 30;

int main(int argc, char *argv[]) {
    if(argc != 5) {
        cerr << "4 parameters required: map path, time limit, number of generations, population size" << endl;
        return 0;
    }
    string path = argv[1];
    int timeLimit = atoi(argv[2]);
    int generations = atoi(argv[3]);
    int populationSize = atoi(argv[4]);

    cerr << "Parameters: " << endl;
    cerr << "Time limit: " << timeLimit << endl;
    cerr << "Generations: " << generations << endl;
    cerr << "Population size: " << populationSize << endl;

    DNN d({ Car::RAYS + 1, 20, 2 });
    Simulator s(path, timeLimit, UPDATES_PER_SECOND);
    DNNProblem p {d, s, 10};
    problem prob {p};
    algorithm algo{nsga2(generations)};
    algo.set_verbosity(1);
    archipelago arch{16u, algo, prob, 20u};
    /*int n = d.getParamsN();
    for(int i = 0; i < populationSize; i++) {
        vec v = randn(n);
        pop.push_back(vector<double>(v.begin(), v.end()));
    }  
    pop = algo.evolve(pop);*/
    arch.evolve(10);

    arch.wait_check();

    for (const auto &isl : arch) {
        std::cout << isl.get_population() << '\n';
    }

    /*std::cout << "The population: \n" << pop;

    if(!fs::exists("population")) {
        fs::create_directory("population");
    }

    auto t = time(nullptr);
    auto tm = *localtime(&t);
    std::ostringstream oss;
    oss << "population/DNN_NSGA2_2L_" << std::put_time(&tm, "%d%m_%H%M%S");
    auto filename = oss.str();

    ofstream of(filename);
    boost::archive::text_oarchive ar(of);
    ar << pop.get_x();

    cout << "saved to " << filename << endl;*/
}