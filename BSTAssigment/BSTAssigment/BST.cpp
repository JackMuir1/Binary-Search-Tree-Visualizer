#include <iostream>
#include <fstream> //For file reading
#include <string>
#include "BST.h"
#include "Node.h"
#include <windows.h>

using namespace std;

//Default Constructor
BST::BST()
{}

//Handle used for displaying
HANDLE out;

//Fuction to move the cursor in order to display the results
void gotoxy(int x, int y)
{

	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	out = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(out, &csbiInfo);
	csbiInfo.dwCursorPosition.X = x;
	csbiInfo.dwCursorPosition.Y = y;
	SetConsoleCursorPosition(out, csbiInfo.dwCursorPosition);
}

//Function to Read and print tree from c:\\temp\\input.txt
void BST::getfile()
{
	ifstream infile("c:\\temp\\input.txt"); //Input file

	string s; //String used in storing lines from file

	Node *root = NULL; //Started node for created tree

	//temp variable for input storage
	int x;

	while (infile) //Loop through entire file
	{
		//get int from file
		infile >> x;
		//check for -1 to end file
		if (x < 0)
		{
			break;
		}
		//insert values into tree
		root = insert(root, x);
	}
	//GUI for displaying tree from file
	gotoxy(44, 1);
	cout << "displaying file";

	//display tree
	display(root);

	//read user input
	readInput(root);

	//Close file
	infile.close();
}

//Function for reading user input
void BST::readInput(Node *root)
{
	//temp variable for character storage
	char c = 's';

	//loop to get user input on tree edit
	while (c != 'e')
	{
		//GUI prompt
		gotoxy(31, 1);
		cout << "Type a to add node, r to remove node, and e to end:  ";

		//Clear and get new value
		gotoxy(83, 1);
		cin >> c;
		gotoxy(44, 2);

		//Temp value for value of tree
		int x;

		//Add case - user types 'a'
		if (c == 'a')
		{
			//Prompt to add a value
			cout << "Type value to add: ";
			cin >> x;

			//Insert value into tree, then display
			root = insert(root, x);
			display(root);
		}

		//Remove Case - user types 'r'
		else if (c == 'r')
		{
			//Prompt to remove a value
			cout << "Type value to remove: ";
			cin >> x;

			//Delete value then display
			root = deleteNode(root, x);
			display(root);
		}

		//Exit Case - user types 'e'
		else if (c == 'e')
			break;
	}
}

//Function to display the GUI on screen
void BST::display(Node *root)
{
	//Clear previous tree
	clearTree();

	//Print the graphical representation of the tree
	printTree(root, 50, 4, 32);
	gotoxy(40, 20);

	//Print the LNR traversal of the tree
	cout << endl << "The tree in LNR format is: ";
	inOrder(root);

	//Print the NLR traversal of the tree
	cout << endl << "The tree in NLR format is: ";
	preOrder(root);

	//Print the LRN traversal of the tree
	cout << endl << "The tree in LRN format is: ";
	postOrder(root);
	cout << endl;
}

//Function to clear previous tree UI
void BST::clearTree()
{
	//Loop through area (lengthh, then height), under text prompt, clearing screen
	for (int i = 0; i < 100; i++)
	{
		for (int j = 2; j < 24; j++)
		{
			gotoxy(i, j);
			cout << " ";
		}
	}
}

//Function to recursively print the tree graphically
void BST::printTree(Node *root, int x, int y, int width)
{
	//Base Case - null node
	if (root == nullptr)
		return;

	//Go to left place
	gotoxy(x - width / 2, y);
	//Set color to blue
	SetConsoleTextAttribute(out, 11);

	//Print left side
	if (root->left != nullptr)
	{
		//Draw line to next node with animation
		for (int i = width / 2; i > 0; i--)
		{
			cout << "-"; //Dash for horizontal line
			Sleep(20);
		}
		//Go down one place for bottom part of tree connection
		gotoxy(x - width / 2, y + 1); 
		cout << "|";
	}

	//Set color back to white, then print value
	SetConsoleTextAttribute(out, 15);
	gotoxy(x, y);
	cout << root->key;
	SetConsoleTextAttribute(out, 11);

	//Print right side
	if (root->right != nullptr)
	{
		//Draw line to next node with animation
		for (int i = 0; i < width / 2; i++)
		{
			cout << "-"; //Dash for horizontal line
			Sleep(20);
		}
		//Go down one place for bottom part of tree connection
		gotoxy(x + width / 2, y + 1);
		cout << "|";
	}

	//Set color back to white
	SetConsoleTextAttribute(out, 15);
	
	//Move down one line, half the width
	cout << endl;
	width = width / 2;

	//Recursively continue with tree until all leaves reached
	printTree(root->right, x + width, y + 2, width);
	printTree(root->left, x - width, y + 2, width);
}

//Prints the tree in preorder (NLR)
void BST::preOrder(Node *root)
{
	if (root != NULL)
	{
		cout << root->key << " "; //N
		preOrder(root->left); //L
		preOrder(root->right); //R
	}
}

//Prints the tree in inorder (LNR)
void BST::inOrder(Node *root)
{
	if (!root) {
		return;
	}
	inOrder(root->left); //L
	cout << root->key << " "; //N
	inOrder(root->right); //R
}

//Prints the tree in postorder (LRN)
void BST::postOrder(Node *root)
{
	if (root == NULL)
		return;
	postOrder(root->left); //L
	postOrder(root->right); //R
	cout << root->key << " "; //N
}

//NODE FUNCTIONS

//Creates a new Node - performs similarly to constructor with pointer
Node* BST::newNode(int key)
{
	//Creates new Node with key and height 1
	Node* node = new Node();
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	return(node);
}

//INSERTION AND DELETION FUNCTIONS

//Recursively inserts a node into the correct leaf of the tree, returns root
Node* BST::insert(Node* node, int key)
{
	//Base Case- Insert a node into empty tree
	if (node == NULL)
		return(newNode(key));

	//Right Case - Larger Nodes to the right
	if (key > node->key)
		node->right = insert(node->right, key);

	//Left Case - Smaller Nodes to the Left
	else
		node->left = insert(node->left, key);

	return node;
}

//Recursively deletes a node into the correct leaf of the tree, returns root
Node* BST::deleteNode(Node* root, int k)
{
	// Base case
	if (root == NULL)
		return root;

	// Recursive calls for next node to be deleted
	//Left Case
	if (root->key > k) 
	{
		root->left = deleteNode(root->left, k);
		return root;
	}
	//Right Case
	else if (root->key < k) 
	{
		root->right = deleteNode(root->right, k);
		return root;
	}


	// If one of the children is empty
	//Left Null case
	if (root->left == NULL)
	{
		//Delete root and move right to roots place
		Node* temp = root->right;
		delete root;
		return temp;
	}

	//Right Null case
	else if (root->right == NULL)
	{
		//Delete root and move left to roots place
		Node* temp = root->left;
		delete root;
		return temp;
	}

	// If both children exist
	else
	{

		Node* succParent = root;

		// Find successor
		Node* succ = root->right;
		while (succ->left != NULL)
		{
			succParent = succ;
			succ = succ->left;
		}

		// Delete successor
		if (succParent != root)
			succParent->left = succ->right;
		else
			succParent->right = succ->right;

		// Copy Successor Data to root
		root->key = succ->key;

		// Delete Successor and return root
		delete succ;
		return root;
	}
}
