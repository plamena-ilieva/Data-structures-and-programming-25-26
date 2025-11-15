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

template <class Pred>
Node* removeByPred(Node* list, const Pred& pr) {
    Node** curr = &list;
    while (*curr) {
        if (pr((*curr)->data)) {
            Node* toDelete = *curr;
            *curr = (*curr)->next;
            delete toDelete;
        } else {
            curr = &((*curr)->next);
        }
    }
    return list;
}

void pushBack(Node*& begin, Node*& end, Node* toAdd) {
    toAdd->next = nullptr;
    if (!begin)
        begin = end = toAdd;
    else {
        end->next = toAdd;
        end = toAdd;
    }
}

Node* concatTwoLists(Node* leftBegin, Node* leftEnd, Node* rightBegin) {
    if (!leftBegin)
        return rightBegin;
    if (leftEnd)
        leftEnd->next = rightBegin;
    return leftBegin;
}

template <typename Compare>
Node* rearrange(Node* list, Compare comp,
               Node*& leftBegin, Node*& leftEnd,
               Node*& rightBegin, Node*& rightEnd) {
    Node* pivot = list;
    leftBegin = leftEnd = rightBegin = rightEnd = nullptr;

    Node* curr = list->next;

    while (curr) {
        Node* next = curr->next;
        if (comp(curr->data, pivot->data))
            pushBack(leftBegin, leftEnd, curr);
        else
            pushBack(rightBegin, rightEnd, curr);
        curr = next;
    }
    
    return pivot;
}

template <typename Compare>
Node* quickSort(Node* list, Compare comp) {
    if (!list || !list->next)
        return list;

    Node* leftBegin = nullptr;
    Node* leftEnd = nullptr;
    Node* rightBegin = nullptr;
    Node* rightEnd = nullptr;

    Node* pivot = rearrange(list, comp, leftBegin, leftEnd, rightBegin, rightEnd);

    leftBegin = quickSort(leftBegin, comp);
    rightBegin = quickSort(rightBegin, comp);

    // Find tail of left list if it exists
    Node* leftTail = leftEnd;
    if (!leftTail && leftBegin) {
        leftTail = leftBegin;
        while (leftTail->next)
            leftTail = leftTail->next;
    }

    // Connect: left -> pivot -> right
    Node* result = concatTwoLists(leftBegin, leftTail, pivot);
    pivot->next = rightBegin;

    return result;
}

int main() {
    Node* list = new Node(8, new Node(2, new Node(10, new Node(4, nullptr))));

    list = quickSort(list, [](int a, int b) { return a > b; }); // ascending

    print(list);
    freeList(list);
}
