/*

Write a Program to create a Binary Tree and perform following non-recursive operations on it.
 a. Inorder Traversal
 b. preorder Traversal
 c. postorder Traversal
 d. count leaf nodes
 e. count total number of nodes
 g. Mirror Image
 f. display leaf node

 f. display height of tree
 g. level wise travesal

*/

#include <stdio.h>
#include <stdlib.h>

// Define the structure for the binary tree node
typedef struct TreeNode
{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Define a structure for the stack node
typedef struct StackNode
{
    TreeNode *treeNode;
    struct StackNode *next;
} StackNode;

// Function to create a new tree node
TreeNode *createNode(int data)
{
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to push a tree node onto the stack
void push(StackNode **top, TreeNode *treeNode)
{
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->treeNode = treeNode;
    newNode->next = *top;
    *top = newNode;
}

// Function to pop a tree node from the stack
TreeNode *pop(StackNode **top)
{
    if (*top == NULL)
    {
        printf("Stack is empty!\n");
        exit(1);
    }
    TreeNode *treeNode = (*top)->treeNode;
    StackNode *temp = *top;
    *top = (*top)->next;
    free(temp);
    return treeNode;
}

// Function to check if the stack is empty
int isEmpty(StackNode *top)
{
    return top == NULL;
}

// Function to perform inorder traversal iteratively
void inorderTraversal(TreeNode *root)
{
    if (root == NULL)
        return;

    StackNode *stack = NULL;
    TreeNode *current = root;

    while (current != NULL || !isEmpty(stack))
    {
        while (current != NULL)
        {
            push(&stack, current);
            current = current->left;
        }

        current = pop(&stack);
        printf("%d ", current->data);
        current = current->right;
    }
}

// Function to perform preorder traversal iteratively
void preorderTraversal(TreeNode *root)
{
    if (root == NULL)
        return;

    StackNode *stack = NULL;
    push(&stack, root);

    while (!isEmpty(stack))
    {
        TreeNode *current = pop(&stack);
        printf("%d ", current->data);

        if (current->right != NULL)
            push(&stack, current->right);

        if (current->left != NULL)
            push(&stack, current->left);
    }
}

// Function to perform postorder traversal iteratively
void postorderTraversal(TreeNode *root)
{
    if (root == NULL)
        return;

    StackNode *stack1 = NULL;
    StackNode *stack2 = NULL;
    push(&stack1, root);

    while (!isEmpty(stack1))
    {
        TreeNode *current = pop(&stack1);
        push(&stack2, current);

        if (current->left != NULL)
            push(&stack1, current->left);

        if (current->right != NULL)
            push(&stack1, current->right);
    }

    while (!isEmpty(stack2))
    {
        TreeNode *current = pop(&stack2);
        printf("%d ", current->data);
    }
}

// count the lelaf nodes and total count of leaf node
int countLeafNodes(TreeNode *root)
{
    if (root == NULL)
        return 0;

    int count = 0;
    StackNode *stack = NULL;
    push(&stack, root);

    printf("\nLeaf element are :\n");
    while (!isEmpty(stack))
    {
        TreeNode *current = pop(&stack);
        if (current->left == NULL && current->right == NULL)
        {
            printf("%d  ", current->data);
            count++;
        }
        if (current->right != NULL)
        {
            push(&stack, current->right);
        }

        if (current->left != NULL)
        {
            push(&stack, current->left);
        }
    }
    printf("\n");
    return count;
}

// Function to count total number of nodes
int countTotalNodes(TreeNode *root)
{
    if (root == NULL)
        return 0;

    int count = 0;
    StackNode *stack = NULL;
    push(&stack, root);

    while (!isEmpty(stack))
    {
        TreeNode *current = pop(&stack);
        count++;

        if (current->right != NULL)
            push(&stack, current->right);

        if (current->left != NULL)
            push(&stack, current->left);
    }

    return count;
}

// Function to create the mirror image of the binary tree
void mirror(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }

    StackNode *stack = NULL;
    push(&stack, root);

    while (!isEmpty(stack))
    {
        TreeNode *current = pop(&stack);
        TreeNode *temp = current->left;
        current->left = current->right;
        current->right = temp;

        if (current->left != NULL)
        {
            push(&stack, current->left);
        }
        if (current->right != NULL)
        {
            push(&stack, current->right);
        }
    }
}

// Example usage
int main()
{
    // Create the binary tree
    TreeNode *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);

    // Perform non-recursive operations
    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n");

    printf("Preorder Traversal: ");
    preorderTraversal(root);
    printf("\n");

    printf("Postorder Traversal: ");
    postorderTraversal(root);
    printf("\n");

    printf("Number of Leaf Nodes: %d\n", countLeafNodes(root));
    printf("Total Number of Nodes: %d\n", countTotalNodes(root));

    // Mirror the binary tree
    mirror(root);

    printf("Inorder Traversal of Mirror Image: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
