#ifndef __NODE_H
#define __NODE_H

#include <iostream>
#include <string>

using namespace std;

class Node {

	friend class Tree;

private:
	string small;
	string large;

	Node* left;
	Node* middle;
	Node* right;
	Node* parent;

	// Add additional functions/variables here. Remember, you may not add any
	// Node * or string variables.
public:
	Node() {
		small = "";
		large = "";
		left = nullptr;
		//middle is right if node is 2 node
		middle = nullptr;
		right = nullptr;
		parent = nullptr;
	}
};

#endif