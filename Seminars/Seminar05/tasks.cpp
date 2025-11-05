#include <iostream>

struct Node {

    Node(int data, Node* next = nullptr) : data(data), next(next) {}

    Node* next;
    int data;
};

void print(const Node* list)
{
    while (list)
    {
        std::cout << list->data;

        if(list->next)
            std::cout << " -> ";
        list = list->next;
    }
}
void freeList(Node* list)
{
    while (list)
    {
        Node* toDel = list;
        list = list->next;
        delete toDel;
    }
}
template <class Pred>
Node* removeByPred(Node* list, const Pred& pr)
{
    Node** curr = &list;

    while (*curr) //*curr != nullptr
    {
        if (pr((**curr).data)) // (*curr)->data
        {
            Node* toDelete = *curr;
            (*curr) = toDelete->next;
            delete toDelete;
        }
        else
        {
            curr = &(**curr).next;
        }
    }
    return list; //!!!!! i changed it if the head should be deleted
}


void pushBack(Node*& begin, Node*& end, Node* toAdd)
{
    if (begin == nullptr) //empty list
    {
        begin = end = toAdd;
    }
    else
    {
        end->next = toAdd;
        end = toAdd;
    }
}

Node* concatTwoLists(Node* leftBegin, 
                     Node* leftEnd, 
                     Node* rightBegin)
{
    if (!leftBegin)
        return rightBegin;
    leftEnd->next = rightBegin;
    return leftBegin;
}

Node* rearange(Node* list)
{
    Node* evenBegin = nullptr;
    Node* evenEnd = nullptr;

    Node* oddBegin = nullptr;
    Node* oddEnd = nullptr;

    Node* curr = list;
    while (curr)
    {
        if (curr->data % 2 == 0)
            pushBack(evenBegin, evenEnd, curr);
        else
            pushBack(oddBegin, oddEnd, curr);
        curr = curr->next;
    }
    if(evenEnd)
        evenEnd->next = nullptr;
    if (oddEnd)
        oddEnd->next = nullptr;
    return concatTwoLists(evenBegin, evenEnd, oddBegin);

}

int main() {

    Node* list = new Node(8, new Node(2, new Node(10, new Node(4, nullptr))));

    list = rearange(list);

    print(list);


}