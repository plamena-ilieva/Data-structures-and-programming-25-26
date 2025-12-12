#pragma once
#include <iostream>
#include <stack>

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

		size_t subTreeSize = 1; //

		static size_t getTreeSize(const Node* tree)
		{
			return tree ? tree->subTreeSize : 0;
		}

		Node(int data, Node* left = nullptr, Node* right = nullptr);
	};

	const Node* getNodeByIndex(const Node* root, size_t index) const
	{
		size_t leftSize = Node::getTreeSize(root->left);
		if (index == leftSize)
			return root;
		if (index < leftSize)
			return getNodeByIndex(root->left, index);
		else
			return getNodeByIndex(root->right, index - leftSize - 1);

	}

	long long getRank(const Node* root, int toRank) const {
		if (!root) {
			throw std::invalid_argument("invalid element");
		}
		if (root->data == toRank) {
			return Node::getTreeSize(root->left);
		}
		if (toRank < root->data) {
			return getRank(root->left, toRank);
		}
		long long leftSize = Node::getTreeSize(root->left);
		long long rightIndex = getRank(root->right, toRank);
		return leftSize + rightIndex + 1;
	}

	Node** getMin(Node** curr)
	{
		while ((*curr)->left)
			curr = &(*curr)->left;
		return curr;
	}


	Node* root = nullptr;

	void free(Node* root);
	Node* copyFrom(const Node* root);
public:

	class ConstForwardIterator {

		void pushLeft(const Set::Node* curr)
		{
			while (curr)
			{
				st.push(curr);
				curr = curr->left;
			}
		}
	public:
		ConstForwardIterator(const Set::Node* root)
		{
			pushLeft(root);
		}
		ConstForwardIterator& operator++() //go to next el
		{
			const Node* currEl = st.top();
			st.pop();
			if (currEl->right)
				pushLeft(currEl->right);
			return *this;
		}

		bool operator==(const ConstForwardIterator& other)
		{
			return st == other.st;
		}

		bool operator!=(const ConstForwardIterator& other)
		{
			return st != other.st;
		}

		int operator*() const //give element that we point to
		{
			return st.top()->data;
		}
	private:
		std::stack<const Node*> st; //top of the stack will be my curr el
	};

	ConstForwardIterator begin() const
	{
		return ConstForwardIterator(root);
	}
	ConstForwardIterator end() const
	{
		return ConstForwardIterator(nullptr);
	}



	int operator[](size_t index) const
	{
		return getNodeByIndex(root, index)->data;
	}

	long long getRank(int el) const {
		return getRank(root, el);
	}
};

Set::Set(const Set& other) {
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
		(*curr)->subTreeSize++; //assume that insert is succesfull 

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

int main()
{
	Set s;

	int arr[] = { 5,1,3,2,6,8,7,9,4,0 };
	for (int i = 0; i < 10; i++)
		s.insert(arr[i]);

	for (int i = 0; i < 10; i++)
		std::cout << s[i] << std::endl;

	for (int i = 0; i < 10; i++)
		std::cout << s.getRank(i) << std::endl;

	for (auto it = s.begin(); it != s.end(); ++it)
	{
		std::cout << (*it);
	}
}
