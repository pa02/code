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
