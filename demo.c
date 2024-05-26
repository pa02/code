#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

int hash(int key)
{
    return key % TABLE_SIZE;
}

int linearProbe(int index, int attempt)
{
    return (index + attempt) % TABLE_SIZE;
}

void insert(int *hashTable, int key)
{
    int index = hash(key);
    int attempt = 0;

    while (hashTable[index] != -1)
    {
        attempt++;
        index = linearProbe(index, attempt);
    }

    hashTable[index] = key;
}

void displayHashTable(int *hashTable)
{
    printf("Hash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        printf("[%d] -> ", i);
        if (hashTable[i] != -1)
        {
            printf("%d", hashTable[i]);
        }
        printf("\n");
    }
}

int main()
{
    int hashTable[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hashTable[i] = -1; // Initialize all slots as empty (-1)
    }

    // Inserting keys into the hash table
    insert(hashTable, 5);
    insert(hashTable, 15);
    insert(hashTable, 25);
    insert(hashTable, 35);
    insert(hashTable, 45);
    insert(hashTable, 55);
    insert(hashTable, 65);
    insert(hashTable, 75);
    insert(hashTable, 85);
    insert(hashTable, 95);

    // Displaying the hash table
    displayHashTable(hashTable);

    return 0;
}
