#include "Network.h"
#include "Neuron.h"

/*
 * Constructor for Network class. Pushes layers of a predifined number of neurons onto the network.
 *
 * @param vector refrence to topology layout
 */
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

/* Performs feedforward calculations on the network given in set of input values
 *
 * @param input vector containing the input values
 * @return void
 */
void Network::feedForward(vector<int>& input) {

    // Set input layer
    for (int i = 1; i < input.size(); ++i) {
        network[0][i].sum = input[i-1];
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
}

/* analyze iterates through every neuron, calling the neurons analyze function to display neurons properties.
 *
 * @params null
 * @return void
 */
void Network::analyze() {
    for(unsigned l = 0; l < network.size(); ++l){
        for (unsigned i = 0; i < network[l].size(); ++i){
            network[l][i].analyze();
        }
    }
}

/* backPropagate utilizes the ideal output and prefered learning characteristics to adjust weights throughout the network.
 *
 * @param ideals vector containing the ideal output
 * @param learnRate double contianing learn rate tuning parameter for delta weight calculations
 * @param momentum double tuning parameter for influence of delta weights in sequential layers
 */
void Network::backPropagate(vector<double> ideals, double learnRate, double momentum) {
    calculateDeltas(ideals);
    calculateGradients();
    calculateDetaWeights(learnRate, momentum);
    updateWeights();
}

/* calculateDeltas finds the delta between the ideal value of output and the actual.
 *
 * @parameter ideals vector containing ideal output of network 
 * @return void
 */
void Network::calculateDeltas(vector<double> ideals) {
    vector<double> errors;

    // Calculate output errors
    for (int i = 1; i < network[network.size() - 1].size(); ++i) {
        double error;
        error = network[network.size() - 1][i].output() - ideals[i - 1];
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

/* calculateGradients calculates the gradient of the rate of change when training the network
 *
 * @returns void
 */
void Network::calculateGradients() {
    for(int l = network.size() - 1; l > 0; --l){
        for(int i = 1; i < network[l].size(); ++i){
            for(int conn = 0; conn < network[l][i].connections.size(); ++conn){
                network[l][i].connections[conn].gradient = network[l][i].delta * network[l - 1][conn].output();
            }
        }
    }
}

/* calculateDeltas determines the amount to change each weight within each neuron
 *
 * @param learnRate double, tuning parameter for training
 * @param momentum double for affectiveness of back propigation in training consecutive layers
 */
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

/* updateWeights progresses through the network to adjust weights in each neuron.
 *
 * @return void
 */
void Network::updateWeights(){
    for(int l = 1; l < network.size(); ++l){
        for(int i = 1; i < network[l].size(); ++i){
            for(int conn = 0; conn < network[l][i].connections.size(); ++conn){
                network[l][i].connections[conn].weight += network[l][i].connections[conn].deltaWeight;
            }
        }
    }
}

/* activationDerivative returns the deravative of the sigmoid activation function
 *
 * @param num double of input to derivative function
 * @return the output of the derivative 
 */
double Network::activationDerivative(double num) {
    return (1/(1 + pow(e, (-1*num)))) * (1 - (1/(1 + pow(e, (-1*num)))));
}

/* initializeNetwork creates the neual network given a specific topology
 *
 * @param topology vector refrence of topology layout
 * @return void
 */
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

/* getOutput returns a vector containing the values of the neurons in the final layer of the network.
 *
 * @return vector containing values of the networks output layer
 */
vector<double> Network::getOutput(){
    vector<double> output;
    for(int i = 1; i < network[network.size()-1].size(); ++i){
        output.push_back(network[network.size()-1][i].output());
    }
    
    return output;
}
