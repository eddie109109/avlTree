#include "Node.h"
#include "avlTree.h"
#include <iostream>
#include <string>

int main() {
  avlTree avl;
  avl.insert(10);
  avl.insert(5);
  avl.insert(2);
  avl.insert(7);
  avl.insert(13);
  avl.insert(8);
  avl.remove(11);
  avl.remove(13);
  avl.inOrderPrint();
  avl.insert(13);
  avl.search(13);
  return 0;
}
