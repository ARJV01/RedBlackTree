#include<iostream>
#include<string>
#include<cstring>

using namespace std;

class Node {//node class for binary tree
private:
  int value;
  int color;
  Node* parent;
  Node* right;
  Node* left;
  Node* next;
public:
  Node(int newValue) {//constructor
    left = NULL;
    right = NULL;
    next = NULL;
    color = 1;
    value = newValue;
  }
  int getV() {//returns value
    return value;
  }
  void setV(int newV) {
    value = newV;
  }
  Node* getR() {//returns right
    return right;
  }
  void setR(Node* newRight) {//sets right
    right = newRight;
  }
  Node* getL() {//returns left
    return left;
  }
  void setN(Node* newNext) {//sets next
    next = newNext;
  }
  Node* getN() {//returns next
    return next;
  }
  void setL(Node* newLeft) {//sets left
    left = newLeft;
  }
  int getC() {
    return color;
  }
  void setC(int nC) {
    color = nC;
  }
  Node* getP() {
    return parent;
  }
  void setP(Node* newParent) {
    parent = newParent;
  }
  ~Node() {}//destructor
};

void enter(Node* root);
void add(Node* root,int newData);
void insert(Node* current);
void rRotate(Node* node);
void lRotate(Node* node);
Node* getUncle(Node* current);

int main() {
  bool sR = true;
  char input[80];
  Node* root;

  while (sR == true) {
    cin >> input;
    if(strcmp(input, "add") == 0) {
      enter(root);
    }
  }
  return 0;
}

void enter(Node* root) {
  int input = 0;
  cout << "enter a number" << endl;
  cin >> input;
  add(root, input);
}

void add(Node* root,int newData) {
  Node* current = root;
  Node* parent = NULL;

  if(root == NULL) {
    root = new Node(newData);
  }

  else {
  while(current != NULL) {
    if (current->getV() < newData) {
      parent = current;
      current = current->getR();
    }
    if (current->getV() > newData) {
      parent = current;
      current = current->getL();
    }
    current = new Node(newData);
    current->setP(parent);
  }
  }
  insert(current);
}

void insert(Node* current) {
  Node* uncle = getUncle(current);
  while(current -> getP() -> getC() == 1) {//while parent is red

    if(current -> getP() == current->getP()->getP()->getR()) {//if uncle is the left child 

      if(uncle -> getC() == 1) {// if parent is red and uncle is red
	current -> getP() -> setC(0);
	uncle->setC(0);
	current->getP()->getP()->setC(1);
	current = current->getP()->getP();
      }

      else if(uncle -> getC() == 0) {// parent is red and u is black
	if(current->getP() -> getL() == current) {
	  current = current->getP();
	  rRotate(current->getP());
	}

	current->getP() -> setC(0);
	current ->getP() -> getP() ->setC(1);
	lRotate(current->getP()->getP());
	}
      }
    else {//if uncle is right child
      if(uncle -> getC() == 1) {// if parent is red and uncle is red
        current -> getP() -> setC(0);
        uncle->setC(0);
        current->getP()->getP()->setC(1);
        current = current->getP()->getP();
      }
      else if(uncle -> getC() == 0) {// parent is red and u is black
        if(current->getP() -> getR() == current) {
          current = current->getP();
          lRotate(current->getP());
        }

        current->getP() -> setC(0);
        current ->getP() -> getP() ->setC(1);
        rRotate(current->getP()->getP());
        }
      }
      }
    }

void rRotate(Node* node) {
  Node* parent = node->getP();
  Node* grandparent = parent->getP();
  if (node == node->getP()->getL()) {
    grandparent->setR(node);
    parent->setL(node->getR());
    node->setR(parent);
  }
  else {
    grandparent->setL(node);
    parent->setL(node->getR());
    node->setR(parent);
  }
}


void lRotate(Node* node) {
  Node* parent = node->getP();
  Node* grandparent = parent->getP();
  if (node == node->getP()->getR()) {
    grandparent->setL(node);
    parent->setR(node->getL());
    node->setL(parent);
  }
  else {
    grandparent->setR(node);
    parent->setR(node->getL());
    node->setL(parent);
  }

}

Node* getUncle(Node* current) {
  Node* uncle = NULL;
  if(current -> getP() == current->getP()->getP()->getR()) {
    uncle =  current->getP()->getP()->getL();
   }
  else {
    uncle =  current->getP()->getP()->getR();
  }
  return uncle;
}

