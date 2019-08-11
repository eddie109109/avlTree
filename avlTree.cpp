#include "Node.h"
#include "avlTree.h"
#include <iostream>
#include <string>

using namespace std;

avlTree::avlTree() {
  root = NULL;
}


avlTree::~avlTree() {
  removeTree(root);
}


void avlTree::removeTree(Node * ptr) {
  if (ptr == NULL) {
		// cout << "the tree is empty" << endl;
		return;
	} else {
		if (ptr->left != NULL) { // use pre -order to traverse the list
			removeTree(ptr->left); // recursively traverse to the left
		}

		if (ptr->right != NULL) {
			removeTree(ptr->right); // recursively traverse to the right
		}
		cout << "deleting " << ptr->value << endl;
		delete ptr;
	}
}

void avlTree::insert(int val) {
  insertHelper(root,val);
  cout << "inserted " << val << endl;
}

Node* avlTree::insertHelper(Node * &tree, int val){
  if (tree == NULL)
    {
        // newRoot
        tree = new Node(val, NULL, NULL);
        if (tree==NULL)
        {
            cout << "ERROR: create avltree node failed!" << endl;
            return NULL;
        }
    }
    else if (val < tree->value)
    {
        tree->left = insertHelper(tree->left, val);
        // after insertion, it needs balancing
        if (heightHelper(tree->left) - heightHelper(tree->right) == 2)
        {

            if (val < tree->left->value) {
              tree = leftLeftRotation(tree);
            } else {
              tree = leftRightRotation(tree);
            }

        }
    }
    else if (val > tree->value)
    {
        tree->right = insertHelper(tree->right, val);
        // after insertion, it moight need balancing
        if (heightHelper(tree->right) - heightHelper(tree->left) == 2)
        {

            if (val > tree->right->value) {
              tree = rightRightRotation(tree);
            } else {
              tree = rightLeftRotation(tree);
            }

        }
    }
    else //key == tree->key)
    {
        cout << "can't add node with the same value" << endl;
    }

    tree->height = max( heightHelper(tree->left), heightHelper(tree->right)) + 1;

    return tree;
}

void avlTree::inOrderPrint() {
  inOrderPrintHelper(root);
  cout << endl;
}


void avlTree::inOrderPrintHelper(Node * ptr) const{
  if (ptr == NULL) {
    return;
  }
    inOrderPrintHelper(ptr->left);
  cout << ptr->value << " ";
    inOrderPrintHelper(ptr->right);
}

int avlTree::heightHelper(Node * tree) {
  if (tree != NULL) {
    return tree->height;
  }
  return 0;
}

int avlTree::height() {
  return heightHelper(root);
}

int avlTree::max(int a, int b) {
  return a>b?a:b;
}

Node *avlTree::leftLeftRotation(Node * k2) {
  Node * k1 = NULL;
  k1 = k2->left;
  k2->left = k1->right;
  k1->right = k2;

  k2->height = max( heightHelper(k2->left), heightHelper(k2->right)) + 1;
  k1->height = max( heightHelper(k1->left), k2->height) + 1;

  return k1;
}

Node *avlTree::rightRightRotation(Node * k1) {
   Node * k2 = NULL;

   k2 = k1->right;
   k1->right = k2->left;
   k2->left = k1;

   k1->height = max( heightHelper(k1->left), heightHelper(k1->right)) + 1;
   k2->height = max( heightHelper(k2->right), k1->height) + 1;

   return k2;
}

Node *avlTree::leftRightRotation(Node * k3) {
    k3->left = rightRightRotation(k3->left);
    return leftLeftRotation(k3);
}

Node *avlTree::rightLeftRotation(Node * k1) {
    k1->right = leftLeftRotation(k1->right);
    return rightRightRotation(k1);
}


