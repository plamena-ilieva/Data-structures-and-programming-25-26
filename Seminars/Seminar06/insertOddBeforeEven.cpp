/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>

struct Node {
    Node(int data, Node* next = nullptr) : data(data), next(next) {}
    int data;
    Node* next;
};

void print(const Node* list) {
    while (list) {
        std::cout << list->data;
        if (list->next)
            std::cout << " -> ";
        list = list->next;
    }
    std::cout << '\n';
}

void freeList(Node* list) {
    while (list) {
        Node* toDel = list;
        list = list->next;
        delete toDel;
    }
}

Node* insertOddBeforeEven(Node* list)
{
    Node** curr = &list;   // pointer to pointer to current node

    while (*curr)
    {
        if ( ((*curr)->data % 2) == 0 )
        {
            Node* newNode = new Node((*curr)->data + 1);

            newNode->next = *curr;
            *curr = newNode;

            curr = &((*curr)->next->next);
        }
        else
        {
            // Move forward normally
            curr = &((*curr)->next);
        }
    }

    return list;
}

int main() {
    Node* list = new Node(8, new Node(2, new Node(10, new Node(4, nullptr))));

    list = insertOddBeforeEven(list); // ascending

    print(list);
    freeList(list);
}
