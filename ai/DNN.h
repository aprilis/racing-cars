#ifndef DNN_H
#define DNN_H

#include <armadillo>
#include <vector>
using namespace arma;
using namespace std;

class DNN {
    vector<mat> weights;
    vector<vec> bias;
    int paramsN;

    vec activation(vec v) {
        return tanh(v);
    }

public:
    DNN(vector<int> layersSize = {});

    vec feedForward(vec input);

    vector<double> params();
    void loadParams(const vector<double> &p);

    int getParamsN() const { return paramsN; }

    function<vec(vec)> decisionFunction(double scale);
};

#endif