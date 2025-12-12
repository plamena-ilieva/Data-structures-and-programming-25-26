#pragma once
#include <iostream>
#include <stack>

class BinaryTree
{
private:
	struct Node {
		Node(Node* left, Node* right, const int& data) : left(left), right(right), data(data)
		{
		}
		Node* left;
		Node* right;
		int data;
	};
	Node* root = nullptr;
public:
	class TreePosition {
		friend class BinaryTree;
		Node** current;
	public:
		TreePosition(Node** current) :current(current)
		{}

		TreePosition goLeft() const
		{
			return TreePosition(&(*current)->left);
		}
		TreePosition goRight() const
		{
			return TreePosition(&(*current)->right);
		}
		int& get()
		{
			return (*current)->data;
		}
		int get() const {
			return (*current)->data;
		}
	};

	void erase(TreePosition position)  //изтрива надолу
	{
		erase(position.goLeft());
		erase(position.goRight());
		delete (*position.current);
		(*position.current) = nullptr; //уведомявам родителя!!!
	}
	void add(const std::string& path, int el)
	{
		TreePosition curr(&root);
		for (char ch : path)
		{
			if (ch == 'L')
				curr.goLeft();
			else
				curr.goRight();
		}
		(*curr.current) = new Node(nullptr, nullptr, el);
	}

	void leftRotate(Node** root)
	{

	}
};


int main()
{
}
