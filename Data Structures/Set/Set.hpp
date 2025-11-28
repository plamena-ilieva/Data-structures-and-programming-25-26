#pragma once

class Set {
public:
	~Set() {
		free(root);
		root = nullptr;
	}

	bool contains(int toFind) const {
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
	bool insert(int toAdd) {
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
	bool remove(int toDelete) {
		Node** curr = &root;

		while (*curr)
		{
			if ((*curr)->data == toDelete) {
				//delete the element

				if (!(*curr)->left && !(*curr)->right) //if its a leaf!
				{
					delete *curr;
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

private:
	struct Node {
		Node* left;
		Node* right;
		int data;

		Node(int data, Node* left = nullptr, Node* right = nullptr):
			data(data), left(left), right(right) { }
	};

	Node* root = nullptr;

	void free(Node* root) {
		if (!root) {
			return;
		}
		
		free(root->left);
		free(root->right);
		delete root;
	}
	Node* copyFrom(const Node* root) {
		if (!root) {
			return nullptr;
		}

		Node* result = new Node(root->data);
		result->left = copyFrom(root->left);
		result->right = copyFrom(root->right);
		
		return result;
	}
};
