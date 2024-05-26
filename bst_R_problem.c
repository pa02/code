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