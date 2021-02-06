#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <math.h>


struct connection{
    double weight;
    double deltaWeight;
    double gradient;
    connection(){
        weight = ((rand() % 200)/100.0) - 1;
        deltaWeight = 0;
    }
};

using namespace std;
class Neuron{
public:
    vector<connection> connections;
    double sum;
    double delta;
    
    Neuron(unsigned layer, unsigned index, const vector<unsigned> &topology);
    void analyze() const;
    double output() const;
private:
    int layer;
    int index;
    double e = 2.71828182845904523536;
    double activation(double num) const;
};
#endif
