/*
Write a Program to create a Binary  Tree and perform following recursive operations on it.

1.insert
2.delete
3.find
4.preoder Traversal
5.inorder Traversal
6. postorder Traversal
7. display leaf Node
8. Mirror image
9.display total Number of nodes
10.height of the tree
11. mirror image with and  without disturbing the original tree
12. level wise Traversal


*/

#include <stdio.h>
#include <stdlib.h>

// Define the structure for the binary tree node
struct TreeNode
{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Function to create a new tree node
struct TreeNode *createNode(int data)
{
    struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a key into the binary tree
struct TreeNode *insert(struct TreeNode *root, int data)
{
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}
// Function to find the minimum value node in the binary tree
struct TreeNode *findMin(struct TreeNode *root)
{
    while (root->left != NULL)
        root = root->left;
    return root;
}

// Function to delete a key from the binary tree
struct TreeNode *delete(struct TreeNode *root, int key)
{
    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = delete (root->left, key);
    else if (key > root->data)
        root->right = delete (root->right, key);
    else
    {
        if (root->left == NULL)
        {
            struct TreeNode *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct TreeNode *temp = root->left;
            free(root);
            return temp;
        }
        struct TreeNode *temp = findMin(root->right);
        root->data = temp->data;
        root->right = delete (root->right, temp->data);
    }
    return root;
}

// Function to find a key in the binary tree
struct TreeNode *find(struct TreeNode *root, int key)
{
    if (root == NULL || root->data == key)
        return root;

    if (key < root->data)
        return find(root->left, key);
    else
        return find(root->right, key);
}

// Function to perform preorder traversal of the binary tree
void preorderTraversal(struct TreeNode *root)
{
    if (root == NULL)
        return;
    printf("%d ", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// Function to perform inorder traversal of the binary tree
void inorderTraversal(struct TreeNode *root)
{
    if (root == NULL)
        return;
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

// Function to perform postorder traversal of the binary tree
void postorderTraversal(struct TreeNode *root)
{
    if (root == NULL)
        return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d ", root->data);
}

// Function to display leaf nodes of the binary tree
void displayLeafNodes(struct TreeNode *root)
{
    if (root == NULL)
        return;
    if (root->left == NULL && root->right == NULL)
        printf("%d ", root->data);
    displayLeafNodes(root->left);
    displayLeafNodes(root->right);
}

// Function to create the mirror image of the binary tree
struct TreeNode *mirrorImage(struct TreeNode *root)
{
    if (root == NULL)
        return NULL;

    struct TreeNode *temp = root->left;
    root->left = mirrorImage(root->right);
    root->right = mirrorImage(temp);

    return root;
}

// Function to count total number of nodes in the binary tree
int countNodes(struct TreeNode *root)
{
    if (root == NULL)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Function to calculate the height of the binary tree
int height(struct TreeNode *root)
{
    if (root == NULL)
        return 0;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Function to create a deep copy of the binary tree
struct TreeNode *deepCopy(struct TreeNode *root)
{
    if (root == NULL)
        return NULL;

    struct TreeNode *newNode = createNode(root->data);
    newNode->left = deepCopy(root->left);
    newNode->right = deepCopy(root->right);

    return newNode;
}

// Function to perform level-wise traversal of the binary tree
void levelOrderTraversal(struct TreeNode *root)
{
    if (root == NULL)
        return;

    struct QueueNode
    {
        struct TreeNode *treeNode;
        struct QueueNode *next;
    };

    struct Queue
    {
        struct QueueNode *front;
        struct QueueNode *rear;
    };

    struct Queue *queue = (struct Queue *)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;

    struct QueueNode *newNode = (struct QueueNode *)malloc(sizeof(struct QueueNode));
    newNode->treeNode = root;
    newNode->next = NULL;

    queue->rear = newNode;
    queue->front = queue->rear;

    while (queue->front != NULL)
    {
        struct QueueNode *temp = queue->front;
        printf("%d ", temp->treeNode->data);
        if (temp->treeNode->left != NULL)
        {
            struct QueueNode *newNode = (struct QueueNode *)malloc(sizeof(struct QueueNode));
            newNode->treeNode = temp->treeNode->left;
            newNode->next = NULL;
            queue->rear->next = newNode;
            queue->rear = newNode;
        }
        if (temp->treeNode->right != NULL)
        {
            struct QueueNode *newNode = (struct QueueNode *)malloc(sizeof(struct QueueNode));
            newNode->treeNode = temp->treeNode->right;
            newNode->next = NULL;
            queue->rear->next = newNode;
            queue->rear = newNode;
        }
        queue->front = queue->front->next;
    }
}

int main()
{
    struct TreeNode *root = NULL;
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
        printf("11. Mirror Image without Disturbing Original Tree\n");
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
            struct TreeNode *foundNode = find(root, data);
            if (foundNode != NULL)
                printf("Key %d found in the tree.\n", data);
            else
                printf("Key %d not found in the tree.\n", data);
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
            root = mirrorImage(root);
            inorderTraversal(root); // Displaying mirror image using inorder traversal
            printf("\n");
            break;
        case 9:
            printf("Total Number of Nodes: %d\n", countNodes(root));
            break;
        case 10:
            printf("Height of the Tree: %d\n", height(root));
            break;
        case 11:
            printf("Mirror Image without Disturbing Original Tree:\n");
            struct TreeNode *mirrorRoot = deepCopy(root);
            mirrorRoot = mirrorImage(mirrorRoot);
            inorderTraversal(mirrorRoot); // Displaying mirror image using inorder traversal
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
