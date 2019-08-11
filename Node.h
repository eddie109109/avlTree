#pragma once
#include <string>
#include <iostream>

using namespace std;

class Node {
public:
  Node * left;
  Node * right;
  Node(int val, Node * l, Node * r);
  int value;
  int height;
};
