/*
Write a Program to implement circular double ended queue where user can
add and remove the elements from both front and rear of the queue


#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct
{
    int deque[MAX];
    int front;
    int rear;
    int size;
} CircularDeque;

// Initialize the deque
void initDeque(CircularDeque *dq)
{
    dq->front = -1;
    dq->rear = -1;
    dq->size = 0;
}

// Check if the deque is empty
int isEmpty(CircularDeque *dq)
{
    return dq->size == 0;
}

// Check if the deque is full
int isFull(CircularDeque *dq)
{
    return dq->size == MAX;
}

// Add an element to the front
void addFront(CircularDeque *dq, int value)
{
    if (isFull(dq))
    {
        printf("Deque is full!\n");
        return;
    }
    if (isEmpty(dq))
    {
        dq->front = dq->rear = 0;
    }
    else
    {
        dq->front = (dq->front - 1 + MAX) % MAX;
    }
    dq->deque[dq->front] = value;
    dq->size++;
}

// Add an element to the rear
void addRear(CircularDeque *dq, int value)
{
    if (isFull(dq))
    {
        printf("Deque is full!\n");
        return;
    }
    if (isEmpty(dq))
    {
        dq->front = dq->rear = 0;
    }
    else
    {
        dq->rear = (dq->rear + 1) % MAX;
    }
    dq->deque[dq->rear] = value;
    dq->size++;
}

// Remove an element from the front
int removeFront(CircularDeque *dq)
{
    if (isEmpty(dq))
    {
        printf("Deque is empty!\n");
        return -1;
    }
    int value = dq->deque[dq->front];
    if (dq->front == dq->rear)
    {
        dq->front = dq->rear = -1;
    }
    else
    {
        dq->front = (dq->front + 1) % MAX;
    }
    dq->size--;
    return value;
}

// Remove an element from the rear
int removeRear(CircularDeque *dq)
{
    if (isEmpty(dq))
    {
        printf("Deque is empty!\n");
        return -1;
    }
    int value = dq->deque[dq->rear];
    if (dq->front == dq->rear)
    {
        dq->front = dq->rear = -1;
    }
    else
    {
        dq->rear = (dq->rear - 1 + MAX) % MAX;
    }
    dq->size--;
    return value;
}

// Display the deque
void displayDeque(CircularDeque *dq)
{
    if (isEmpty(dq))
    {
        printf("Deque is empty!\n");
        return;
    }
    printf("Deque: ");
    int i = dq->front;
    while (1)
    {
        printf("%d ", dq->deque[i]);
        if (i == dq->rear)
            break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main()
{
    CircularDeque dq;
    initDeque(&dq);
    int choice, value;

    do
    {
        printf("\nMenu:\n");
        printf("1. Add to Front\n");
        printf("2. Add to Rear\n");
        printf("3. Remove from Front\n");
        printf("4. Remove from Rear\n");
        printf("5. Display Deque\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value to add to front: ");
            scanf("%d", &value);
            addFront(&dq, value);
            break;
        case 2:
            printf("Enter value to add to rear: ");
            scanf("%d", &value);
            addRear(&dq, value);
            break;
        case 3:
            value = removeFront(&dq);
            if (value != -1)
                printf("Removed from front: %d\n", value);
            break;
        case 4:
            value = removeRear(&dq);
            if (value != -1)
                printf("Removed from rear: %d\n", value);
            break;
        case 5:
            displayDeque(&dq);
            break;
        case 6:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
            break;
        }
    } while (choice != 6);

    return 0;
}
*/

/*
Write a Program to implement multiple two queues using array and
perform following operations on it. A. Addq, B. Delq, C. Display Queue
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Global variables to manage the queues
int arr[MAX];
int front1, rear1;
int front2, rear2;

// Initialize the queues
void initQueues()
{
    front1 = 0;
    rear1 = -1;
    front2 = MAX / 2;
    rear2 = (MAX / 2) - 1;
}

// Check if Queue1 is empty
int isEmpty1()
{
    return front1 > rear1;
}

// Check if Queue2 is empty
int isEmpty2()
{
    return front2 > rear2;
}

// Check if Queue1 is full
int isFull1()
{
    return rear1 == (MAX / 2) - 1;
}

// Check if Queue2 is full
int isFull2()
{
    return rear2 == MAX - 1;
}

// Add element to Queue1
void addq1(int value)
{
    if (isFull1())
    {
        printf("Queue1 is full!\n");
    }
    else
    {
        arr[++rear1] = value;
    }
}

// Add element to Queue2
void addq2(int value)
{
    if (isFull2())
    {
        printf("Queue2 is full!\n");
    }
    else
    {
        arr[++rear2] = value;
    }
}

// Delete element from Queue1
int delq1()
{
    if (isEmpty1())
    {
        printf("Queue1 is empty!\n");
        return -1;
    }
    else
    {
        return arr[front1++];
    }
}

// Delete element from Queue2
int delq2()
{
    if (isEmpty2())
    {
        printf("Queue2 is empty!\n");
        return -1;
    }
    else
    {
        return arr[front2++];
    }
}

// Display elements of Queue1
void displayQueue1()
{
    if (isEmpty1())
    {
        printf("Queue1 is empty!\n");
    }
    else
    {
        printf("Queue1: ");
        for (int i = front1; i <= rear1; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
}

// Display elements of Queue2
void displayQueue2()
{
    if (isEmpty2())
    {
        printf("Queue2 is empty!\n");
    }
    else
    {
        printf("Queue2: ");
        for (int i = front2; i <= rear2; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
}

int main()
{
    initQueues();
    int choice, value, queueNum;

    do
    {
        printf("\nMenu:\n");
        printf("1. Add to Queue\n");
        printf("2. Delete from Queue\n");
        printf("3. Display Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter queue number (1 or 2): ");
            scanf("%d", &queueNum);
            printf("Enter value to add: ");
            scanf("%d", &value);
            if (queueNum == 1)
            {
                addq1(value);
            }
            else if (queueNum == 2)
            {
                addq2(value);
            }
            else
            {
                printf("Invalid queue number!\n");
            }
            break;
        case 2:
            printf("Enter queue number (1 or 2): ");
            scanf("%d", &queueNum);
            if (queueNum == 1)
            {
                value = delq1();
                if (value != -1)
                    printf("Deleted from Queue1: %d\n", value);
            }
            else if (queueNum == 2)
            {
                value = delq2();
                if (value != -1)
                    printf("Deleted from Queue2: %d\n", value);
            }
            else
            {
                printf("Invalid queue number!\n");
            }
            break;
        case 3:
            printf("Enter queue number (1 or 2): ");
            scanf("%d", &queueNum);
            if (queueNum == 1)
            {
                displayQueue1();
            }
            else if (queueNum == 2)
            {
                displayQueue2();
            }
            else
            {
                printf("Invalid queue number!\n");
            }
            break;
        case 4:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
            break;
        }
    } while (choice != 4);

    return 0;
}
