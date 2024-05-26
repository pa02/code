/*
Write a Program to create a Binary Tree and perform following Non-recursive operations on it.
a.preoder Traversal
b.inorder Traversal
c. postorder Traversal
d. display leaf Node
e. Mirror image
f. display total Number of nodes
g. height of the tree
h. mirror image with and  without disturbing the original tree
i. level wise Traversal

*/

#include <stdio.h>
#include <stdlib.h>

// Define the structure for the binary tree node
struct node
{
    int data;
    struct node *left;
    struct node *right;
};

// Function to create a new tree node
struct node *createNode(int data)
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a key into the binary tree (BST-like insertion)
struct node *insert(struct node *root, int data)
{
    struct node *newNode = createNode(data);
    struct node *current = root;
    struct node *parent = NULL;

    if (root == NULL)
    {
        return newNode;
    }

    while (current != NULL)
    {
        parent = current;
        if (data < current->data)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    if (data < parent->data)
    {
        parent->left = newNode;
    }
    else
    {
        parent->right = newNode;
    }

    return root;
}

// Function to find the minimum value node in the BST
struct node *findMin(struct node *root)
{
    while (root->left != NULL)
        root = root->left;
    return root;
}

// Function to delete a key from the binary tree (BST-like deletion)
struct node *delete(struct node *root, int data)
{
    if (root == NULL)
        return root;

    struct node *parent = NULL;
    struct node *current = root;

    // Find the node to be deleted and its parent
    while (current != NULL && current->data != data)
    {
        parent = current;
        if (data < current->data)
            current = current->left;
        else
            current = current->right;
    }

    if (current == NULL)
    {
        printf("Node not found!\n");
        return root;
    }

    // Case 1: Node to be deleted has no children
    if (current->left == NULL && current->right == NULL)
    {
        if (current != root)
        {
            if (parent->left == current)
                parent->left = NULL;
            else
                parent->right = NULL;
        }
        else
        {
            root = NULL;
        }
        free(current);
    }
    // Case 2: Node to be deleted has two children
    else if (current->left && current->right)
    {
        struct node *successor = findMin(current->right);
        int val = successor->data;
        delete (root, successor->data);
        current->data = val;
    }
    // Case 3: Node to be deleted has one child
    else
    {
        struct node *child = (current->left) ? current->left : current->right;
        if (current != root)
        {
            if (current == parent->left)
                parent->left = child;
            else
                parent->right = child;
        }
        else
        {
            root = child;
        }
        free(current);
    }
    return root;
}

// Function to find a node in the binary tree
struct node *find(struct node *root, int data)
{
    while (root != NULL && root->data != data)
    {
        if (data < root->data)
            root = root->left;
        else
            root = root->right;
    }
    return root;
}

// Function to perform non-recursive preorder traversal
void preorderTraversal(struct node *root)
{
    if (root == NULL)
    {
        return;
    }

    struct node *stack[100];
    int top = -1;
    stack[++top] = root;

    while (top >= 0)
    {
        struct node *current = stack[top--];
        printf("%d ", current->data);

        if (current->right != NULL)
        {
            stack[++top] = current->right;
        }
        if (current->left != NULL)
        {
            stack[++top] = current->left;
        }
    }
}

// Function to perform non-recursive inorder traversal
void inorderTraversal(struct node *root)
{
    if (root == NULL)
    {
        return;
    }

    struct node *stack[100];
    int top = -1;
    struct node *current = root;

    while (current != NULL || top != -1)
    {
        while (current != NULL)
        {
            stack[++top] = current;
            current = current->left;
        }

        current = stack[top--];
        printf("%d ", current->data);
        current = current->right;
    }
}

// Function to perform non-recursive postorder traversal
void postorderTraversal(struct node *root)
{
    if (root == NULL)
    {
        return;
    }

    struct node *stack1[100];
    struct node *stack2[100];
    int top1 = -1, top2 = -1;

    stack1[++top1] = root;

    while (top1 >= 0)
    {
        struct node *current = stack1[top1--];
        stack2[++top2] = current;

        if (current->left != NULL)
        {
            stack1[++top1] = current->left;
        }
        if (current->right != NULL)
        {
            stack1[++top1] = current->right;
        }
    }

    while (top2 >= 0)
    {
        printf("%d ", stack2[top2--]->data);
    }
}

// Function to display leaf nodes non-recursively
void displayLeafNodes(struct node *root)
{
    if (root == NULL)
    {
        return;
    }

    struct node *stack[100];
    int top = -1;
    stack[++top] = root;

    while (top >= 0)
    {
        struct node *current = stack[top--];

        if (current->left == NULL && current->right == NULL)
        {
            printf("%d ", current->data);
        }

        if (current->right != NULL)
        {
            stack[++top] = current->right;
        }
        if (current->left != NULL)
        {
            stack[++top] = current->left;
        }
    }
}

// Function to create the mirror image of the tree non-recursively
void mirrorImage(struct node *root)
{
    if (root == NULL)
    {
        return;
    }

    struct node *stack[100];
    int top = -1;
    stack[++top] = root;

    while (top >= 0)
    {
        struct node *current = stack[top--];

        struct node *temp = current->left;
        current->left = current->right;
        current->right = temp;

        if (current->left != NULL)
        {
            stack[++top] = current->left;
        }
        if (current->right != NULL)
        {
            stack[++top] = current->right;
        }
    }
}

// Function to count the total number of nodes non-recursively
int countTotalNodes(struct node *root)
{
    if (root == NULL)
    {
        return 0;
    }

    struct node *stack[100];
    int top = -1;
    stack[++top] = root;
    int count = 0;

    while (top >= 0)
    {
        struct node *current = stack[top--];
        count++;

        if (current->right != NULL)
        {
            stack[++top] = current->right;
        }
        if (current->left != NULL)
        {
            stack[++top] = current->left;
        }
    }

    return count;
}

// Function to find the height of the tree non-recursively
int findHeight(struct node *root)
{
    if (root == NULL)
    {
        return 0;
    }

    struct node *queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;
    int height = 0;

    while (front < rear)
    {
        int nodeCount = rear - front;
        height++;

        while (nodeCount > 0)
        {
            struct node *current = queue[front++];
            if (current->left != NULL)
            {
                queue[rear++] = current->left;
            }
            if (current->right != NULL)
            {
                queue[rear++] = current->right;
            }
            nodeCount--;
        }
    }

    return height;
}

// Function to perform level-wise traversal
void levelOrderTraversal(struct node *root)
{
    if (root == NULL)
    {
        return;
    }

    struct node *queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear)
    {
        struct node *current = queue[front++];
        printf("%d ", current->data);

