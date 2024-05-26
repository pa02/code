/*
Write a Program to accept a graph from user and represent it with Adjacency List .
 DFS traversals on it.
 BSF traversal on it .

*/
#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the adjacency list
struct Node
{
    int vertex;
    struct Node *next;
};

// Structure to represent the adjacency list
struct Graph
{
    int vertices;
    struct Node **adjList;
};

// Function to create a new node
struct Node *createNode(int vertex)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with 'vertices' vertices
struct Graph *createGraph(int vertices)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    graph->adjList = (struct Node **)malloc(vertices * sizeof(struct Node *));
    for (int i = 0; i < vertices; i++)
    {
        graph->adjList[i] = NULL;
    }
    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph *graph, int src, int dest)
{
    // Add an edge from src to dest
    struct Node *newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // For an undirected graph, add an edge from dest to src
    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// Function to perform Depth-First Search (DFS) traversal (recursive utility function)
void DFSUtil(struct Graph *graph, int vertex, int *visited)
{
    visited[vertex] = 1;
    printf("%d ", vertex);

    struct Node *temp = graph->adjList[vertex];
    while (temp != NULL)
    {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex])
        {
            DFSUtil(graph, adjVertex, visited);
        }
        temp = temp->next;
    }
}

// Function to perform Depth-First Search (DFS) traversal
void DFS(struct Graph *graph, int startVertex)
{
    int *visited = (int *)malloc(graph->vertices * sizeof(int));
    for (int i = 0; i < graph->vertices; i++)
    {
        visited[i] = 0;
    }
    printf("DFS traversal starting from vertex %d: ", startVertex);
    DFSUtil(graph, startVertex, visited);
    printf("\n");
    free(visited);
}

// Function to perform Breadth-First Search (BFS) traversal
void BFS(struct Graph *graph, int startVertex)
{
    int *visited = (int *)malloc(graph->vertices * sizeof(int));
    for (int i = 0; i < graph->vertices; i++)
    {
        visited[i] = 0;
    }

    int *queue = (int *)malloc(graph->vertices * sizeof(int));
    int front = 0, rear = 0;

    visited[startVertex] = 1;
    queue[rear++] = startVertex;
    printf("BFS traversal starting from vertex %d: ", startVertex);
    while (front < rear)
    {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        struct Node *temp = graph->adjList[currentVertex];
        while (temp != NULL)
        {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex])
            {
                visited[adjVertex] = 1;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }

    printf("\n");
    free(visited);
    free(queue);
}

