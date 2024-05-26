/*
Write an iterative Reverse() function that reverses a list by rearranging all the next pointers and the head pointer.
 Ideally, Reverse() should only need to make one pass of the list
*/
#include <stdio.h>
#include <stdlib.h>

// Definition of a node in the linked list
struct Node
{
    int data;
    struct Node *next;
};

// Function to reverse the linked list iteratively
void Reverse(struct Node **head)
{
    struct Node *prev = NULL;
    struct Node *current = *head;
    struct Node *next = NULL;

    while (current != NULL)
    {
        // Store the next node
        next = current->next;
        // Reverse the current node's pointer
        current->next = prev;
        // Move pointers one position ahead
        prev = current;
        current = next;
    }
    *head = prev;
}

// Function to push a new node at the head of the list
void push(struct Node **head, int new_data)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = *head;
    *head = new_node;
}

// Function to print the linked list
void printList(struct Node *node)
{
    while (node != NULL)
    {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main()
{
    struct Node *head = NULL;

    // Creating a sample linked list
    push(&head, 20);
    push(&head, 15);
    push(&head, 10);
    push(&head, 5);

    printf("Original list: ");
    printList(head);

    // Reverse the linked list
    Reverse(&head);

    printf("Reversed list: ");
    printList(head);

    return 0;
}
