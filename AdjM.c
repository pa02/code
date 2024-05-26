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
