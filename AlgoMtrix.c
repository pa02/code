#define MAX 20
#include <stdio.h>

void Display(int Graph[MAX][MAX], int Data[], int n);
void Prims(int Graph[MAX][MAX], int Data[], int n);
int FindMin_Distance(int Distance[], int Visited[], int n);
void Print_Prims(int Parent[], int Distance[], int n);
void Dijktras(int Graph[MAX][MAX], int Data[], int n);
void Print_Dijktras(int Distance[], int n, int st);
void Kruskel(int Graph[MAX][MAX], int Data[], int n);
int FindParent(int Parent[], int a);
void Union(int Parent[], int i, int j);

int iFront = 0;
int iRear = -1;
int iTop = -1;

int main(void)
{
    int n, v, m, adj, k, wt;
    int Data[MAX];
    int Graph[MAX][MAX] = {{0}};

    printf("Enter total no of vertices for graph:\n");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("Enter %d vertex:\n", i + 1);
        scanf("%d", &Data[i]);
    }

    for (int i = 0; i < n; i++)
    {
        printf("How many adjacent vertices for %d\n", Data[i]);
        scanf("%d", &m);

        for (int j = 0; j < m; j++)
        {
            printf("Enter %d adjacent vertex:\n", j + 1);
            scanf("%d", &adj);
            printf("Enter Weight:\n");
            scanf("%d", &wt);

            for (k = 0; k < n; k++)
            {
                if (Data[k] == adj)
                {
                    break;
                }
            }
            Graph[i][k] = Graph[k][i] = wt;
        }
    }

    printf("The Graph is:\n");
    Display(Graph, Data, n);

    printf("The Prims is:\n");
    Prims(Graph, Data, n);
    printf("The Dijtras is:\n");
    Dijktras(Graph, Data, n);
    printf("The Kruskel is:\n");
    Kruskel(Graph, Data, n);
}

void Display(int Graph[MAX][MAX], int Data[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d = ", Data[i]);
        for (int j = 0; j < n; j++)
        {
            if (Graph[i][j] != 0)
            {
                printf("%d(%d)->", Data[j], Graph[i][j]);
            }
        }
        printf("\n");
    }
}

void Prims(int Graph[MAX][MAX], int Data[], int n)
{
    int index;
    int Visited[MAX] = {0};
    int Distance[MAX];
    int Parent[MAX];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (Graph[i][j] == 0)
            {
                Graph[i][j] = 999;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        Distance[i] = 999;
        Parent[i] = -1;
    }

    Distance[0] = 0;

    for (int i = 0; i < n - 1; i++)
    {
        index = FindMin_Distance(Distance, Visited, n);
        Visited[index] = 1;

        for (int j = 0; j < n; j++)
        {
            if (Visited[j] == 0 && Graph[index][j] != 999 && Graph[index][j] < Distance[j])
            {
                Distance[j] = Graph[index][j];
                Parent[j] = index;
            }
        }
    }

    Print_Prims(Parent, Distance, n);
}

int FindMin_Distance(int Distance[], int Visited[], int n)
{
    int Min = 999;
    int index;

    for (int i = 0; i < n; i++)
    {
        if (Visited[i] == 0 && Distance[i] < Min)
        {
            Min = Distance[i];
            index = i;
        }
    }
    return index;
}

void Print_Prims(int Parent[], int Distance[], int n)
{
    for (int i = 1; i < n; i++)
    {
        printf("%d -> %d(%d)\n", i, Parent[i], Distance[i]);
    }
}

void Dijktras(int Graph[MAX][MAX], int Data[], int n)
{
    int st;
    int index;
    int Visited[MAX] = {0};
    int Distance[MAX];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (Graph[i][j] == 0)
            {
                Graph[i][j] = 999;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        Distance[i] = 999;
    }

    printf("Enter vertex by whch you want to calculate distance of other vertex(MIN):\n");
    scanf("%d", &st);
    Distance[st] = 0;

    for (int i = 0; i < n - 1; i++)
    {
        index = FindMin_Distance(Distance, Visited, n);
        Visited[index] = 1;

        for (int j = 0; j < n; j++)
        {
            if (Visited[j] == 0 && Graph[index][j] != 999 && Graph[index][j] + Distance[index] < Distance[j])
            {
                Distance[j] = Graph[index][j] + Distance[index];
            }
        }
    }

    printf("The Minimum Distance from %d uisng Dijktras is:\n", st);
    Print_Dijktras(Distance, n, st);
}

void Print_Dijktras(int Distance[], int n, int st)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d->%d(%d)\n", st, i, Distance[i]);
    }
}

void Kruskel(int Graph[MAX][MAX], int Data[], int n)
{
    int Parent[MAX];
    int a, b;
    int Min;

    for (int i = 0; i < n; i++)
    {
        Parent[i] = i;
    }

    for (int i = 0; i < n - 1; i++)
    {
        Min = 999;
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                if (Graph[j][k] < Min && FindParent(Parent, j) != FindParent(Parent, k))
                {
                    a = j;
                    b = k;
                    Min = Graph[j][k];
                }
            }
        }
        printf("%d -> %d(%d)\n", a, b, Graph[a][b]);
        Union(Parent, a, b);
    }
}

int FindParent(int Parent[], int a)
{

    while (Parent[a] != a)
    {
        a = Parent[a];
    }

    return a;
}

void Union(int Parent[], int i, int j)
{
    int a, b;

    a = FindParent(Parent, i);
    b = FindParent(Parent, j);

    Parent[b] = a;
}