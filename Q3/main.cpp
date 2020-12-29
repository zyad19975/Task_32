#include <iostream>

using namespace std;

/* Link list Node */
struct Node
{
    int data;
    struct Node *next;
};

/*  delete a given node
    it takes two parameters the head node and the given data
    it only delete the first node with the given data
*/
void deleteNode(struct Node *head, int Data)
{
    // Base cases
    if (head == NULL)
    {
        cout << "Node " << Data << " Not Found\n";
        return;
    }
    while (head->next != NULL)
    {
        if (head->next->data == Data)
        {
            // Delete the node
            head->next = head->next->next;
            return;
        }
        head = head->next;
    }
    cout << "Node " << Data << " Not Found\n";
}

// A function to print a given linked list
void printList(struct Node *ptr)
{
    while (ptr != NULL)
    {
        cout << ptr->data << " -> ";
        ptr = ptr->next;
    }
    cout << "NULL\n";
}

// function to create a new node.
Node *newNode(int data)
{
    struct Node *temp = new Node;
    temp->data = data;
    temp->next = NULL;
    return temp;
}

/*test*/
int main()
{
    /* Start with the empty list */
    struct Node *head = newNode(1);
    head->next = newNode(2);
    head->next->next = newNode(3);
    head->next->next->next = newNode(4);

    cout << "Given Linked List\n";
    printList(head);

    deleteNode(head, 2);
    deleteNode(head, 3);
    deleteNode(head, 6);

    cout << "Linked List after deletion\n";
    printList(head);

    return 0;
}
