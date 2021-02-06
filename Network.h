#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include "Neuron.h"

typedef vector<Neuron> layer;

using namespace std;
class Network{
public:
    Network(){};
    Network(const vector<unsigned> &topology);
    void initializeNetwork(const vector<unsigned> &topology);
    void analyze();
    void feedForward(vector<int>& input);
    void backPropagate(vector<double> ideals, double learnRate, double momentum);
    vector<double> getOutput();
private:
    void calculateGradients();
    double e = 2.71828182845904523536;
    void calculateDeltas(vector<double> ideals);
    void calculateDetaWeights(double learnRate, double momentum);
    void updateWeights();
    double activationDerivative(double num);
    vector<layer> network;
};
#endif //XOR_NETWORK_H
