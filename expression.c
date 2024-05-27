/*
WAP to convert a given Infix expression into its equivalent
 Postfix  expression and evaluate it using stack.
 Infix :(3+4)*5-2,postFix : 34+5*2-,result : 33

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

// Structure to represent stack
struct Stack
{
    int top;
    int capacity;
    int *array;
};

// Function to create a stack
struct Stack *createStack(int capacity)
{
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int *)malloc(stack->capacity * sizeof(int));
    return stack;
}

// Function to check if the stack is empty
int isEmpty(struct Stack *stack)
{
    return stack->top == -1;
}

// Function to check if the stack is full
int isFull(struct Stack *stack)
{
    return stack->top == stack->capacity - 1;
}

// Function to push an element onto the stack
void push(struct Stack *stack, int item)
{
    if (isFull(stack))
    {
        printf("Stack Overflow\n");
        return;
    }
    stack->array[++stack->top] = item;
}

// Function to pop an element from the stack
int pop(struct Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack Underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->array[stack->top--];
}

// Function to return the top element of the stack without popping it
int peek(struct Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return stack->array[stack->top];
}

// Function to return the precedence of an operator
int precedence(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    }
    return -1;
}

// Function to convert infix expression to postfix expression
void infixToPostfix(char *infix, char *postfix)
{
    struct Stack *stack = createStack(strlen(infix));
    int i, k;
    for (i = 0, k = -1; infix[i]; ++i)
    {
        if (isalnum(infix[i]))
        {
            postfix[++k] = infix[i];
        }
        else if (infix[i] == '(')
        {
            push(stack, infix[i]);
        }
        else if (infix[i] == ')')
        {
            while (!isEmpty(stack) && peek(stack) != '(')
            {
                postfix[++k] = pop(stack);
            }
            if (!isEmpty(stack) && peek(stack) != '(')
            {
                printf("Invalid Expression\n");
                exit(EXIT_FAILURE);
            }
            else
            {
                pop(stack);
            }
        }
        else
        {
            while (!isEmpty(stack) && precedence(infix[i]) <= precedence(peek(stack)))
            {
                postfix[++k] = pop(stack);
            }
            push(stack, infix[i]);
        }
    }
    while (!isEmpty(stack))
    {
        postfix[++k] = pop(stack);
    }
    postfix[++k] = '\0';
    free(stack->array);
    free(stack);
}

// Function to evaluate postfix expression
int evaluatePostfix(char *postfix)
{
    struct Stack *stack = createStack(strlen(postfix));
    for (int i = 0; postfix[i]; ++i)
    {
        if (isdigit(postfix[i]))
        {
            push(stack, postfix[i] - '0');
        }
        else
        {
            int operand2 = pop(stack);
            int operand1 = pop(stack);
            switch (postfix[i])
            {
            case '+':
                push(stack, operand1 + operand2);
                break;
            case '-':
                push(stack, operand1 - operand2);
                break;
            case '*':
                push(stack, operand1 * operand2);
                break;
            case '/':
                push(stack, operand1 / operand2);
                break;
            }
        }
    }
    int result = pop(stack);
    free(stack->array);
    free(stack);
    return result;
}

int main()
{
    char infix[MAX_SIZE], postfix[MAX_SIZE];
    int choice;
    printf("Enter an infix expression: ");
    scanf("%s", infix);
    do
    {
        printf("\nMenu:\n1. Convert infix to postfix\n2. Evaluate postfix expression\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            infixToPostfix(infix, postfix);
            printf("Postfix expression: %s\n", postfix);
            break;
        case 2:
            infixToPostfix(infix, postfix);
            printf("Postfix expression: %s\n", postfix);
            printf("Result: %d\n", evaluatePostfix(postfix));
            break;
        case 3:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 3);
    return 0;
}
*/

/*
WAP to convert a given Infix expression into its equivalent
Prefix  expression and evaluate it using stack. make menu driven code in c
infix :(3+4)*5-2 , Prefix:-*+3452  ,Result :33
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isOperator(char c)
{
    return (!isalpha(c) && !isdigit(c));
}

int getPriority(char C)
{
    if (C == '-' || C == '+')
        return 1;
    else if (C == '*' || C == '/')
        return 2;
    else if (C == '^')
        return 3;
    return 0;
}

char *infixToPostfix(const char *infix)
{
    char *postfix = malloc(strlen(infix) * 2);
    strcpy(postfix, "");
    strcat(postfix, "(");
    strcat(postfix, infix);
    strcat(postfix, ")");
    int l = strlen(postfix);
    char *output = malloc(l * 2);
    strcpy(output, "");

    int j = 0;
    char char_stack[l];
    int top = -1;

    for (int i = 0; i < l; i++)
    {

        if (isalpha(postfix[i]) || isdigit(postfix[i]))
            output[j++] = postfix[i];
        else if (postfix[i] == '(')
            char_stack[++top] = '(';
        else if (postfix[i] == ')')
        {
            while (char_stack[top] != '(')
            {
                output[j++] = char_stack[top--];
            }
            top--;
        }
        else
        {
            if (isOperator(char_stack[top]))
            {
                if (postfix[i] == '^')
                {
                    while (getPriority(postfix[i]) <= getPriority(char_stack[top]))
                    {
                        output[j++] = char_stack[top--];
                    }
                }
                else
                {
                    while (getPriority(postfix[i]) < getPriority(char_stack[top]))
                    {
                        output[j++] = char_stack[top--];
                    }
                }
                char_stack[++top] = postfix[i];
            }
        }
    }
    while (top != -1)
    {
        output[j++] = char_stack[top--];
    }
    output[j] = '\0';
    return output;
}

char *infixToPrefix(const char *infix)
{
    char *infix_modified = malloc(strlen(infix) + 1);
    strcpy(infix_modified, infix);
    strrev(infix_modified);
    for (int i = 0; i < strlen(infix_modified); i++)
    {
        if (infix_modified[i] == '(')
        {
            infix_modified[i] = ')';
        }
        else if (infix_modified[i] == ')')
        {
            infix_modified[i] = '(';
        }
    }

    char *prefix = infixToPostfix(infix_modified);
    strrev(prefix);

    return prefix;
}

int evaluatePrefix(const char *prefix)
{
    int length = strlen(prefix);
    int stack[length];
    int top = -1;

    for (int i = length - 1; i >= 0; i--)
    {
        if (isdigit(prefix[i]))
        {
            stack[++top] = prefix[i] - '0';
        }
        else
        {
            int operand1 = stack[top--];
            int operand2 = stack[top--];
            switch (prefix[i])
            {
            case '+':
                stack[++top] = operand1 + operand2;
                break;
            case '-':
                stack[++top] = operand1 - operand2;
                break;
            case '*':
                stack[++top] = operand1 * operand2;
                break;
            case '/':
                stack[++top] = operand1 / operand2;
                break;
            }
        }
    }
    return stack[top];
}

int main()
{
    char infix[100];
    int choice;
    printf("Enter an infix expression: ");
    scanf("%s", infix);
    char *prefix = infixToPrefix(infix);

    do
    {
        printf("\nMenu:\n1. Prefix expression\n2. Evaluate expression\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Prefix expression: %s\n", prefix);
            break;
        case 2:
            printf("Result: %d\n", evaluatePrefix(prefix));
            break;
        case 3:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 3);

    free(prefix);
    return 0;
}
