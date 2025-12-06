#pragma once
#include <iostream>


class Set {
public:
	Set() = default;
	Set(const Set& other);
	~Set();
	bool contains(int toFind) const;
	bool insert(int toAdd);
	bool remove(int toDelete);

private:
	struct Node {
		Node* left;
		Node* right;
		int data;

		Node(int data, Node* left = nullptr, Node* right = nullptr);
	};
	Node** getMin(Node** curr)
	{
		while ((*curr)->left)
			curr = &(*curr)->left;
		return curr;
	}


	Node* root = nullptr;

	void free(Node* root);
	Node* copyFrom(const Node* root);
};

Set::Set(const Set& other){
	root = copyFrom(other.root);
}

Set::~Set() {
	free(root);
	root = nullptr;
}

bool Set::contains(int toFind) const {
	Node* curr = root;

	while (curr) {
		if (curr->data == toFind) {
			return true;
		}
		else if (toFind < curr->data) {
			curr = curr->left;
		}
		else {
			curr = curr->right;
		}
	}

	return false;
}

bool Set::insert(int toAdd) {
	Node** curr = &root;

	while (*curr) {
		if ((*curr)->data == toAdd) {
			return false;
		}
		else if (toAdd < (*curr)->data) {
			curr = &(*curr)->left;
		}
		else {
			curr = &(*curr)->right;
		}
	}

	*curr = new Node(toAdd);
	return true;
}

bool Set::remove(int toDelete) {
	Node** curr = &root;

	while (*curr)
	{
		if ((*curr)->data == toDelete) {
			//delete the element

			if (!(*curr)->left && !(*curr)->right) //if its a leaf!
			{
				delete* curr;
				*curr = nullptr;
			}
			else if (!(*curr)->right) //only left
			{
				Node* toDeleteNode = *curr;
				*curr = (*curr)->left;
				delete toDeleteNode;
			}
			else if (!(*curr)->left) //only right
			{
				Node* toDeleteNode = *curr;
				*curr = (*curr)->right;
				delete toDeleteNode;
			}
			else //if we have two children 
			{
				Node** minFromRight = getMin(&(*curr)->right);

				Node* toDelete = *curr;
				Node* replacement = *minFromRight;

				replacement->left = toDelete->left; //1
				(*minFromRight) = replacement->right; //2

				replacement->right = toDelete->right; //3
				(*curr) = replacement; //4
				delete toDelete;
			}
		}
		else if (toDelete < (*curr)->data) {
			curr = &(*curr)->left;
		}
		else {
			curr = &(*curr)->right;
		}
	}
	return false; //nothing to delete
}

Set::Node::Node(int data, Node* left, Node* right) :
	data(data), left(left), right(right) {
}

void Set::free(Node* root) {
	if (!root) {
		return;
	}

	free(root->left);
	free(root->right);
	delete root;
}

Set::Node* Set::copyFrom(const Node* root) {
	if (!root) {
		return nullptr;
	}

	Node* result = new Node(root->data);
	result->left = copyFrom(root->left);
	result->right = copyFrom(root->right);

	return result;
}
