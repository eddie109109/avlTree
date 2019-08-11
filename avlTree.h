#pragma once
#include "Node.h"
#include <string>
#include <iostream>

class avlTree {
public:
  avlTree(); //good
  ~avlTree(); // good
  int height(); // good
  int max(int a, int b); // good
  void insert(int val); // good
  void remove(int val);
  bool search(int val);// good
  void inOrderPrint(); // good




private:
  Node * root;
  Node * insertHelper(Node * &tree,int val);
  bool hasLeftChild(Node * ptr) const; // good
  bool hasRightChild(Node * ptr) const; // good
  Node * searchHelper(Node * ptr, int val);
  void inOrderPrintHelper(Node * ptr) const; // good
  int heightHelper(Node * tree);
  Node * maximum(Node * root);
  Node * minimum(Node * root);
  Node * leftLeftRotation(Node * k2);
  Node * rightRightRotation(Node * k1);
  Node * leftRightRotation(Node * k3);
  Node * rightLeftRotation(Node * k1);
  void removeTree(Node * ptr);
  Node* removeHelper(Node * &tree, Node * z);


};
