#include "lab3.h"


void BST::addToBST(int n)
{
	node* p = root;
	while (true)
	{
		if (p->data > n)
		{
			if (p->left == nullptr)
			{
				p->left = new node(n, p);
				return;
			}
			else
				p = p->left;
		}
		else if (p->data == n)
			return;
		else if (p->data < n)
		{
			if (p->right == nullptr)
			{
				p->right = new node(n, p);
				return;
			}
			else
				p = p->right;
		}
	}
}
BST::node* BST::findInBST(int n)
{
	node* p = root;
	while (p != nullptr)
	{
		if (p->data > n)
			p = p->left;
		else if (p->data == n)
			return p;
		else if (p->data < n)
			p = p->right;
	}
	return nullptr;
}
BST::node* BST::findMinInBST()
{
	node* p = root;
	while (true)
	{
		if (p->left == nullptr)
			break;
		else
			p = p->left;
	}
	return p;
}

BST::node* BST::findMaxInBST()
{
	node* p = root;
	while (true)
	{
		if (p->right == nullptr)
			break;
		else
			p = p->right;
	}
	return p;
}
BST::node* BST::findFirstLess(int n)
{
	node* p = root;
	while (true)
	{
		if (p->data < n)
			return p;
		else
			p = p->left;
	}
	return nullptr;
}

//BST::node* BST::findFirstEqual(int n)
//{
//	node* p = root;
//	int lastOp = p->data > n ? 1 : 2;
//	while (p!=nullptr)
//	{
//		if (p->data > n)
//		{
//			if (lastOp == 1)
//				p = p->left;
//			else
//				break;
//		}
//		else if (p->data == n)
//			return p;
//		else if (p->data < n)
//		{
//			if (lastOp == 2)
//				p = p->right;
//			else
//				break;
//		}
//	}
//	return nullptr;
//}

BST::node* BST::findFirstGreater(int n)
{
	node* p = root;
	while (true)
	{
		if (p->data < n)
			return p;
		else
			p = p->right;
	}
	return nullptr;
}

void BST::deleteNode(BST::node* n)
{
	if (n->left == nullptr && n->right == nullptr)
	{
		if (n->parent != nullptr) {
			if (n->parent->left == n)
				n->parent->left = nullptr;
			else if (n->parent->right == n)
				n->parent->right = nullptr;
		}
		if (n == root)
			root = nullptr;
	}
	else if (n->left != nullptr && n->right == nullptr)
	{
		n->left->parent = n->parent;
		if (n->parent != nullptr) {
			if (n->parent->left == n)
				n->parent->left = n->left;
			else if (n->parent->right == n)
				n->parent->right = n->left;
		}
		else {
			root = n->left;
		}
	}
	else if (n->left == nullptr && n->right != nullptr)
	{
		n->right->parent = n->parent;

		if (n->parent != nullptr) {
			if (n->parent->left == n)
				n->parent->left = n->right;
			else if (n->parent->right == n)
				n->parent->right = n->right;
		}
		else {
			root = n->right;
		}
	}
	else if (n->left != nullptr && n->right != nullptr)
	{
		node* p = n->right;
		while (p->left != nullptr)
			p = p->left;

		if (p->parent != n) {
			p->parent->left = p->right;
			if (p->right != nullptr)
				p->right->parent = p->parent;
			p->right = n->right;
			p->right->parent = p;
		}

		p->parent = n->parent;
		p->left = n->left;
		p->left->parent = p;

		if (n->parent != nullptr) {
			if (n->parent->left == n)
				n->parent->left = p;
			else if (n->parent->right == n)
				n->parent->right = p;
		}
		else {
			root = p;
		}
	}
	delete n;
}

void BST::printLRR(node* n)
{
	if (n == nullptr)
		return;
	printLRR(n->left);
	std::cout << n->data << " ";
	printLRR(n->right);
}

void BST::printRRL(node* n)
{
	if (n == nullptr)
		return;
	std::stack<node*> st;
	while (!st.empty()||n!=nullptr)
	{
		while (n != nullptr)
		{
			st.push(n);
			n = n->right;
		}
		n = st.top();
		st.pop();
		std::cout << n->data << " ";
		n = n->left;
	}
}

void BST::printByLayers(node* n)
{
	if (n == nullptr)
		return;
	std::queue<node*> q;
	q.push(n);
	while (!q.empty())
	{
		node* x = q.front();
		q.pop();
		std::cout << x->data << " ";
		if (x->left != nullptr)
			q.push(x->left);
		if (x->right != nullptr)
			q.push(x->right);
	}
}

bool BST::equalValues(BST::node* n)
{
	std::stack<int> rst;
	std::stack<int> nst;
	std::function<void(node*,std::stack<int>&)> eqVal= [&](node* n, std::stack<int>& st)->void
		{
			if (n == nullptr)
				return;
			eqVal(n->left,st);
			st.push(n->data);
			eqVal(n->right,st);
		};
	eqVal(root, rst);
	eqVal(n, nst);
	if (rst.size() != nst.size())
		return false;
	while (!nst.empty())
	{
		if (rst.top() != nst.top())
			return false;
		rst.pop();
		nst.pop();
	}
	return true;
}

bool BST::equalStructure(BST::node* n)
{
	std::function<bool(node*, node*)> eqStr = [&](node* r, node* n)->bool
		{
			if (r == nullptr && n == nullptr)
				return true;
			else if (r == nullptr || n == nullptr)
				return false;
			return eqStr(r->left, n->left) && eqStr(r->right, n->right);
		};
	return eqStr(root, n);
}

bool BST::fullEquality(BST::node* n)
{
	std::function<bool(node*, node*)> fulEq
		= [&](node* r, node* n)->bool
		{
			if (r == nullptr && n == nullptr)
				return true;
			if (r == nullptr || n == nullptr)
				return false;
			if (r->data != n->data)
				return false;
			return fulEq(r->left, n->left) && fulEq(r->right, n->right);
		};
	return fulEq(root, n);
}