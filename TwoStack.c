/*
Two stack using array
push1 ,push2 ,pop1,pop2,display1,display2,check for full or empty
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int arr[MAX];
int top1 = -1;
int top2 = MAX;

void push1(int value)
{
    if (top1 < top2 - 1)
    {
        arr[++top1] = value;
    }
    else
    {
        printf("Stack 1 Overflow\n");
    }
}

void push2(int value)
{
    if (top1 < top2 - 1)
    {
        arr[--top2] = value;
    }
    else
    {
        printf("Stack 2 Overflow\n");
    }
}

int pop1()
{
    if (top1 >= 0)
    {
        return arr[top1--];
    }
    else
    {
        printf("Stack 1 Underflow\n");
        return -1;
    }
}

int pop2()
{
    if (top2 < MAX)
    {
        return arr[top2++];
    }
    else
    {
        printf("Stack 2 Underflow\n");
        return -1;
    }
}

int isStack1Full()
{
    return top1 >= top2 - 1;
}

int isStack2Full()
{
    return top1 >= top2 - 1;
}

int isStack1Empty()
{
    return top1 == -1;
}

int isStack2Empty()
{
    return top2 == MAX;
}

void displayStack1()
{
    if (top1 >= 0)
    {
        printf("Stack 1: ");
        for (int i = top1; i >= 0; i--)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
    else
    {
        printf("Stack 1 is empty\n");
    }
}

void displayStack2()
{
    if (top2 < MAX)
    {
        printf("Stack 2: ");
        for (int i = top2; i < MAX; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
    else
    {
        printf("Stack 2 is empty\n");
    }
}

int main()
{
    int choice, value;
    do
    {
        printf("\nMenu:\n");
        printf("1. Push in Stack 1\n");
        printf("2. Push in Stack 2\n");
        printf("3. Pop from Stack 1\n");
        printf("4. Pop from Stack 2\n");
        printf("5. Check if Stack 1 is Full\n");
        printf("6. Check if Stack 2 is Full\n");
        printf("7. Check if Stack 1 is Empty\n");
        printf("8. Check if Stack 2 is Empty\n");
        printf("9. Display Stack 1\n");
        printf("10. Display Stack 2\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value to push in Stack 1: ");
            scanf("%d", &value);
            push1(value);
            break;
        case 2:
            printf("Enter value to push in Stack 2: ");
            scanf("%d", &value);
            push2(value);
            break;
        case 3:
            value = pop1();
            if (value != -1)
            {
                printf("Popped from Stack 1: %d\n", value);
            }
            break;
        case 4:
            value = pop2();
            if (value != -1)
            {
                printf("Popped from Stack 2: %d\n", value);
            }
            break;
        case 5:
            if (isStack1Full())
            {
                printf("Stack 1 is Full\n");
            }
            else
            {
                printf("Stack 1 is not Full\n");
            }
            break;
        case 6:
            if (isStack2Full())
            {
                printf("Stack 2 is Full\n");
            }
            else
            {
                printf("Stack 2 is not Full\n");
            }
            break;
        case 7:
            if (isStack1Empty())
            {
                printf("Stack 1 is Empty\n");
            }
            else
            {
                printf("Stack 1 is not Empty\n");
            }
            break;
        case 8:
            if (isStack2Empty())
            {
                printf("Stack 2 is Empty\n");
            }
            else
            {
                printf("Stack 2 is not Empty\n");
            }
            break;
        case 9:
            displayStack1();
            break;
        case 10:
            displayStack2();
            break;
        case 11:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
            break;
        }
    } while (choice != 11);

    return 0;
}
