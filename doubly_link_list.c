/*
WAP to create doubly linked list and perform following operations on it.
A) Insert (all cases) 2. Delete (all cases).

#include <stdio.h>
#include <stdlib.h>

// Definition of a node in the doubly linked list
struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
};

// Function to create a new node
struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to insert a node at the beginning
void insertAtBeginning(struct Node **head, int data)
{
    struct Node *newNode = createNode(data);
    if (*head != NULL)
    {
        (*head)->prev = newNode;
    }
    newNode->next = *head;
    *head = newNode;
}

// Function to insert a node at the end
void insertAtEnd(struct Node **head, int data)
{
    struct Node *newNode = createNode(data);
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }
    struct Node *temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Function to insert a node after a given node
void insertAfter(struct Node *prevNode, int data)
{
    if (prevNode == NULL)
    {
        printf("The given previous node cannot be NULL\n");
        return;
    }
    struct Node *newNode = createNode(data);
    newNode->next = prevNode->next;
    prevNode->next = newNode;
    newNode->prev = prevNode;
    if (newNode->next != NULL)
    {
        newNode->next->prev = newNode;
    }
}

// Function to delete a node from the beginning
void deleteFromBeginning(struct Node **head)
{
    if (*head == NULL)
    {
        printf("List is empty\n");
        return;
    }
    struct Node *temp = *head;
    *head = (*head)->next;
    if (*head != NULL)
    {
        (*head)->prev = NULL;
    }
    free(temp);
}

// Function to delete a node from the end
void deleteFromEnd(struct Node **head)
{
    if (*head == NULL)
    {
        printf("List is empty\n");
        return;
    }
    struct Node *temp = *head;
    if (temp->next == NULL)
    {
        *head = NULL;
        free(temp);
        return;
    }
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->prev->next = NULL;
    free(temp);
}

// Function to delete a node after a given node
void deleteAfter(struct Node *prevNode)
{
    if (prevNode == NULL || prevNode->next == NULL)
    {
        printf("There is no node to delete\n");
        return;
    }
    struct Node *temp = prevNode->next;
    prevNode->next = temp->next;
    if (temp->next != NULL)
    {
        temp->next->prev = prevNode;
    }
    free(temp);
}

// Function to print the doubly linked list
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
    int choice, data, position;

    do
    {
        printf("\nMenu:\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Insert After a Node\n");
        printf("4. Delete from Beginning\n");
        printf("5. Delete from End\n");
        printf("6. Delete After a Node\n");
        printf("7. Display List\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter data to insert at the beginning: ");
            scanf("%d", &data);
            insertAtBeginning(&head, data);
            break;
        case 2:
            printf("Enter data to insert at the end: ");
            scanf("%d", &data);
            insertAtEnd(&head, data);
            break;
        case 3:
            printf("Enter the data of the node after which you want to insert: ");
            scanf("%d", &position);
            struct Node *temp = head;
            while (temp != NULL && temp->data != position)
            {
                temp = temp->next;
            }
            if (temp == NULL)
            {
                printf("Node with data %d not found\n", position);
            }
            else
            {
                printf("Enter data to insert after node with data %d: ", position);
                scanf("%d", &data);
                insertAfter(temp, data);
            }
            break;
        case 4:
            deleteFromBeginning(&head);
            break;
        case 5:
            deleteFromEnd(&head);
            break;
        case 6:
            printf("Enter the data of the node after which you want to delete: ");
            scanf("%d", &position);
            temp = head;
            while (temp != NULL && temp->data != position)
            {
                temp = temp->next;
            }
            if (temp == NULL)
            {
                printf("Node with data %d not found\n", position);
            }
            else
            {
                deleteAfter(temp);
            }
            break;
        case 7:
            printf("Doubly Linked List: ");
            printList(head);
            break;
        case 8:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
            break;
        }
    } while (choice != 8);

    return 0;
}
*/

