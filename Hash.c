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
