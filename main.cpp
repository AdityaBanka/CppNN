#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <vector>
#include "Node.h"

using namespace std;

class Net
{
public:
    int length;

    vector<int> topology;                   // an array containting number of nodes in each layer
    vector<vector<Node>> nodes;             // an array of arrays [layer][node]
    vector<vector<vector<double>>> weights; // an array of 2d arrays [layer][firstNode][secondNode]

    vector<double> prediction; // an array containing calcuated probabilty
    vector<double> output;     // an array containing the expected results

    Net(vector<int> topology)
    {
        length = topology.size();
        this->topology = vector<int>(length);
        for (int i = 0; i < length; i++)
        {
            this->topology[i] = topology[i];
        }

        nodes = vector<vector<Node>>(length);
        for (int i = 0; i < length; i++) // selecting the layer
        {
            nodes[i] = vector<Node>(topology[i]);
            for (int j = 0; j < topology[i]; j++) // selecting the node inside that layer
            {
                double random = (double)((rand() * 1.0) / INT_MAX);
                nodes[i][j] = Node(random);
            }
        }

        weights = vector<vector<vector<double>>>(length);
        for (int i = 0; i < length - 1; i++) // selecting the layer
        {
            weights[i] = vector<vector<double>>(topology[i]);
            for (int j = 0; j < topology[i]; j++) // selecting the current node
            {
                weights[i][j] = vector<double>(topology[i + 1]);
                for (int k = 0; k < topology[i + 1]; k++) // selecting the next connected node
                {
                    weights[i][j][k] = (rand() * 1.0) / INT_MAX;
                }
            }
        }

        prediction = vector<double>(topology[length - 1]);
        for (int i = 0; i < topology[length - 1]; i++)
        {
            prediction[i] = 0;
        }

        output = vector<double>(topology[length - 1]);
        for (int i = 0; i < topology[length - 1]; i++)
        {
            output[i] = 0;
        }
    }

    void printNodes()
    {
        for (int layer = 0; layer < length; layer++)
        {
            for (int node = 0; node < topology[layer]; node++)
            {
                cout << nodes[layer][node].value << " ";
            }
            cout << endl;
        }
    }
    void printWeights()
    {
        for (int layer = 0; layer < length - 1; layer++)
        {
            for (int fisrtNode = 0; fisrtNode < topology[layer]; fisrtNode++)
            {
                for (int secondNode = 0; secondNode < topology[layer + 1]; secondNode++)
                {
                    cout << weights[layer][fisrtNode][secondNode] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
    }

    double relu(double x) // ReLU Function
    {
        return std::max(0.0, x);
    }

    double relu_derivative(double x) // Derivative of ReLU Function
    {
        return x > 0 ? 1.0 : 0.0;
    }

    void input()
    {
    }

    void forwardPass()
    {
        for (int layer = 1; layer < length; layer++)
        {
            for (int currentNode = 0; currentNode < topology[layer]; currentNode++)
            {
                double sum = 0;
                for (int node = 0; node < topology[layer - 1]; node++)
                {
                    sum += nodes[layer - 1][node].value * weights[layer - 1][node][currentNode];
                }
                nodes[layer][currentNode].value = relu(sum + nodes[layer][currentNode].bias);
            }
        }
    }

    void softMax()
    {
        double sum = 0;
        for (int node = 0; node < topology[length - 1]; node++)
        {
            prediction[node] = exp(nodes[length - 1][node].value);
            sum += prediction[node];
        }
        for (int node = 0; node < topology[length - 1]; node++)
        {
            prediction[node] /= sum;
        }
    }

    double lossCalculation()
    {
        double loss = 0;
        for (int node = 0; node < topology[length - 1]; node++)
        {
            if (output[node] == 1)
            {
                loss -= log(prediction[node]);
            }
        }
        return (loss);
    }
};

int main()
{
    time_t Time;
    srand((unsigned)time(&Time));

    vector<int> topology = {4, 5, 6, 3, 1};
    Net neuralNet = Net(topology);
    neuralNet.printWeights();
    neuralNet.forwardPass();
    neuralNet.printNodes();
}