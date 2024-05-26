/*
Write a Program to create a Binary Search Tree and perform following Non-recursive operations on it.
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

// Define the structure for the binary search tree node
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

// Function to insert a key into the BST
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

// Function to delete a key from the BST
struct node *deleteNode(struct node *root, int data)
{
    struct node *parent = NULL;
    struct node *current = root;

    while (current != NULL && current->data != data)
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

    if (current == NULL)
    {
        printf("Node not found!\n");
        return root;
    }

    if (current->left == NULL || current->right == NULL)
    {
        struct node *newCurrent;

        if (current->left == NULL)
            newCurrent = current->right;
        else
            newCurrent = current->left;

        if (parent == NULL)
        {
            free(current);
            return newCurrent;
        }

        if (current == parent->left)
            parent->left = newCurrent;
        else
            parent->right = newCurrent;

        free(current);
    }
    else
    {
        struct node *p = NULL;
        struct node *temp;

        temp = current->right;
        while (temp->left != NULL)
        {
            p = temp;
            temp = temp->left;
        }

        if (p != NULL)
            p->left = temp->right;
        else
            current->right = temp->right;

        current->data = temp->data;
        free(temp);
    }

    return root;
}

// Function to find a key in the BST
struct node *find(struct node *root, int data)
{
    struct node *current = root;
    while (current != NULL)
    {
        if (data == current->data)
            return current;
        else if (data < current->data)
            current = current->left;
        else
            current = current->right;
    }
    return NULL;
}

// Function to perform non-recursive preorder traversal
void preorderTraversal(struct node *root)
{
    if (root == NULL)
        return;

    struct node *stack[100];
    int top = -1;
    stack[++top] = root;

    while (top >= 0)
    {
        struct node *node = stack[top--];
        printf("%d ", node->data);

        if (node->right != NULL)
            stack[++top] = node->right;
        if (node->left != NULL)
            stack[++top] = node->left;
    }
}

// Function to perform non-recursive inorder traversal
void inorderTraversal(struct node *root)
{
    struct node *stack[100];
    int top = -1;
    struct node *current = root;

    while (current != NULL || top >= 0)
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
    struct node *stack1[100];
    struct node *stack2[100];
    int top1 = -1, top2 = -1;
    if (root == NULL)
        return;

    stack1[++top1] = root;
    while (top1 >= 0)
    {
        struct node *node = stack1[top1--];
        stack2[++top2] = node;

        if (node->left != NULL)
            stack1[++top1] = node->left;
        if (node->right != NULL)
            stack1[++top1] = node->right;
    }

    while (top2 >= 0)
    {
        struct node *node = stack2[top2--];
        printf("%d ", node->data);
    }
}

// Function to count the number of leaf nodes non-recursively
int countLeafNodes(struct node *root)
{
    if (root == NULL)
        return 0;

    struct node *stack[100];
    int top = -1;
    stack[++top] = root;
    int leafCount = 0;

    while (top >= 0)
    {
        struct node *node = stack[top--];
        if (node->left == NULL && node->right == NULL)
            leafCount++;
        if (node->right != NULL)
            stack[++top] = node->right;
        if (node->left != NULL)
            stack[++top] = node->left;
    }

    return leafCount;
}

// Function to create the mirror image of the tree non-recursively
void mirrorImage(struct node *root)
{
    if (root == NULL)
        return;

    struct node *stack[100];
    int top = -1;
    stack[++top] = root;

    while (top >= 0)
    {
        struct node *node = stack[top--];
        struct node *temp = node->left;
        node->left = node->right;
        node->right = temp;

        if (node->left != NULL)
            stack[++top] = node->left;
        if (node->right != NULL)
            stack[++top] = node->right;
    }
}

// Function to clone a tree recursively
struct node *cloneTree(struct node *root)
{
    if (root == NULL)
        return NULL;

    struct node *newNode = createNode(root->data);
    newNode->left = cloneTree(root->left);
    newNode->right = cloneTree(root->right);
    return newNode;
}

// Function to count the total number of nodes non-recursively
int countNodes(struct node *root)
{
    if (root == NULL)
        return 0;

    struct node *stack[100];
    int top = -1;
    stack[++top] = root;
    int count = 0;

    while (top >= 0)
    {
        struct node *node = stack[top--];
        count++;
        if (node->right != NULL)
            stack[++top] = node->right;
        if (node->left != NULL)
            stack[++top] = node->left;
    }

    return count;
}

// Function to find the height of the tree non-recursively
int findHeight(struct node *root)
{
    if (root == NULL)
        return 0;

    struct node *queue[100];
    int front = -1, rear = -1;
    queue[++rear] = root;
    int height = 0;

    while (front != rear)
    {
        int nodeCount = rear - front;
        height++;

        while (nodeCount > 0)
        {
            struct node *node = queue[++front];
            if (node->left != NULL)
                queue[++rear] = node->left;
            if (node->right != NULL)
                queue[++rear] = node->right;
            nodeCount--;
        }
    }

    return height;
}

// Function to perform level-wise traversal
void levelOrderTraversal(struct node *root)
{
    if (root == NULL)
        return;

    struct node *queue[100];
    int front = -1, rear = -1;
    queue[++rear] = root;

    while (front != rear)
    {
        struct node *node = queue[++front];
        printf("%d ", node->data);

        if (node->left != NULL)
            queue[++rear] = node->left;
        if (node->right != NULL)
            queue[++rear] = node->right;
    }
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
        printf("11. Mirror Image Without Disturbing the Original Tree\n");
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
            root = deleteNode(root, data);
            printf("Key deleted successfully.\n");
            break;
        case 3:
            printf("Enter key to find: ");
            scanf("%d", &data);
            struct node *foundNode = find(root, data);
            if (foundNode != NULL)
                printf("Key found.\n");
            else
                printf("Key not found.\n");
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
            int leafCount = countLeafNodes(root);
            printf("Total number of leaf nodes: %d\n", leafCount);
            break;
        case 8:
            printf("Mirror Image of the Tree:\n");
            mirrorImage(root);
            inorderTraversal(root);
            printf("\n");
            break;
        case 9:
            printf("Total Number of Nodes: %d\n", countNodes(root));
            break;
        case 10:
            printf("Height of the Tree: %d\n", findHeight(root));
            break;
        case 11:
            printf("Mirror Image Without Disturbing the Original Tree:\n");
            struct node *clone = cloneTree(root);
            mirrorImage(clone);
            inorderTraversal(clone);
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

/*
Write a Program to create a Binary Search Tree and perform deletion of a node from it.
 Also display the tree in nonrecursive postorder way


 #include <stdio.h>
#include <stdlib.h>

// Definition of a node in the binary search tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a node into the binary search tree
struct Node* insertNode(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }
    return root;
}

// Function to find the minimum value node in a binary search tree
struct Node* findMinNode(struct Node* node) {
    struct Node* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Function to delete a node from the binary search tree
struct Node* deleteNode(struct Node* root, int data) {
    if (root == NULL) {
        return root;
    }
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        // Node with only one child or no child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        // Node with two children: Get the inorder successor (smallest in the right subtree)
        struct Node* temp = findMinNode(root->right);
        // Copy the inorder successor's content to this node
        root->data = temp->data;
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to display the binary search tree in non-recursive postorder traversal
void postorder(struct Node* root) {
    if (root == NULL) {
        return;
    }
    struct Node* stack[100];
    int top = -1;
    do {
        // Move to leftmost node
        while (root) {
            // Push root's right child and then root to stack
            if (root->right) {
                stack[++top] = root->right;
            }
            stack[++top] = root;
            // Set root as root's left child
            root = root->left;
        }
        // Pop an item from stack and set it as root
        root = stack[top--];
        // If the popped item has a right child and the right child is at the top of the stack, then remove the right child from the stack, push root back to stack, and set root as root's right child
        if (root->right && stack[top] == root->right) {
            stack[top--] = root;
            root = root->right;
        } else {
            printf("%d ", root->data);
            root = NULL;
        }
    } while (top != -1);
}

// Function to display the binary search tree in inorder traversal
void inorder(struct Node* root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

int main() {
    struct Node* root = NULL;

    // Insert nodes into the binary search tree
    root = insertNode(root, 50);
    root = insertNode(root, 30);
    root = insertNode(root, 70);
    root = insertNode(root, 20);
    root = insertNode(root, 40);
    root = insertNode(root, 60);
    root = insertNode(root, 80);

    printf("Binary Search Tree (inorder): ");
    inorder(root);
    printf("\n");

    // Delete node with data 20
    root = deleteNode(root, 20);
    printf("Binary Search Tree after deletion of 20 (inorder): ");
    inorder(root);
    printf("\n");

    printf("Binary Search Tree (postorder): ");
    postorder(root);
    printf("\n");

    return 0;
}

*/
