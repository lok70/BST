#pragma once
#include <iostream>
#include <stack>
#include <queue>
#include <functional>


class BST
{
private:
	struct node
	{
		int data;
		node* parent;
		node* left;
		node* right;
		node(int d, node* p, node* l = nullptr, node* r = nullptr) :data(d), parent(p), left(l), right(r) {}
	};
public:
	node* root;

	BST(node* r) :root(r) {};

	BST(int d, node* l = nullptr, node* r = nullptr) { root = new node(d, nullptr, l, r); }

	void addToBST(int);

	node* findInBST(int);

	node* findMinInBST();

	node* findMaxInBST();

	node* findFirstLess(int);

	//node* findFirstEqual(int);

	node* findFirstGreater(int);

	void deleteNode(node*);

	void printLRR(node*);

	void printRRL(node*);

	void printByLayers(node*);

	bool equalValues(node*);

	bool equalStructure(node*);

	bool fullEquality(node*);
	~BST() {};



};

