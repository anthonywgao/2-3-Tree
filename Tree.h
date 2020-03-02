#ifndef __TREE_H
#define __TREE_H

#include "Node.h"

class Tree {
private:
	Node* root;

public:
	Tree() {
		root = nullptr;
	}
	~Tree() {
		delete root;
	}
	void insert(const string&);
	void preOrder() const;
	void inOrder() const;
	void postOrder() const;
	void remove(const string&);
	bool search(const string&) const;

private:
	// Add additional functions/variables here
	void pre(Node*)const;
	void in(Node*)const;
	void post(Node*)const;
	Node* find(Node*, const string&)const;
	void split(Node*, Node*, Node*, const string&);
	void emptyNode(Node*);
	bool hasSpare(Node*);
	void redist(Node*);
	void merge(Node*);
};

#endif
