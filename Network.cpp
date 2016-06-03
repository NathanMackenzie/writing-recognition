#include "Network.h"
#include "Neuron.h"

Network::Network(const vector<unsigned> &topology) {
    for(unsigned l = 0; l < topology.size(); ++l){
        layer lay;
        //Add extra node for bias neuron
        for(unsigned i = 0; i <= topology[l]; ++i){
            lay.push_back(Neuron(l, i, topology));
        }
        network.push_back(lay);
    }
}

void Network::feedForward(int args[400]) {

    // Set input layer
    for (int i = 1; i < 400; ++i) {
        network[0][i].sum = args[i-1];
    }

    // Calculate sum for all remaining layers
    for (int l = 1; l < network.size(); ++l){
        for (int i = 1; i < network[l].size(); ++i){
            double sum = 0;
            for ( int conn = 0; conn < network[l - 1].size(); ++conn){
                sum += network[l - 1][conn].output() * network[l][i].connections[conn].weight;
            }
            network[l][i].sum = sum;
        }
    }

    for(int i = 1; i <= 10; ++i){
        //cout << network[4][i].sum << endl;
    }
}

void Network::analyze() {
    for(unsigned l = 0; l < network.size(); ++l){
        for (unsigned i = 0; i < network[l].size(); ++i){
            network[l][i].analyze();
        }
    }
}

void Network::backPropagate(vector<double> ideals, double learnRate, double momentum) {
    calculateDeltas(ideals);
    calculateGradients();
    calculateDetaWeights(learnRate, momentum);
    updateWeights();
}

void Network::calculateDeltas(vector<double> ideals) {
    vector<double> errors;

    // Calculate output errors
    for (int i = 1; i < network[network.size() - 1].size(); ++i) {
        double error;
        error = network[network.size() - 1][i].sum - ideals[i - 1];
        errors.push_back(error);
    }

    // Set output layers deltas
    for (int i = 1; i < network[network.size() - 1].size(); ++i) {
        network[network.size() - 1][i].delta = activationDerivative(network[network.size() - 1][i].sum) * ((-1)*errors[i-1]);
    }

    // Calculate hidden layer deltas
    for (int l = network.size() - 2; l > 0 ; --l) {
        for(int i = 1; i < network[l].size(); ++i){
            double sum = 0;
            for(int prevIn = 1; prevIn < network[l+1].size(); ++prevIn){
                sum += network[l+1][prevIn].delta * network[l+1][prevIn].connections[i].weight;
            }
            network[l][i].delta = activationDerivative(network[l][i].sum) * sum;
        }
    }
}

void Network::calculateGradients() {
    for(int l = network.size() - 1; l > 0; --l){
        for(int i = 1; i < network[l].size(); ++i){
            for(int conn = 0; conn < network[l][i].connections.size(); ++conn){
                network[l][i].connections[conn].gradient = network[l][i].delta * network[l - 1][conn].output();
            }
        }
    }
}

void Network::calculateDetaWeights(double learnRate, double momentum) {
    for(int l = 1; l < network.size(); ++l){
        for(int i = 1; i < network[l].size(); ++i){
            for(int conn = 0; conn < network[l][i].connections.size(); ++conn){
                network[l][i].connections[conn].deltaWeight = learnRate * network[l][i].connections[conn].gradient
                                                              + momentum * network[l][i].connections[conn].deltaWeight;
            }
        }
    }
}

void Network::updateWeights(){
    for(int l = 1; l < network.size(); ++l){
        for(int i = 1; i < network[l].size(); ++i){
            for(int conn = 0; conn < network[l][i].connections.size(); ++conn){
                network[l][i].connections[conn].weight += network[l][i].connections[conn].deltaWeight;
            }
        }
    }
}

double Network::activationDerivative(double num) {
    return (1/(1 + pow(e, (-1*num)))) * (1 - (1/(1 + pow(e, (-1*num)))));
}

void Network::initializeNetwork(const vector<unsigned> &topology)
{
    for(unsigned l = 0; l < topology.size(); ++l){
        layer lay;
        //Add extra node for bias neuron
        for(unsigned i = 0; i <= topology[l]; ++i){
            lay.push_back(Neuron(l, i, topology));
        }
        network.push_back(lay);
    }
}
