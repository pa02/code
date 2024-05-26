/*
Write a Program to create Inorder Threaded Binary Tree and
1.Traverse it in Preorder way.
2. inoder way
3. postorder way
*/

#include <stdio.h>
#include <stdlib.h>

// Define the structure for the threaded binary tree node
struct TreeNode
{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
    int isThreaded; // Flag to indicate whether right child is a thread or not
};

// Function to create a new tree node
struct TreeNode *createNode(int data)
{
    struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->isThreaded = 0; // Initially, right child is not a thread
    return newNode;
}
/*
// Recusive

// Function to insert a new node into the threaded binary tree
struct TreeNode *insert(struct TreeNode *root, int data)
{
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
    {
        root->left = insert(root->left, data);
    }
    else if (data > root->data)
    {
        if (root->isThreaded)
        {
            struct TreeNode *temp = createNode(data);
            temp->right = root->right;
            temp->isThreaded = 1;
            root->right = temp;
            root->isThreaded = 0;
        }
        else
        {
            root->right = insert(root->right, data);
        }
    }
    return root;
}

// Recursive function to perform inorder traversal of the threaded binary tree
void inorderTraversal(struct TreeNode *root)
{
    if (root == NULL)
        return;

    if (root->left)
        inorderTraversal(root->left);

    printf("%d ", root->data);

    if (!root->isThreaded)
        inorderTraversal(root->right);
}

// Recursive function to perform preorder traversal of the threaded binary tree
void preorderTraversal(struct TreeNode *root)
{
    if (root == NULL)
        return;

    printf("%d ", root->data);

    preorderTraversal(root->left);

    if (!root->isThreaded)
        preorderTraversal(root->right);
}

// Recursive function to perform postorder traversal of the threaded binary tree
void postorderTraversal(struct TreeNode *root)
{
    if (root == NULL)
        return;

    postorderTraversal(root->left);

    if (!root->isThreaded)
        postorderTraversal(root->right);

    printf("%d ", root->data);
}
*/

// NON -Recursive
// Function to insert a new node into the threaded binary tree
struct TreeNode *insert(struct TreeNode *root, int data)
{
    if (root == NULL)
        return createNode(data);

    struct TreeNode *current = root;
    struct TreeNode *parent = NULL;

    while (current != NULL)
    {
        parent = current;
        if (data < current->data)
        {
            if (current->left == NULL)
            {
                current = NULL;
            }
            else
            {
                current = current->left;
            }
        }
        else if (data > current->data)
        {
            if (current->isThreaded)
            {
                current = NULL;
            }
            else
            {
                current = current->right;
            }
        }
        else
        {
            // Duplicate data, do nothing
            return root;
        }
    }

    struct TreeNode *newNode = createNode(data);
    if (data < parent->data)
    {
        parent->left = newNode;
        newNode->right = parent;
        newNode->isThreaded = 1;
    }
    else
    {
        newNode->right = parent->right;
        newNode->isThreaded = 1;
        parent->right = newNode;
        parent->isThreaded = 0;
    }

    return root;
}

// Non-recursive function to perform inorder traversal of the threaded binary tree
void inorderTraversal(struct TreeNode *root)
{
    if (root == NULL)
        return;

    struct TreeNode *current = root;
    while (current->left != NULL)
        current = current->left;

    while (current != NULL)
    {
        printf("%d ", current->data);

        if (current->isThreaded)
            current = current->right;
        else
        {
            current = current->right;
            while (current != NULL && !current->isThreaded)
                current = current->left;
        }
    }
}

// Non-recursive function to perform preorder traversal of the threaded binary tree
void preorderTraversal(struct TreeNode *root)
{
    if (root == NULL)
        return;

    struct TreeNode *current = root;
    while (current != NULL)
    {
        printf("%d ", current->data);

        if (current->left != NULL)
        {
            current = current->left;
        }
        else
        {
            while (current != NULL && current->isThreaded)
            {
                current = current->right;
            }
            if (current != NULL)
            {
                current = current->right;
            }
        }
    }
}

// Non-recursive function to perform postorder traversal of the threaded binary tree
void postorderTraversal(struct TreeNode *root)
{
    if (root == NULL)
        return;

    struct TreeNode *current = root;
    struct TreeNode *prev = NULL;

    while (current != NULL)
    {
        if (current->left == NULL)
        {
            printf("%d ", current->data);
            current = current->right;
        }
        else
        {
            struct TreeNode *predecessor = current->left;
            while (predecessor->right != NULL && predecessor->right != current)
            {
                predecessor = predecessor->right;
            }

            if (predecessor->right == NULL)
            {
                predecessor->right = current;
                current = current->left;
            }
            else
            {
                predecessor->right = NULL;
                printf("%d ", current->data);
                current = current->right;
            }
        }
    }
}

int main()
{
    struct TreeNode *root = NULL;
    int choice, data;

    printf("Menu:\n");
    printf("1. Insert\n");
    printf("2. Inorder Traversal\n");
    printf("3. Preorder Traversal\n");
    printf("4. Postorder Traversal\n");
    printf("5. Exit\n");

    while (1)
    {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &data);
            root = insert(root, data);
            break;
        case 2:
            printf("Inorder Traversal: ");
            inorderTraversal(root);
            printf("\n");
            break;
        case 3:
            printf("Preorder Traversal: ");
            preorderTraversal(root);
            printf("\n");
            break;
        case 4:
            printf("Postorder Traversal: ");
            postorderTraversal(root);
            printf("\n");
            break;
        case 5:
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
