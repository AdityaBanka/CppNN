#include "Node.h"

Node::Node()
{
    bias = 0;
    value = 1;
    loss = 0;
}
Node::Node(double bias)
{
    this->bias = bias;
    value = 1;
    loss = 0;
}