        if (current->left != NULL)
        {
            queue[rear++] = current->left;
        }
        if (current->right != NULL)
        {
            queue[rear++] = current->right;
        }
    }
}

// Function to create a mirror image without disturbing the original tree
struct node *mirrorImageWithoutDisturbing(struct node *root)
{
    if (root == NULL)
    {
        return NULL;
    }

    struct node *newNode = createNode(root->data);
    newNode->left = mirrorImageWithoutDisturbing(root->right);
    newNode->right = mirrorImageWithoutDisturbing(root->left);
    return newNode;
}

// Main function for demonstration
int main()
{
    struct node *root = NULL;
    int choice, data;

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Find\n");
        printf("4. Preorder Traversal\n");
        printf("5. Inorder Traversal\n");
        printf("6. Postorder Traversal\n");
        printf("7. Display Leaf Nodes\n");
        printf("8. Mirror Image\n");
        printf("9. Display Total Number of Nodes\n");
        printf("10. Height of the Tree\n");
        printf("11. Mirror Image Without Disturbing Original Tree\n");
        printf("12. Level-wise Traversal\n");
        printf("13. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter key to insert: ");
            scanf("%d", &data);
            root = insert(root, data);
            printf("Key inserted successfully.\n");
            break;
        case 2:
            printf("Enter key to delete: ");
            scanf("%d", &data);
            root = delete (root, data);
            printf("Key deleted successfully.\n");
            break;
        case 3:
            printf("Enter key to find: ");
            scanf("%d", &data);
            struct node *foundNode = find(root, data);
            if (foundNode)
            {
                printf("Node found with key: %d\n", foundNode->data);
            }
            else
            {
                printf("Node not found!\n");
            }
            break;
        case 4:
            printf("Preorder Traversal:\n");
            preorderTraversal(root);
            printf("\n");
            break;
        case 5:
            printf("Inorder Traversal:\n");
            inorderTraversal(root);
            printf("\n");
            break;
        case 6:
            printf("Postorder Traversal:\n");
            postorderTraversal(root);
            printf("\n");
            break;
        case 7:
            printf("Leaf Nodes:\n");
            displayLeafNodes(root);
            printf("\n");
            break;
        case 8:
            printf("Mirror Image of the Tree:\n");
            mirrorImage(root);
            inorderTraversal(root); // Display the tree to show the mirror image
            printf("\n");
            break;
        case 9:
            printf("Total Number of Nodes: %d\n", countTotalNodes(root));
            break;
        case 10:
            printf("Height of the Tree: %d\n", findHeight(root));
            break;
        case 11:
            printf("Mirror Image Without Disturbing Original Tree:\n");
            struct node *mirroredRoot = mirrorImageWithoutDisturbing(root);
            inorderTraversal(mirroredRoot); // Display the tree to show the mirror image
            printf("\n");
            break;
        case 12:
            printf("Level-wise Traversal:\n");
            levelOrderTraversal(root);
            printf("\n");
            break;
        case 13:
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
