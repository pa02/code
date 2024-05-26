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