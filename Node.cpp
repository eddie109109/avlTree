#include "Node.h"
#include <iostream>
#include <string>

using namespace std;

Node::Node(int val, Node * l, Node * r):left(l),right(r),value(val),height(0){}