Node* avlTree::searchHelper(Node * ptr, int val){
  if (ptr == NULL) {
    return NULL;
  } else {
    Node * targetNode = new Node(val, NULL, NULL);// make the target node that has the same last name and first initial as a comparison
		if (targetNode->value == ptr->value) {
			delete targetNode; // we need to delete the new node when we return the node in the tree
			return ptr;
		} else if (targetNode->value > ptr->value) {
			delete targetNode;
			return searchHelper(ptr->right, val);
		} else {
			delete targetNode;
			return searchHelper(ptr->left, val);
		}
  }
}


bool avlTree::search(int val) {
  if (searchHelper(root,val) != NULL) {
    cout << "found the node " << val << endl;
    return true;
  }
  cout << "couldn't find the target node "<< val << endl;
  return false;
}


Node* avlTree::removeHelper(Node * &tree, Node * z) {
  // 根为空 或者 没有要删除的节点，直接返回NULL。
    if (tree==NULL || z==NULL) {
      return NULL;
    }

    if (z->value < tree->value)        // 待删除的节点在"tree的左子树"中
    {
        tree->left = removeHelper(tree->left, z);
        // 删除节点后，若AVL树失去平衡，则进行相应的调节。
        if (heightHelper(tree->right) - heightHelper(tree->left) == 2)
        {
            Node *r =  tree->right;
            if (heightHelper(r->left) > heightHelper(r->right))
                tree = rightLeftRotation(tree);
            else
                tree = rightRightRotation(tree);
        }
    }
    else if (z->value > tree->value)// 待删除的节点在"tree的右子树"中
    {
        tree->right = removeHelper(tree->right, z);
        // 删除节点后，若AVL树失去平衡，则进行相应的调节。
        if (heightHelper(tree->left) - heightHelper(tree->right) == 2)
        {
            Node *l =  tree->left;
            if (heightHelper(l->right) > heightHelper(l->left))
                tree = leftRightRotation(tree);
            else
                tree = leftLeftRotation(tree);
        }
    }
    else    // tree是对应要删除的节点。
    {
        // tree的左右孩子都非空
        if ((tree->left!=NULL) && (tree->right!=NULL))
        {
            if (heightHelper(tree->left) > heightHelper(tree->right))
            {
                // 如果tree的左子树比右子树高；
                // 则(01)找出tree的左子树中的最大节点
                //   (02)将该最大节点的值赋值给tree。
                //   (03)删除该最大节点。
                // 这类似于用"tree的左子树中最大节点"做"tree"的替身；
                // 采用这种方式的好处是：删除"tree的左子树中最大节点"之后，AVL树仍然是平衡的。
                Node* max = maximum(tree->left);
                tree->value = max->value;
                tree->left = removeHelper(tree->left, max);
            }
            else
            {
                // 如果tree的左子树不比右子树高(即它们相等，或右子树比左子树高1)
                // 则(01)找出tree的右子树中的最小节点
                //   (02)将该最小节点的值赋值给tree。
                //   (03)删除该最小节点。
                // 这类似于用"tree的右子树中最小节点"做"tree"的替身；
                // 采用这种方式的好处是：删除"tree的右子树中最小节点"之后，AVL树仍然是平衡的。
                Node* min = minimum(tree->right);
                tree->value = min->value;
                tree->right = removeHelper(tree->right, min);
            }
        }
        else
        {
            Node* tmp = tree;
            tree = (tree->left!=NULL) ? tree->left : tree->right;
            delete tmp;
        }
    }

    return tree;
}

void avlTree::remove(int val) {
    if (search(val)) {
        Node * z = searchHelper(root, val);
        root = removeHelper(root, z);
        cout << "removed the node " << val << endl;
    } else {
      cout << "couldn't remove the node " <<val << endl;
    }

}


Node * avlTree::minimum(Node * root) {
  Node * current = root;
  while(current->left != NULL) {
    current = current->left;
  }
  return current;
}

Node * avlTree::maximum(Node * root) {
  Node * current = root;
  while(current->right != NULL) {
    current = current->right;
  }
  return current;
}
