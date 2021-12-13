#pragma once
#include "Node.h"

class BST
{
public:

	//Function to Read and print tree from c:\\temp\\input.txt
	void getfile();

	//Function to read user input
	void readInput(Node *root);

	//Fucntion to dispaly all UI
	void display(Node *root);

	//Function to recursively print tree
	void printTree(Node *root, int x, int y, int width);

	//Function to clear all graphics
	void clearTree();

	//Default Constructor
	BST();

	//Creates a new Node - performs similarly to constructor with pointer
	Node* newNode(int key);

	//Recursively inserts a node into the correct leaf of the tree, returns root - balances as well
	Node* insert(Node* node, int key);

	//Recursively deletes a node into the correct leaf of the tree, returns root - balances as well
	Node* deleteNode(Node* root, int k);

	//Prints the tree in preorder (NLR)
	void preOrder(Node *root);

	//Prints the tree in inorder (LNR)
	void inOrder(Node *root);

	//Prints the tree in postorder (LRN)
	void postOrder(Node *root);

};