#include "DNN.h"

DNN::DNN(vector<int> layersSize) {
    int n = layersSize.size() - 1;
    weights.resize(n);
    bias.resize(n);
    paramsN = 0;
    for(int i = 0; i < n; i++) {
        weights[i] = mat(layersSize[i + 1], layersSize[i]);
        bias[i] = vec(layersSize[i + 1]);
        paramsN += (layersSize[i] + 1) * layersSize[i + 1];
    }
}

vec DNN::feedForward(vec v) {
    for(int i = 0; i < weights.size(); i++) {
        v = activation(weights[i] * v + bias[i]);
    }
    return v;
}

vector<double> DNN::params() {
    vector<double> res;
    for(const auto &w: weights) {
        res.insert(res.end(), w.begin(), w.end());
    }
    for(const auto &b: bias) {
        res.insert(res.end(), b.begin(), b.end());
    }
    return res;
}

void DNN::loadParams(const vector<double> &params) {
    auto it = params.begin();
    for(auto &w: weights) {
        for(auto &x: w) {
            x = *(it++);
        }
    }
    for(auto &b: bias) {
        for(auto &x: b) {
            x = *(it++);
        }
    }
}

function<vec(vec)> DNN::decisionFunction(double scale) {
    return [this, scale](auto input) {
        return this->feedForward(input / scale);
    };
}