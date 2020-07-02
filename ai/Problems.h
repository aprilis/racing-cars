#ifndef PROBLEMS_H
#define PROBLEMS_H

#include "DNN.h"
#include "../simulate/Simulator.h"

#include <pagmo/problem.hpp>
#include <pagmo/types.hpp>

using namespace pagmo;

struct DNNProblem {
    DNN d;
    Simulator s;
    double limit = 10;
    
    vector_double fitness(const vector_double &dv) const {
        DNN d1 = d;
        d1.loadParams(dv);
        auto [a, b] = s.simulate(d1.decisionFunction(Car::LENGTH));
        return { -a, -b };
    }

    pair<vector_double, vector_double> get_bounds() const {
        int n = d.getParamsN();
        return { vector_double(n, -limit), vector_double(n, limit) };
    }

    vector_double::size_type get_nobj() const {
        return 2;
    }
};

struct DNNMultiProblem {
    DNN d;
    vector<Simulator> sims;
    double limit = 10;
    
    vector_double fitness(const vector_double &dv) const {
        vector_double res;
        DNN d1 = d;
        d1.loadParams(dv);
        for(auto &s: sims) {
            auto [a, b] = s.simulate(d1.decisionFunction(Car::LENGTH));
            res.push_back(-a);
            res.push_back(-b);
        }
        return res;
    }

    pair<vector_double, vector_double> get_bounds() const {
        int n = d.getParamsN();
        return { vector_double(n, -limit), vector_double(n, limit) };
    }

    vector_double::size_type get_nobj() const {
        return sims.size() * 2;
    }
};

struct DNN1DProblem {
    DNN d;
    Simulator s;
    double limit = 10;
    
    vector_double fitness(const vector_double &dv) const {
        DNN d1 = d;
        d1.loadParams(dv);
        auto [a, b] = s.simulate(d1.decisionFunction(Car::LENGTH));
        return { -a };
    }

    pair<vector_double, vector_double> get_bounds() const {
        int n = d.getParamsN();
        return { vector_double(n, -limit), vector_double(n, limit) };
    }
};

#endif