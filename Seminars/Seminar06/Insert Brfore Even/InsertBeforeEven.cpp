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

int main() {
    Node* list = new Node(8, new Node(5, new Node(10, new Node(4, nullptr))));

    list = insertOddBeforeEven(list);

    print(list);
    freeList(list);
}
