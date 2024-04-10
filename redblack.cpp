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

void enter(Node* &root);
void add(Node* &root,int newData);
void fixer(Node* current,Node* root);
void rRotate(Node* node);
void lRotate(Node* node);
void print(Node* root,int level);//prints out the tree

int main() {
  bool sR = true;
  char input[80];
  Node* root = NULL;

  while (sR == true) {
    cout << "Enter add or quit" << endl;
    cin >> input;
    if(strcmp(input, "add") == 0) {
      enter(root);
    }
    if(strcmp(input, "print") == 0) {
      print(root,0);
    }
    if(strcmp(input, "quit") == 0) {
      enter(root);
    }
  }
  return 0;
}

void enter(Node* &root) {
  int input = 0;
  cout << "enter a number" << endl;
  cin >> input;
  add(root, input);
}

void add(Node* &root,int newData) {//adds the values to the tree
  if(root == NULL) {//when there is nothing in the tree
    root = new Node(newData);
    root ->setC(0);
    return;
  }
  else {// if the root is not null
    Node* current = root;
    Node* parent = NULL;
    bool right = NULL;
    while(current != NULL) {//iterate down the left or right sub trees
      parent = current;
      if(current->getV() > newData) {//left subtree
	current = current ->getL();
	right = false;
      }
      else if(current->getV() < newData) {//right subtree
	current = current -> getR();
	right = true;
      }

  }
    if(right == true) {//set new right node
      parent ->setR(new Node(newData));
      current = parent -> getR();
      current -> setP(parent);
    }
    else if(right == false) {//set new left node
      parent -> setL(new Node(newData));
      current = parent->getL();
      current -> setP(parent);
    }
    fixer(current, root);
  }
}


void fixer(Node* current,Node*root) {
  while(current != root && current -> getP() -> getC() == 1) {//while parent is red
    
    if(current -> getP() == current->getP()->getP()->getR()) {//if uncle is the left child
      Node* uncle = current->getP()->getP()->getL();
      if(uncle -> getC() == 1) {// if parent is red and uncle is red
      
	current -> getP() -> setC(0);
	uncle->setC(0);
	current->getP()->getP()->setC(1);
	current = current->getP()->getP();
      }

      else if(uncle -> getC() == 0 || uncle == NULL) {// parent is red and u is black
	if(current->getP() -> getL() == current) {//current is a left child
	  current = current->getP();
	  rRotate(current);
	}

	current->getP() -> setC(0);
	current ->getP() -> getP() ->setC(1);
	lRotate(current->getP()->getP());
	}
      }
    else {//if uncle is right child
      Node* uncle = current->getP()->getP()->getR();

      if(uncle -> getC() == 1) {// if parent is red and uncle is red
        current -> getP() -> setC(0);
        uncle->setC(0);
        current->getP()->getP()->setC(1);
        current = current->getP()->getP();
      }

      else if(uncle -> getC() == 0 || uncle == NULL) {// parent is red and u is black

	if(current->getP() -> getR() == current) {
          current = current->getP();
          lRotate(current);
        }

        current->getP() -> setC(0);
        current ->getP() -> getP() ->setC(1);
        rRotate(current->getP()->getP());
        }
      }
    if(current == root) {//if the new thing to be changed is the root just set it too black
      current->setC(0);
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

void print(Node* root,int level) {//will print the tree
  if (!root) {//if nothing in tree or nothing left to print
    return;
  }
  print(root->getR(), level + 1);//prints out the left subtree

  for(int i = 0; i < level; i++) {
    cout << "\t";
  }
  cout << 'V' << root->getV() << "C" << root->getC() << endl;//prints the current value
  print(root->getL(), level + 1);//prints the left subtree
}
