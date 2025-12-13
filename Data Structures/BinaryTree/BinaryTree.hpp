#pragma once
#include <iostream>
#include <stack>
#include <string>

class BinaryTree
{
private:
    struct Node {
        Node(const int& data, Node* left = nullptr, Node* right = nullptr) : left(left), right(right), data(data)
        {
        }
        Node* left;
        Node* right;
        int data;
    };
    Node* root = nullptr;

    static Node* copyNode(const Node* other)
    {
        if (!other) 
            return nullptr;
            
        Node* n = new Node(other->data);
        
        n->left = copyNode(other->left);
        n->right = copyNode(other->right);
        return n;
    }

    static void freeNode(Node* node)
    {
        if (!node) 
            return;
        freeNode(node->left);
        freeNode(node->right);
        
        delete node;
    }

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

    BinaryTree() = default;

    BinaryTree(const BinaryTree& other)
    {
        root = copyNode(other.root);
    }

    BinaryTree& operator=(const BinaryTree& other)
    {
        if (this != &other)
        {
            free();
            root = copyNode(other.root);
        }
        return *this;
    }

    ~BinaryTree()
    {
        free();
    }

    void free()
    {
        freeNode(root);
        root = nullptr;
    }

    void erase(TreePosition position)
    {
        if (!*position.current) 
            return;
    
        erase(position.goLeft());
        erase(position.goRight());
        
        delete (*position.current);
        (*position.current) = nullptr;
    }

    void add(const std::string& path, int el)
    {
        TreePosition curr(&root);
        for (char ch : path)
        {
            if (!*curr.current)
            {
                *curr.current = new Node(0);
            }
            if (ch == 'L')
                curr = curr.goLeft();
            else
                curr = curr.goRight();
        }
        if (!*curr.current)
            *curr.current = new Node(el);
        else
            (*curr.current)->data = el;
    }

    void printInorder() const
    {
        printInorder(root);
        std::cout << std::endl;
    }

private:
    static void printInorder(Node* node)
    {
        if (!node) 
            return;
    
        printInorder(node->left);
        std::cout << node->data << ' ';
        printInorder(node->right);
    }
};


int main()
{
    BinaryTree t;
    t.add("", 10);
    t.add("L", 5);
    t.add("R", 15);
    t.add("LL", 2);
    t.add("LR", 7);

    t.printInorder();
    return 0;
}