/*
WAP to merge two sorted Doubly linked lists and display their result.

#include <stdio.h>
#include <stdlib.h>

// Definition of a node in the doubly linked list
struct Node
{
    int data;
    struct Node *prev;
    struct Node *next;
};

// Function to create a new node
struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the doubly linked list
void insertAtEnd(struct Node **head, int data)
{
    struct Node *newNode = createNode(data);
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }
    struct Node *temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Function to merge two sorted doubly linked lists
struct Node *mergeSortedLists(struct Node *list1, struct Node *list2)
{
    struct Node *mergedList = NULL;
    struct Node *tail = NULL;

    while (list1 != NULL && list2 != NULL)
    {
        if (list1->data <= list2->data)
        {
            if (mergedList == NULL)
            {
                mergedList = tail = list1;
            }
            else
            {
                tail->next = list1;
                list1->prev = tail;
                tail = list1;
            }
            list1 = list1->next;
        }
        else
        {
            if (mergedList == NULL)
            {
                mergedList = tail = list2;
            }
            else
            {
                tail->next = list2;
                list2->prev = tail;
                tail = list2;
            }
            list2 = list2->next;
        }
    }

    if (list1 != NULL)
    {
        tail->next = list1;
        list1->prev = tail;
    }
    else
    {
        tail->next = list2;
        if (list2 != NULL)
        {
            list2->prev = tail;
        }
    }

    return mergedList;
}

// Function to display the doubly linked list
void displayList(struct Node *head)
{
    printf("Doubly Linked List: ");
    while (head != NULL)
    {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main()
{
    struct Node *list1 = NULL;
    struct Node *list2 = NULL;

    // Insert elements into the first sorted doubly linked list
    insertAtEnd(&list1, 1);
    insertAtEnd(&list1, 3);
    insertAtEnd(&list1, 5);

    // Insert elements into the second sorted doubly linked list
    insertAtEnd(&list2, 2);
    insertAtEnd(&list2, 4);
    insertAtEnd(&list2, 6);

    printf("First sorted list:\n");
    displayList(list1);

    printf("Second sorted list:\n");
    displayList(list2);

    // Merge the two sorted lists
    struct Node *mergedList = mergeSortedLists(list1, list2);

    printf("Merged sorted list:\n");
    displayList(mergedList);

    return 0;
}
*/

/*
Implement Push and POP operations of STACK on Doubly linked lists

#include <stdio.h>
#include <stdlib.h>

// Definition of a node in the doubly linked list
struct Node
{
    int data;
    struct Node *prev;
    struct Node *next;
};

// Function to create a new node
struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to push an element onto the stack
void push(struct Node **top, int data)
{
    struct Node *newNode = createNode(data);
    if (*top == NULL)
    {
        *top = newNode;
    }
    else
    {
        newNode->next = *top;
        (*top)->prev = newNode;
        *top = newNode;
    }
    printf("%d pushed onto the stack.\n", data);
}

// Function to pop an element from the stack
int pop(struct Node **top)
{
    if (*top == NULL)
    {
        printf("Stack underflow: Cannot pop from an empty stack.\n");
        return -1;
    }
    int poppedData = (*top)->data;
    struct Node *temp = *top;
    *top = (*top)->next;
    if (*top != NULL)
    {
        (*top)->prev = NULL;
    }
    free(temp);
    printf("%d popped from the stack.\n", poppedData);
    return poppedData;
}

// Function to display the elements of the stack
void displayStack(struct Node *top)
{
    printf("Stack: ");
    while (top != NULL)
    {
        printf("%d ", top->data);
        top = top->next;
    }
    printf("\n");
}

int main()
{
    struct Node *top = NULL;

    push(&top, 10);
    push(&top, 20);
    push(&top, 30);

    displayStack(top);

    pop(&top);
    pop(&top);
    pop(&top);
    pop(&top);

    return 0;
}
*/
