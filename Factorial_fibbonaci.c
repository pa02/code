/*
WAP to implement following by using stack.
 A. Factorial of a given number
  B. Generation of Fibonacci series

*/
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Stack for factorial calculation
int stack1[MAX];
int top1 = -1;

// Stack for Fibonacci series generation
int stack2[MAX];
int top2 = -1;

// Initialize the stack
void initStack(int *top)
{
    *top = -1;
}

// Check if the stack is empty
int isEmpty(int top)
{
    return top == -1;
}

// Check if the stack is full
int isFull(int top)
{
    return top == MAX - 1;
}

// Push an element onto the stack
void push(int stack[], int *top, int value)
{
    if (!isFull(*top))
    {
        stack[++(*top)] = value;
    }
    else
    {
        printf("Stack Overflow\n");
    }
}

// Pop an element from the stack
int pop(int stack[], int *top)
{
    if (!isEmpty(*top))
    {
        return stack[(*top)--];
    }
    else
    {
        printf("Stack Underflow\n");
        return -1;
    }
}

// Function to calculate factorial using stack
int factorial(int n)
{
    initStack(&top1);
    push(stack1, &top1, n);
    int result = 1;
    while (!isEmpty(top1))
    {
        int value = pop(stack1, &top1);
        result *= value;
        if (value - 1 > 0)
        {
            push(stack1, &top1, value - 1);
        }
    }
    return result;
}

// Function to generate the first 10 Fibonacci series using stack
void fibonacci(int n)
{
    if (n <= 0)
    {
        printf("Please enter a positive number.\n");
        return;
    }

    initStack(&top2);
    push(stack2, &top2, 1); // Fibonacci(1)
    push(stack2, &top2, 0); // Fibonacci(0)

    printf("Fibonacci series: ");
    for (int i = 0; i < n; i++)
    {
        int a = pop(stack2, &top2);
        printf("%d ", a);
        int b = pop(stack2, &top2);
        push(stack2, &top2, a);
        push(stack2, &top2, a + b);
    }
    printf("\n");
}

int main()
{
    int choice, n;

    do
    {
        printf("\nMenu:\n");
        printf("1. Calculate Factorial\n");
        printf("2. Generate Fibonacci Series\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter a number to calculate its factorial: ");
            scanf("%d", &n);
            printf("Factorial of %d is %d\n", n, factorial(n));
            break;
        case 2:
            printf("Enter the number of terms for Fibonacci series: ");
            scanf("%d", &n);
            if (n > 0)
            {
                fibonacci(n);
            }
            else
            {
                printf("Please enter a positive number.\n");
            }
            break;
        case 3:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
            break;
        }
    } while (choice != 3);

    return 0;
}
