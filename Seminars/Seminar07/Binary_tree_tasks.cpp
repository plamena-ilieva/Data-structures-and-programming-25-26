#include <iostream>
#include <vector>
#include <string>

using namespace std;


struct NodeFull
{
	int value;
	vector<NodeFull*> children;
};

struct Node
{
	Node(int value) :value(value), left(nullptr), right(nullptr)
	{}
	int value;
	Node* left;
	Node* right;
};
bool contains(Node* root, int elem)
{
	if (root == nullptr)
		return false;
	return root->value == elem || contains(root->left, elem) || contains(root->right, elem);
}
int sum(Node* root)
{
	if (root == nullptr)
		return 0;
	return root->value + sum(root->left) + sum(root->right);
}
int max(int a, int b)
{
	return a > b ? a : b;
}
int max(int a, int b, int c)
{
	return max(max(a, b), c);
}
int maxElementInTree(Node* root)
{
	if (root->left == nullptr && root->right == nullptr)
		return root->value;
	else if (root->left == nullptr && root->right != nullptr)
		return max(root->value, maxElementInTree(root->right));
	else if (root->left != nullptr && root->right == nullptr)
		return max(root->value, maxElementInTree(root->left));

	return max(root->value, maxElementInTree(root->left), maxElementInTree(root->right));
}