#include "../ai/Problems.h"

#include <pagmo/algorithm.hpp>
#include <pagmo/algorithms/nsga2.hpp>
#include <pagmo/population.hpp>
#include <pagmo/problem.hpp>
using namespace pagmo;

#include <boost/archive/text_oarchive.hpp>
#include <fstream>
#include <ctime>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

const int UPDATES_PER_SECOND = 30;

int main(int argc, char *argv[]) {
    if(argc < 6) {
        cerr << "5 parameters required: initial_population, time limit, number of generations, population size, map paths" << endl;
        return 0;
    }
    string populationPath = argv[1];
    int timeLimit = atoi(argv[2]);
    int generations = atoi(argv[3]);
    int populationSize = atoi(argv[4]);

    cerr << "Parameters: " << endl;
    cerr << "Time limit: " << timeLimit << endl;
    cerr << "Generations: " << generations << endl;
    cerr << "Population size: " << populationSize << endl;

    DNN d({ Car::RAYS + 1, 20, 2 });
    vector<Simulator> sims;
    for(int i = 5; i < argc; i++) {
        sims.emplace_back(argv[i], timeLimit, UPDATES_PER_SECOND);
    }
    DNNMultiProblem p {d, sims, 10};
    problem prob {p};
    algorithm algo{nsga2(generations)};
    population pop{prob};
    
    if(populationPath != "random") {
        vector<vector_double> vecs;
        ifstream file(populationPath);
        boost::archive::text_iarchive ar(file);
        ar >> vecs;
        for(auto v: vecs)
            pop.push_back(v);
    } else {
        int n = d.getParamsN();
        for(int i = 0; i < populationSize; i++) {
            vec v = randn(n);
            pop.push_back(vector<double>(v.begin(), v.end()));
        }
    }
    algo.set_verbosity(1);
    pop = algo.evolve(pop);

    std::cout << "The population: \n" << pop;

    if(!fs::exists("population")) {
        fs::create_directory("population");
    }
    if(!fs::exists("logs")) {
        fs::create_directory("logs");
    }

    auto t = time(nullptr);
    auto tm = *localtime(&t);
    std::ostringstream oss;
    oss << "DNN_20_" << std::put_time(&tm, "%d%m_%H%M%S");
    auto filename = oss.str();

    {
        auto filePath = "population/" + filename;
        ofstream of(filePath);
        boost::archive::text_oarchive ar(of);
        ar << pop.get_x();

        cout << "Population saved to " << filePath << endl;
    }
    {
        auto filePath = "logs/" + filename;
        ofstream of(filePath);
        auto log = algo.extract<nsga2>()->get_log();
        for(auto l: log) {
            for(auto x: get<2>(l)) {
                of << -x << " ";
            }
            of << "\n";
        }

        cout << "Log saved to " << filePath << endl;
    }
}