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
    if(argc < 5) {
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
    population pop{prob};
    if(argc >= 6) {
        vector<vector_double> vecs;
        ifstream file(argv[5]);
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