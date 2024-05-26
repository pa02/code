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