// Main function to accept graph and perform DFS and BFS traversals
int main()
{
    int vertices, edges, src, dest;
    int choice, startVertex;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    struct Graph *graph = createGraph(vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    printf("Enter the edges (src dest):\n");
    for (int i = 0; i < edges; i++)
    {
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. DFS Traversal\n");
        printf("2. BFS Traversal\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the start vertex for DFS: ");
            scanf("%d", &startVertex);
            DFS(graph, startVertex);
            break;
        case 2:
            printf("Enter the start vertex for BFS: ");
            scanf("%d", &startVertex);
            BFS(graph, startVertex);
            break;
        case 3:
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

/*
Write a Program to accept a graph from user and represent it with Adjacency Matrix and perform
.DFS traversals on it.
.BSF traversals on it.
*/

#include <stdio.h>
#include <stdlib.h>

// Function to create and initialize the adjacency matrix
int *createAdjMatrix(int vertices)
{
    int *adjMatrix = (int *)malloc(vertices * vertices * sizeof(int));
    for (int i = 0; i < vertices * vertices; i++)
    {
        adjMatrix[i] = 0;
    }
    return adjMatrix;
}

// Function to add an edge to the adjacency matrix
void addEdge(int *adjMatrix, int vertices, int u, int v)
{
    adjMatrix[u * vertices + v] = 1;
    adjMatrix[v * vertices + u] = 1; // For an undirected graph
}

// Function to perform BFS traversal
void BFS(int *adjMatrix, int vertices, int startVertex)
{
    int *visited = (int *)malloc(vertices * sizeof(int));
    for (int i = 0; i < vertices; i++)
    {
        visited[i] = 0;
    }

    int *queue = (int *)malloc(vertices * sizeof(int));
    int front = 0;
    int rear = 0;

    visited[startVertex] = 1;
    queue[rear++] = startVertex;

    while (front < rear)
    {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        for (int i = 0; i < vertices; i++)
        {
            if (adjMatrix[currentVertex * vertices + i] == 1 && !visited[i])
            {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }

    free(visited);
    free(queue);
}

// Function to perform DFS traversal
void DFSUtil(int *adjMatrix, int vertices, int vertex, int *visited)
{
    printf("%d ", vertex);
    visited[vertex] = 1;

    for (int i = 0; i < vertices; i++)
    {
        if (adjMatrix[vertex * vertices + i] == 1 && !visited[i])
        {
            DFSUtil(adjMatrix, vertices, i, visited);
        }
    }
}

void DFS(int *adjMatrix, int vertices, int startVertex)
{
    int *visited = (int *)malloc(vertices * sizeof(int));
    for (int i = 0; i < vertices; i++)
    {
        visited[i] = 0;
    }
    DFSUtil(adjMatrix, vertices, startVertex, visited);
    free(visited);
}

// Main function to accept graph and perform BFS and DFS traversal
int main()
{
    int vertices, edges, u, v, startVertex;
    int choice;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    int *adjMatrix = createAdjMatrix(vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    printf("Enter the edges (u v):\n");
    for (int i = 0; i < edges; i++)
    {
        scanf("%d %d", &u, &v);
        addEdge(adjMatrix, vertices, u, v);
    }

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. BFS Traversal\n");
        printf("2. DFS Traversal\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the start vertex for BFS: ");
            scanf("%d", &startVertex);
            printf("BFS traversal starting from vertex %d: ", startVertex);
            BFS(adjMatrix, vertices, startVertex);
            printf("\n");
            break;
        case 2:
            printf("Enter the start vertex for DFS: ");
            scanf("%d", &startVertex);
            printf("DFS traversal starting from vertex %d: ", startVertex);
            DFS(adjMatrix, vertices, startVertex);
            printf("\n");
            break;
        case 3:
            free(adjMatrix);
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
/*
Write a Program to implement AVL tree and perform different rotations on it and display it Levelwise

*/
#include <stdio.h>
#include <stdlib.h>

// Define the structure for the AVL tree node
struct AVLNode
{
    int data;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
};

// Function to create a new AVL tree node
struct AVLNode *createNode(int data)
{
    struct AVLNode *newNode = (struct AVLNode *)malloc(sizeof(struct AVLNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

// Function to get the height of a node
int getHeight(struct AVLNode *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to get the balance factor of a node
int getBalance(struct AVLNode *node)
{
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Function to perform a right rotation
struct AVLNode *rightRotate(struct AVLNode *y)
{
    struct AVLNode *x = y->left;
    struct AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));

    return x;
}

// Function to perform a left rotation
struct AVLNode *leftRotate(struct AVLNode *x)
{
    struct AVLNode *y = x->right;
    struct AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));
    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));

    return y;
}

// Function to insert a new node into the AVL tree and perform rotations if necessary
struct AVLNode *insert(struct AVLNode *node, int data)
{
    if (node == NULL)
        return createNode(data);

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else
        return node; // Duplicate keys are not allowed

    node->height = 1 + (getHeight(node->left) > getHeight(node->right) ? getHeight(node->left) : getHeight(node->right));

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && data > node->left->data)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && data < node->right->data)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Function to print the tree level-wise
void printLevelWise(struct AVLNode *root)
{
    if (root == NULL)
        return;

    struct AVLNode *queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear)
    {
        struct AVLNode *current = queue[front++];
        printf("%d ", current->data);

        if (current->left != NULL)
            queue[rear++] = current->left;
        if (current->right != NULL)
            queue[rear++] = current->right;
    }
}

// Main function to provide menu-driven interface
int main()
{
    struct AVLNode *root = NULL;
    int choice, data;

    printf("Menu:\n");
    printf("1. Insert\n");
    printf("2. Display Level-wise\n");
    printf("3. Exit\n");

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
            printf("Level-wise Display: ");
            printLevelWise(root);
            printf("\n");
            break;
        case 3:
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
/*
 delete and level wise with non recursion
 // Function to delete a node from the AVL tree

 int height(struct AVLNode* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

void printLevelWise(struct AVLNode* root) {
    int h = height(root);
    for (int i = 1; i <= h; i++)
        printGivenLevel(root, i);
}
struct AVLNode* deleteNode(struct AVLNode* root, int data) {
    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            struct AVLNode* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            struct AVLNode* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + (getHeight(root->left) > getHeight(root->right) ? getHeight(root->left) : getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Recursive function to print the tree level-wise
void printGivenLevel(struct AVLNode* root, int level) {
    if (root == NULL)
        return;
    if (level == 1)
        printf("%d ", root->data);
    else if (level > 1) {
        printGivenLevel(root->left, level - 1);
        printGivenLevel(root->right, level - 1);
    }
}

// Function to perform a preorder traversal
void preorderTraversal(struct AVLNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}
*/
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
/*

Write a program to illustrate operations on a BST holding numeric keys. The menu must include:
• Insert
• Delete
• Find
• Level wise Display
. mirror image
. height
*/

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

// insert
struct node *create(int key)
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    if (newnode == NULL)
    {
        printf("Menory allcation error\n");
        exit(1);
    }

    newnode->data = key;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

struct node *insert(struct node *root, int key)
{
    if (root == NULL)
    {
        return create(key);
    }
    if (key < root->data)
    {
        root->left = insert(root->left, key);
    }
    if (key > root->data)
    {
        root->right = insert(root->right, key);
    }

    return root;
}

// delete
struct node *findmin(struct node *root)
{
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

struct node *delete(struct node *root, int key)
{
    if (root == NULL)
    {
        return root;
    }
    if (key < root->data)
    {
        root->left = delete (root->left, key);
    }
    else if (key > root->data)
    {
        root->right = delete (root->right, key);
    }
    else if (key == root->data)
    {
        struct node *temp;
        if (root->right == NULL)
        {
            temp = root->left;
            free(root);
            return temp;
        }
        if (root->left == NULL)
        {
            temp = root->right;
            free(root);
            return temp;
        }

        temp = findmin(root->right);
        root->data = temp->data;
        root->right = delete (root->right, temp->data);
    }
    else
    {
        printf("%d not present in BST \n", key);
        return root;
    }
}

// find

void find(struct node *root, int key)
{

    if (key < root->data)
    {
        find(root->left, key);
    }
    else if (key < root->data)
    {
        find(root->right, key);
    }
    else if (root->data == key)
    {
        printf("%d is Found \n", key);
        return;
    }
    else
    {
        printf("%d is NOT Found \n", key);
    }
}

// level wise display
struct quenode
{
    struct node *treenode;
    struct quenode *next;
};

struct que
{
    struct quenode *f;
    struct quenode *r;
};

struct quenode *createquenode(struct node *treenode)
{
    struct quenode *newquenode = (struct quenode *)malloc(sizeof(struct quenode));
    newquenode->treenode = treenode;
    newquenode->next = NULL;
    return newquenode;
}
struct que *createque()
{
    struct que *newque = (struct que *)malloc(sizeof(struct que));
    newque->f = NULL;
    newque->r = NULL;
    return newque;
}

void enqueue(struct que *queue, struct node *treenode)
{
    struct quenode *newquenode = createquenode(treenode);
    if (queue->r == NULL)
    {
        queue->f = queue->r = newquenode;
    }
    else
    {
        queue->r->next = newquenode; // Fix: Set the next of the rear node only if the queue is not empty
        queue->r = newquenode;
    }
}

struct node *dequeue(struct que *queue)
{
    if (queue->f == NULL)
    {
        return NULL;
    }
    struct quenode *temp = queue->f;
    queue->f = queue->f->next;

    if (queue->f == NULL)
    {
        queue->r = NULL;
    }

    struct node *treenode = temp->treenode;
    free(temp);
    return treenode;
}

int isqueempty(struct que *queue)
{
    return queue->f == NULL;
}

void levelOrderTraversal(struct node *root)
{
    if (root == NULL)
    {
        return;
    }
    struct que *queue = createque();
    enqueue(queue, root);

    while (!isqueempty(queue))
    {
        struct node *current = dequeue(queue);
        printf("%d  ", current->data);

        if (current->left != NULL)
        {
            enqueue(queue, current->left);
        }
        if (current->right != NULL)
        {
            enqueue(queue, current->right);
        }
    }
}

// mirror image
void inorder(struct node *root)
{
    if (root == NULL)
        return;
    printf("%d  ", root->data);
    inorder(root->left);
    inorder(root->right);
}
void mirror(struct node *root)
{
    if (root == NULL)
        return;
    struct node *temp = root->left;
    root->left = root->right;
    root->right = temp;
    if (root->right != NULL)
    {
        mirror(root->right);
    }
    if (root->left != NULL)
    {
        mirror(root->left);
    }
}

// height of the tree
int findheight(struct node *root)
{
    if (root == NULL)
        return 0;
    int lheight = findheight(root->left);
    int rheight = findheight(root->right);
    return (lheight > rheight ? lheight : rheight) + 1;
}

int main()
{

    struct node *root = NULL;
    int choice, key;

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Find\n");
        printf("4. Level-wise Display\n");
        printf("5. Exit\n");
        printf("6. Mirror Image\n");
        printf("7. Find Height \n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter key to insert: ");
            scanf("%d", &key);
            root = insert(root, key);
            printf("Key inserted successfully.\n");
            break;
        case 2:
            printf("Enter key to delete: ");
            scanf("%d", &key);
            root = delete (root, key);
            printf("Key deleted successfully.\n");
            break;
        case 3:
            printf("Enter key to find: ");
            scanf("%d", &key);
            find(root, key);
            break;
        case 4:
            printf("Level-wise Display:\n");
            levelOrderTraversal(root);
            printf("\n");
            break;
        case 6:
            printf("Mirror :\n");
            mirror(root);
            inorder(root);
            break;
        case 5:
            exit(0);
        case 7:
            printf("Height of Tree is : %d \n", findheight(root));
            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
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
/*
       Write a program to efficiently search a particular employee record by using Tree data structure.
       Also sort the data on emp-id in ascending order
*/

#include <stdio.h>
#include <stdlib.h>

// Define the structure for the employee record
struct Employee
{
    int empId;
    char name[50];
    char department[50];
};

// Define the structure for the binary search tree node
struct TreeNode
{
    struct Employee data;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Function to create a new tree node
struct TreeNode *createNode(struct Employee data)
{
    struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a new employee record into the binary search tree
struct TreeNode *insert(struct TreeNode *root, struct Employee data)
{
    if (root == NULL)
        return createNode(data);

    if (data.empId < root->data.empId)
        root->left = insert(root->left, data);
    else if (data.empId > root->data.empId)
        root->right = insert(root->right, data);

    return root;
}

// Function to perform an inorder traversal of the binary search tree
void inorderTraversal(struct TreeNode *root)
{
    if (root == NULL)
        return;
    inorderTraversal(root->left);
    printf("Employee ID: %d, Name: %s, Department: %s\n",
           root->data.empId, root->data.name, root->data.department);
    inorderTraversal(root->right);
}

// Function to search for an employee record by ID in the binary search tree
struct Employee *search(struct TreeNode *root, int empId)
{
    while (root != NULL)
    {
        if (empId < root->data.empId)
            root = root->left;
        else if (empId > root->data.empId)
            root = root->right;
        else
            return &(root->data);
    }
    return NULL;
}

int main()
{
    struct TreeNode *root = NULL;
    struct Employee empData[] = {
        {101, "John Doe", "Engineering"},
        {103, "Alice Smith", "Human Resources"},
        {105, "Bob Johnson", "Marketing"},
        {102, "Jane Brown", "Finance"},
        {104, "Mary Lee", "Sales"}};
    int numEmployees = sizeof(empData) / sizeof(empData[0]);

    // Inserting employee records into the binary search tree
    for (int i = 0; i < numEmployees; i++)
    {
        root = insert(root, empData[i]);
    }

    // Sorting the employee records based on empId in ascending order (BST property)
    printf("Employee Records Sorted by ID (Ascending Order):\n");
    inorderTraversal(root);

    // Searching for a particular employee record by ID
    int searchId;
    printf("\nEnter employee ID to search: ");
    scanf("%d", &searchId);

    struct Employee *foundEmployee = search(root, searchId);
    if (foundEmployee != NULL)
    {
        printf("Employee Record Found:\n");
        printf("Employee ID: %d, Name: %s, Department: %s\n",
               foundEmployee->empId, foundEmployee->name, foundEmployee->department);
    }
    else
    {
        printf("Employee Record with ID %d not found.\n", searchId);
    }

    return 0;
}
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
/*
WAP to convert a given Infix expression into its equivalent
 Postfix  expression and evaluate it using stack.

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
/*
Implement following hashing Techniques by assuming suitable input and Table Size.
a.	Linear Probing With Chaining  ***Without Replacement
Also mention number of collisions occurred while inserting a Data in hash table


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

struct Node
{
    int data;
    struct Node *next;
};

struct HashTable
{
    struct Node *table[TABLE_SIZE];
    int collisions;
};

unsigned int hash(int key)
{
    return key % TABLE_SIZE;
}

struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void initHashTable(struct HashTable *ht)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        ht->table[i] = NULL;
    }
    ht->collisions = 0;
}

void insert(struct HashTable *ht, int data)
{
    int index = hash(data);
    struct Node *newNode = createNode(data);

    if (ht->table[index] == NULL)
    {
        ht->table[index] = newNode;
    }
    else
    {
        ht->collisions++;
        struct Node *temp = ht->table[index];
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void printHashTable(struct HashTable *ht)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        printf("Index %d: ", i);
        struct Node *temp = ht->table[i];
        while (temp != NULL)
        {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
    printf("Number of collisions: %d\n", ht->collisions);
}

int main()
{
    struct HashTable ht;
    initHashTable(&ht);

    int data[] = {20, 21, 23, 11, 13, 25, 45, 35, 47, 49};
    int n = sizeof(data) / sizeof(data[0]);

    for (int i = 0; i < n; i++)
    {
        insert(&ht, data[i]);
    }

    printHashTable(&ht);

    return 0;
}
*/
/*
Implement following hashing Techniques by assuming suitable input and Table Size.
a.	Linear Probing With Chaining With Replacement
Also mention number of collisions occurred while inserting a Data in hash table.

*/
#include <stdio.h>

void Insert_HashTable(int arr[], int iKey, int chain[]);
void Display_HashTable(int arr[], int chain[]);

int count = 0;

int main(void)
{
    int arr[10];
    int chain[10];
    int iKey;

    for (int i = 0; i < 10; i++)
    {
        arr[i] = -1;
        chain[i] = -1;
    }

    printf("Enter Data:\n");

    for (int i = 0; i < 10; i++)
    {
        scanf("%d", &iKey);
        Insert_HashTable(arr, iKey, chain);
    }

    Display_HashTable(arr, chain);
    printf("Count %d", count);
}

void Insert_HashTable(int arr[], int iKey, int chain[])
{
    int iPos;

    iPos = iKey % 10;

    if (arr[iPos] == -1)
    {
        arr[iPos] = iKey;
        return;
    }

    if (arr[iPos] != -1 && arr[iPos] % 10 != iPos)
    {
        for (int i = 0; i < 10; i++)
        {
            count++;
            if (arr[(iPos + i) % 10] == -1)
            {
                arr[(iPos + i) % 10] = arr[iPos];
                arr[iPos] = iKey;
                for (int j = 0; j < 10; j++)
                {
                    if (chain[j] == iPos)
                    {
                        printf("%d\t", iPos);
                        if (chain[iPos] != -1)
                        {
                            chain[j] = chain[iPos];
                            chain[iPos] = -1;
                        }
                        chain[chain[j]] = (iPos + i) % 10;
                        return;
                    }
                }
            }
        }
    }

    for (int i = 0; i < 10; i++)
    {
        count++;
        if (arr[(iPos + i) % 10] == -1)
        {
            arr[(iPos + i) % 10] = iKey;
            for (int j = 0; j < 10; j++)
            {
                if ((arr[j] != iKey) && (arr[j] % 10 == iKey % 10) && (chain[j] == -1))
                {
                    chain[j] = (iPos + i) % 10;
                    return;
                }
            }
        }
    }
}

void Display_HashTable(int arr[], int chain[])
{
    for (int i = 0; i < 10; i++)
    {
        if (arr[i] != -1)
        {
            printf("[%d]  %d->%d\n", i, arr[i], chain[i]);
        }
    }
}
// poly addi

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int iCoeff;
    int iExpo;
    struct node *pNext;
};

void InsertLast(struct node **, int, int);
void Display(struct node *);
void Addition(struct node *, struct node *, struct node **);

int main(void)
{
    struct node *pFirst1 = NULL;
    struct node *pFirst2 = NULL;
    struct node *pFirst3 = NULL;
    int iChoice = 1;
    int coeff, expo;

    printf("Enter 1st polynomial Expression(Ascending/Desending order of Exponent):\n");

    while (iChoice)
    {
        printf("Enter coefficient:\n");
        scanf("%d", &coeff);
        printf("Enter Exponent:\n");
        scanf("%d", &expo);
        InsertLast(&pFirst1, coeff, expo);
        printf("Do you want to continue if Yes press '1' either press '0':\n");
        scanf("%d", &iChoice);
    }

    printf("Enter 2nd polynomial Expression(Ascending/Desending order of Exponent):\n");

    iChoice = 1;

    while (iChoice)
    {
        printf("Enter coefficient:\n");
        scanf("%d", &coeff);
        printf("Enter Exponent:\n");
        scanf("%d", &expo);
        InsertLast(&pFirst2, coeff, expo);
        printf("Do you want to continue if Yes press '1' either press '0':\n");
        scanf("%d", &iChoice);
    }

    printf("The 1st polynomial is:\n");
    Display(pFirst1);
    printf("\n");

    printf("The 2nd polynomial is:\n");
    Display(pFirst2);
    printf("\n");

    Addition(pFirst1, pFirst2, &pFirst3);

    printf("The addition of polynomial is:\n");
    Display(pFirst3);
}

void InsertLast(struct node **ppHead, int iCoefficient, int iExponent)
{
    struct node *pNewnode = NULL;
    struct node *pTemp = NULL;

    pNewnode = (struct node *)malloc(sizeof(struct node));

    if (NULL == pNewnode)
    {
        printf("Memory Allocation Failed\n");
        return;
    }

    pNewnode->iCoeff = iCoefficient;
    pNewnode->iExpo = iExponent;
    pNewnode->pNext = NULL;

    if (NULL == *ppHead)
    {
        *ppHead = pNewnode;
        return;
    }

    pTemp = *ppHead;

    while (pTemp->pNext != NULL)
    {
        pTemp = pTemp->pNext;
    }

    pTemp->pNext = pNewnode;
}

void Display(struct node *pHead)
{
    if (NULL == pHead)
    {
        printf("You did not entered polynomial\n");
        return;
    }

    while (pHead->pNext != NULL)
    {

        printf("%dx^%d +", pHead->iCoeff, pHead->iExpo);
        pHead = pHead->pNext;
    }
    printf("%dx^%d ", pHead->iCoeff, pHead->iExpo);
}

void Addition(struct node *pHead1, struct node *pHead2, struct node **ppHead3)
{
    struct node *pTemp1 = NULL;
    struct node *pTemp2 = NULL;
    struct node *pNewnode = NULL;

    pTemp1 = pHead1;
    pTemp2 = pHead2;

    while (pTemp1 != NULL || pTemp2 != NULL)
    {
        if (pTemp1->iExpo == pTemp2->iExpo)
        {
            InsertLast(&(*ppHead3), (pTemp1->iCoeff + pTemp2->iCoeff), (pTemp1->iExpo));
            pTemp1 = pTemp1->pNext;
            pTemp2 = pTemp2->pNext;
        }

        else if (pTemp1->iExpo > pTemp2->iExpo)
        {
            InsertLast(&(*ppHead3), (pTemp1->iCoeff), (pTemp1->iExpo));
            pTemp1 = pTemp1->pNext;
        }

        else
        {
            InsertLast(&(*ppHead3), (pTemp2->iCoeff), (pTemp2->iExpo));
            pTemp2 = pTemp2->pNext;
        }
    }

    while (pTemp1 != NULL)
    {
        InsertLast(&(*ppHead3), (pTemp1->iCoeff), (pTemp1->iExpo));
        pTemp1 = pTemp1->pNext;
    }

    while (pTemp2 != NULL)
    {
        InsertLast(&(*ppHead3), (pTemp2->iCoeff), (pTemp2->iExpo));
        pTemp2 = pTemp2->pNext;
    }
}
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
/*
Write an iterative Reverse() function that reverses a list by rearranging all the next pointers and the head pointer.
 Ideally, Reverse() should only need to make one pass of the list
*/
#include <stdio.h>
#include <stdlib.h>

// Definition of a node in the linked list
struct Node
{
    int data;
    struct Node *next;
};

// Function to reverse the linked list iteratively
void Reverse(struct Node **head)
{
    struct Node *prev = NULL;
    struct Node *current = *head;
    struct Node *next = NULL;

    while (current != NULL)
    {
        // Store the next node
        next = current->next;
        // Reverse the current node's pointer
        current->next = prev;
        // Move pointers one position ahead
        prev = current;
        current = next;
    }
    *head = prev;
}

// Function to push a new node at the head of the list
void push(struct Node **head, int new_data)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = *head;
    *head = new_node;
}

// Function to print the linked list
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

    // Creating a sample linked list
    push(&head, 20);
    push(&head, 15);
    push(&head, 10);
    push(&head, 5);

    printf("Original list: ");
    printList(head);

    // Reverse the linked list
    Reverse(&head);

    printf("Reversed list: ");
    printList(head);

    return 0;
}
/*
WAP to implement Heap sort on 1D array of Student structure (contains student_name, student_roll_no, total_marks),
with key as student_roll_no. And count the number of swap performed.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a student
struct Student
{
    char name[50];
    int rollNo;
    int totalMarks;
};

// Function to swap two students
void swap(struct Student *a, struct Student *b)
{
    struct Student temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify a subtree rooted with node i which is an index in arr[]
void heapify(struct Student arr[], int n, int i, int *swapCount)
{
    int largest = i;   // Initialize largest as root
    int l = 2 * i + 1; // Left child
    int r = 2 * i + 2; // Right child

    // If left child is larger than root
    if (l < n && arr[l].rollNo > arr[largest].rollNo)
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r].rollNo > arr[largest].rollNo)
        largest = r;

    // If largest is not root
    if (largest != i)
    {
        *swapCount += 1;
        swap(&arr[i], &arr[largest]);
        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest, swapCount);
    }
}

// Main function to do heap sort
void heapSort(struct Student arr[], int n, int *swapCount)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, swapCount);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--)
    {
        // Move current root to end
        *swapCount += 1;
        swap(&arr[0], &arr[i]);
        // call max heapify on the reduced heap
        heapify(arr, i, 0, swapCount);
    }
}

// Function to print an array of students
void printArray(struct Student arr[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        printf("Roll No: %d, Name: %s, Total Marks: %d\n", arr[i].rollNo, arr[i].name, arr[i].totalMarks);
    }
}

int main()
{
    int n;
    printf("Enter the number of students: ");
    scanf("%d", &n);

    // Create an array of students
    struct Student *students = (struct Student *)malloc(n * sizeof(struct Student));

    // Input student details
    for (int i = 0; i < n; ++i)
    {
        printf("Enter details for student %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", students[i].name);
        printf("Roll No: ");
        scanf("%d", &students[i].rollNo);
        printf("Total Marks: ");
        scanf("%d", &students[i].totalMarks);
    }

    int swapCount = 0;
    // Perform Heap Sort
    heapSort(students, n, &swapCount);

    printf("\nSorted array of students:\n");
    printArray(students, n);

    printf("\nNumber of swaps performed: %d\n", swapCount);

    free(students); // Free allocated memory
    return 0;
}
*/
// 2
/*
WAP to implement Quick sort on 1D array of Employee structure (contains employee_name, emp_no, emp_salary)
, with key as emp_no. And count the number of swap performed


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent an employee
struct Employee
{
    char name[50];
    int empNo;
    float salary;
};

// Function to swap two employees
void swap(struct Employee *a, struct Employee *b)
{
    struct Employee temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function for Quick Sort
int partition(struct Employee arr[], int low, int high, int *swapCount)
{
    struct Employee pivot = arr[high]; // Pivot
    int i = (low - 1);                 // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than or equal to pivot
        if (arr[j].empNo <= pivot.empNo)
        {
            i++; // Increment index of smaller element
            swap(&arr[i], &arr[j]);
            *swapCount += 1;
        }
    }
    swap(&arr[i + 1], &arr[high]);
    *swapCount += 1;
    return (i + 1);
}

// Main function to implement Quick Sort
void quickSort(struct Employee arr[], int low, int high, int *swapCount)
{
    if (low < high)
    {
        // pi is partitioning index, arr[pi] is now at right place
        int pi = partition(arr, low, high, swapCount);

        // Separately sort elements before partition and after partition
        quickSort(arr, low, pi - 1, swapCount);
        quickSort(arr, pi + 1, high, swapCount);
    }
}

// Function to print an array of employees
void printArray(struct Employee arr[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        printf("Emp No: %d, Name: %s, Salary: %.2f\n", arr[i].empNo, arr[i].name, arr[i].salary);
    }
}

int main()
{
    int n;
    printf("Enter the number of employees: ");
    scanf("%d", &n);

    // Create an array of employees
    struct Employee *employees = (struct Employee *)malloc(n * sizeof(struct Employee));

    // Input employee details
    for (int i = 0; i < n; ++i)
    {
        printf("Enter details for employee %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", employees[i].name);
        printf("Emp No: ");
        scanf("%d", &employees[i].empNo);
        printf("Salary: ");
        scanf("%f", &employees[i].salary);
    }

    int swapCount = 0;
    // Perform Quick Sort
    quickSort(employees, 0, n - 1, &swapCount);

    printf("\nSorted array of employees:\n");
    printArray(employees, n);

    printf("\nNumber of swaps performed: %d\n", swapCount);

    free(employees); // Free allocated memory
    return 0;
}

*/
// 3
/*
Assume that an array A with n elements was sorted in an ascending order,
 but two of its elements swapped their positions by a mistake while maintaining the array.
  Write a code to identify the swapped pair of elements and their positions in the
  asymptotically best possible time. [Assume that all given elements are distinct integers.]

*/
#define MAX 20
#include <stdio.h>

void Check(int arr[], int n);

int main(void)
{
    int n;
    int arr[MAX];

    printf("Enter total no of elements in array that you want:\n");
    scanf("%d", &n);

    printf("Enter elements:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    Check(arr, n);
}

void Check(int arr[], int n)
{
    int First = -1;
    int Second = -1;

    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i] > arr[i + 1] && First == -1)
        {
            First = i;
        }

        else if (arr[i] > arr[i + 1])
        {
            Second = i + 1;
            break;
        }
    }

    printf("The elements which are not swappend properly are :\n %d and %d at Position %d and %d\n %d and %d at Position %d and %d\n", arr[First], arr[First + 1], First, (First + 1), arr[Second - 1], arr[Second], Second, (Second + 1));
}
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
