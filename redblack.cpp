#include <iostream>
#include <string>
#include <cstring>

using namespace std;

struct Node
{
    int data;
    Node *parent;
    Node *left;
    Node *right;
    int color;

    Node(int x) : data(x), parent(NULL), left(NULL), right(NULL), color(1) {}
};

void enter(Node *&root);
void add(Node *&root, int newData);
void fixer(Node *current, Node *root);
void rRotate(Node *node, Node *&root);
void lRotate(Node *node, Node *&root);
void print(Node *root, int level); // prints out the tree

int main()
{
    bool sR = true;
    char input[80];
    Node *root = NULL;

    while (sR == true)
    {
        cout << "Enter add or quit" << endl;
        cin >> input;
        if (strcmp(input, "add") == 0)
        {
            enter(root);
        }
        if (strcmp(input, "print") == 0)
        {
            print(root, 0);
        }
        if (strcmp(input, "quit") == 0)
        {
            sR = false;
        }
    }
    return 0;
}

void enter(Node *&root)
{
    int input = 0;
    cout << "enter a number" << endl;
    cin >> input;
    add(root, input);
}

void add(Node *&root, int newData)
{ // adds the values to the tree
    if (root == NULL)
    { // when there is nothing in the tree
        root = new Node(newData);
        root->color = 0;
        return;
    }
    else
    { // if the root is not null
        Node *current = root;
        Node *parent = NULL;
        bool right = NULL;
        while (current != NULL)
        { // iterate down the left or right sub trees
            parent = current;
            if (current->data > newData)
            { // left subtree
                current = current->left;
                right = false;
            }
            else if (current->data < newData)
            { // right subtree
                current = current->right;
                right = true;
            }
        }
        if (right == true)
        { // set new right node
            parent->right = (new Node(newData));
            current = parent->right;
            current->parent = parent;
        }
        else if (right == false)
        { // set new left node
            parent->left = (new Node(newData));
            current = parent->left;
            current->parent = (parent);
        }
        fixer(current, root);
    }
}

void fixer(Node *current, Node *root)
{
    while (current != root && current->parent->color == 1)
    { // while parent is red

        if (current->parent == current->parent->parent->right)
        { // if uncle is the left child
            Node *uncle = current->parent->parent->left;
            if (uncle != NULL && uncle->color == 1)
            { // if parent is red and uncle is red

                current->parent->color = 0;
                uncle->color = 0;
                current->parent->parent->color = 1;
                current = current->parent->parent;
            }

            else if (uncle == NULL || (uncle != NULL && uncle->color == 0))
            { // parent is red and u is black
                if (current->parent->left == current)
                { // current is a left child
                    current = current->parent;
                    rRotate(current, root);
                }

                current->parent->color = 0;
                current->parent->parent->color = 1;
                lRotate(current->parent->parent, root);
            }
        }
        else
        { // if uncle is right child
            Node *uncle = current->parent->parent->right;

            if (uncle != NULL && uncle->color == 1)
            { // if parent is red and uncle is red
                current->parent->color = 0;
                uncle->color = 0;
                current->parent->parent->color = 1;
                current = current->parent->parent;
            }

            else if (uncle == NULL || (uncle != NULL && uncle->color == 0))
            { // parent is red and u is black

                if (current->parent->right == current)
                {
                    current = current->parent;
                    lRotate(current, root);
                }

                current->parent->color = 0;
                current->parent->parent->color = 1;
                rRotate(current->parent->parent, root);
            }
        }
        if (current == root)
        { // if the new thing to be changed is the root just set it too black
            current->color = 0;
        }
    }
}

void print(Node *root, int level)
{ // will print the tree
    if (!root)
    { // if nothing in tree or nothing left to print
        return;
    }
    print(root->right, level + 1); // prints out the left subtree

    for (int i = 0; i < level; i++)
    {
        cout << "\t";
    }
    cout << 'V' << root->data << "C" << root->color << endl; // prints the current value
    print(root->left, level + 1);                            // prints the left subtree
}

void lRotate(Node *node, Node *&root)
{
    Node *y = node->right;
    node->right = y->left;
    if (y->left != NULL)
    {
        y->left->parent = node;
    }
    y->parent = node->parent;

    if (node->parent == NULL)
    {
        root = y;
    }
    else if (node == node->parent->left)
    {
        node->parent->left = y;
    }
    else
    {
        node->parent->right = y;
    }

    y->left = node;
    node->parent = y;
}

void rRotate(Node *node, Node *&root)
{
    Node *x = node->left;
    node->left = x->right;
    if (x->right != NULL)
    {
        x->right->parent = node;
    }
    x->parent = node->parent;

    if (node->parent == NULL)
    {
        root = x;
    }
    else if (node == node->parent->right)
    {
        node->parent->right = x;
    }
    else
    {
        node->parent->left = x;
    }

    x->right = node;
    node->parent = x;
}
