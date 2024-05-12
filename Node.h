#ifndef NODE_H
#define NODE_H

class Node
{
public:
    double bias;
    double value;
    double loss;

    Node();
    Node(double bias);
};

#endif