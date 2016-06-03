#include "Neuron.h"

Neuron::Neuron(unsigned layer, unsigned index, const vector<unsigned> &topology) {
    Neuron::layer = layer;
    Neuron::index = index;
    delta = 0;

    if(index == 0){
        sum = 1;
    }else{
        sum = 0;
    }

    if(index != 0 && layer != 0){
        for (int i = 0; i <= topology[layer - 1]; ++i){
            connections.push_back(connection());
        }
    }
}

double Neuron::output() const{
    if(index == 0 || layer == 0){
        return sum;
    }else{
        return activation(sum);
    }
}

// Sigmoid function
double Neuron::activation(double num) const{
    return 1/(1 + pow(e, (-1*num)));
}

void Neuron::analyze() const {
    // Display node location
    cout << left << setw(5) << "Layer: " << setw(5) << layer << setw(5) << "Node: " << index << endl;

    // Display node connections
    if(index != 0 && layer != 0){
        for (int i = 0; i < connections.size(); ++i){
            cout << left << setw(5) << "Connection: " << setw(5) << i << setw(5) << "Weight: " << setw(5) << connections[i].weight <<
                    setw(5) << "Gradient: " << setw(5) << connections[i].gradient << endl;
        }
    }

    //Display sum
    cout << left << setw(5) << "Sum: " << sum << endl;

    // Display output
    cout << left << setw(5) << "Output: " << output() << endl;

    // Display node delta
    cout << left << setw(5) << "Node Delta: " << delta << endl;

    cout << endl;
}
