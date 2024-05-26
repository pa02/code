
// prims List
#define MAX 20
#include <stdio.h>
#include <stdlib.h>

struct edge;

struct vertex
{
    struct vertex *pNext;
    int iData;
    struct edge *pAdjEdge;
};

struct edge
{
    struct vertex *pAdjvertex;
    int iWeight;
    struct edge *pNext;
};

struct queue
{
    int iData;
    struct queue *pNext;
};

struct stack
{
    int iData;
    struct stack *pNext;
};

struct vertex *InsertVertex(struct vertex **ppHead, int iNo);
void InsertEdge(struct vertex **ppHead, struct vertex *pVertex, struct vertex *pAdj, int iWt);
struct vertex *Serachvertex(struct vertex *pHead, int iNo);
void DisplayGraph(struct vertex *pHead);
int CountVertex(struct vertex *pHead);
void prims(struct vertex *pHead);
int FindMin_Distance(int Distance[], int Visited[], int n);
void Print_Prims(int Parent[], int Distance[], int n);
void Dijktras(struct vertex *pHead);
void Print_Dijktras(int Distance[], int n, int st);
void Kruskel(struct vertex *pHead);
int FindParent(int i, int Parent[]);
void Union(int i, int j, int Parent[]);

int main(void)
{
    int v, n, adj, iChoice, wt;
    struct vertex *pFirst = NULL;
    struct vertex *pTemp = NULL;
    struct vertex *pTemp1 = NULL;

    while (1)
    {
        printf("Enter vertex:\n");
        scanf("%d", &v);

        pTemp1 = Serachvertex(pFirst, v);

        if (pTemp1 == NULL)
        {
            pTemp1 = InsertVertex(&pFirst, v);
        }

        printf("How many Adjacent vertices for %d:\n", v);
        scanf("%d", &n);

        for (int i = 0; i < n; i++)
        {
            printf("Enter %d Adjacent vertex:\n", i + 1);
            scanf("%d", &adj);
            printf("Enter Weight:\n");
            scanf("%d", &wt);
            pTemp = Serachvertex(pFirst, adj);
            if (pTemp == NULL)
            {
                pTemp = InsertVertex(&pFirst, adj);
            }
            InsertEdge(&pFirst, pTemp1, pTemp, wt);
            InsertEdge(&pFirst, pTemp, pTemp1, wt);
        }
        printf("Do you want to continue if yes then press 1 either press 0:\n");
        scanf("%d", &iChoice);

        if (iChoice == 0)
        {
            break;
        }
    }

    printf("The Graph is:\n");
    DisplayGraph(pFirst);

    printf("The prims is:\n");
    prims(pFirst);
    printf("The Dijktras is:\n");
    Dijktras(pFirst);
    printf("The Kruskel is:\n");
    Kruskel(pFirst);
}

struct vertex *InsertVertex(struct vertex **ppHead, int iNo)
{
    struct vertex *pNewnode = NULL;
    struct vertex *pTemp = NULL;

    pNewnode = (struct vertex *)malloc(sizeof(struct vertex));

    if (NULL == pNewnode)
    {
        printf("The Memory Allocation Failed:\n");
        return NULL;
    }

    pNewnode->iData = iNo;
    pNewnode->pAdjEdge = NULL;
    pNewnode->pNext = NULL;

    if (*ppHead == NULL)
    {
        *ppHead = pNewnode;
        return pNewnode;
    }

    pTemp = *ppHead;

    while (pTemp->pNext != NULL)
    {
        pTemp = pTemp->pNext;
    }

    pTemp->pNext = pNewnode;

    return pNewnode;
}

void InsertEdge(struct vertex **ppHead, struct vertex *pVertex, struct vertex *pAdj, int iWt)
{
    struct edge *pNewnode = NULL;
    struct edge *pTemp = NULL;

    pTemp = pVertex->pAdjEdge;

    while (pTemp != NULL)
    {
        if (pTemp->pAdjvertex == pAdj)
        {
            return;
        }
        pTemp = pTemp->pNext;
    }

    pNewnode = (struct edge *)malloc(sizeof(struct edge));

    if (NULL == pNewnode)
    {
        printf("The Memory Allocation Failed:\n");
        return;
    }

    pNewnode->pAdjvertex = pAdj;
    pNewnode->iWeight = iWt;
    pNewnode->pNext = NULL;

    if (pVertex->pAdjEdge == NULL)
    {
        pVertex->pAdjEdge = pNewnode;
        return;
    }

    pTemp = pVertex->pAdjEdge;

    while (pTemp->pNext != NULL)
    {
        pTemp = pTemp->pNext;
    }

    pTemp->pNext = pNewnode;
}

struct vertex *Serachvertex(struct vertex *pHead, int iNo)
{
    while (pHead != NULL)
    {
        if (pHead->iData == iNo)
        {
            return pHead;
        }
        pHead = pHead->pNext;
    }

    return NULL;
}

void DisplayGraph(struct vertex *pHead)
{
    struct vertex *pTemp = NULL;
    struct edge *pTemp1 = NULL;
    struct vertex *pTemp2 = NULL;

    pTemp = pHead;

    while (pTemp != NULL)
    {
        printf("%d =", pTemp->iData);
        pTemp1 = pTemp->pAdjEdge;
        while (pTemp1 != NULL)
        {
            pTemp2 = pTemp1->pAdjvertex;
            printf(" %d(%d)->", pTemp2->iData, pTemp1->iWeight);
            pTemp1 = pTemp1->pNext;
        }
        printf("\n");
        pTemp = pTemp->pNext;
    }
}

int CountVertex(struct vertex *pHead)
{
    int iCount = 0;
    while (pHead != NULL)
    {
        iCount++;
        pHead = pHead->pNext;
    }

    return iCount;
}

void prims(struct vertex *pHead)
{
    int n, st, u;
    struct vertex *pTemp = NULL;
    struct edge *pTemp1 = NULL;
    int Visited[MAX] = {0};
    int Distance[MAX];
    int Parent[MAX];

    n = CountVertex(pHead);

    for (int i = 0; i < n; i++)
    {
        Distance[i] = 999;
        Parent[i] = -1;
    }

    printf("Enter starting vertex:\n");
    scanf("%d", &st);
    Distance[st] = 0;

    for (int i = 0; i < n - 1; i++)
    {
        u = FindMin_Distance(Distance, Visited, n);
        Visited[u] = 1;

        pTemp = pHead;

        while (pTemp != NULL)
        {
            if (pTemp->iData == u)
            {
                break;
            }
            pTemp = pTemp->pNext;
        }

        pTemp1 = pTemp->pAdjEdge;

        while (pTemp1 != NULL)
        {
            for (int j = 0; j < n; j++)
            {
                if (Visited[pTemp1->pAdjvertex->iData] == 0 && Distance[j] > pTemp1->iWeight && j == pTemp1->pAdjvertex->iData)
                {
                    Distance[j] = pTemp1->iWeight;
                    Parent[j] = u;
                }
            }
            pTemp1 = pTemp1->pNext;
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

void Dijktras(struct vertex *pHead)
{
    int n, st, u;
    struct vertex *pTemp = NULL;
    struct edge *pTemp1 = NULL;
    int Visited[MAX] = {0};
    int Distance[MAX];

    n = CountVertex(pHead);

    for (int i = 0; i < n; i++)
    {
        Distance[i] = 999;
    }

    printf("Enter starting vertex:\n");
    scanf("%d", &st);
    Distance[st] = 0;

    for (int i = 0; i < n - 1; i++)
    {
        u = FindMin_Distance(Distance, Visited, n);
        Visited[u] = 1;

        pTemp = pHead;

        while (pTemp != NULL)
        {
            if (pTemp->iData == u)
            {
                break;
            }
            pTemp = pTemp->pNext;
        }

        pTemp1 = pTemp->pAdjEdge;

        while (pTemp1 != NULL)
        {
            for (int j = 0; j < n; j++)
            {
                if (Visited[pTemp1->pAdjvertex->iData] == 0 && Distance[j] > pTemp1->iWeight + Distance[u] && j == pTemp1->pAdjvertex->iData)
                {
                    Distance[j] = pTemp1->iWeight + Distance[u];
                }
            }
            pTemp1 = pTemp1->pNext;
        }
    }
    Print_Dijktras(Distance, n, st);
}

void Print_Dijktras(int Distance[], int n, int st)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d->%d(%d)\n", st, i, Distance[i]);
    }
}

void Kruskel(struct vertex *pHead)
{
    int n, Min, a, b;
    struct vertex *pTemp = NULL;
    struct edge *pTemp1 = NULL;
    int Parent[MAX];

    n = CountVertex(pHead);

    for (int i = 0; i < n; i++)
    {
        Parent[i] = i;
    }

    for (int i = 0; i < n - 1; i++)
    {
        Min = 999;
        pTemp = pHead;

        while (pTemp != NULL)
        {
            pTemp1 = pTemp->pAdjEdge;
            while (pTemp1 != NULL)
            {
                if (pTemp1->iWeight < Min && FindParent(pTemp->iData, Parent) != FindParent(pTemp1->pAdjvertex->iData, Parent))
                {
                    a = pTemp->iData;
                    b = pTemp1->pAdjvertex->iData;
                    Min = pTemp1->iWeight;
                }
                pTemp1 = pTemp1->pNext;
            }
            pTemp = pTemp->pNext;
        }
        printf("%d -> %d\n", a, b);
        Union(a, b, Parent);
    }
}

int FindParent(int i, int Parent[])
{
    while (i != Parent[i])
    {
        i = Parent[i];
    }
    return i;
}

void Union(int i, int j, int Parent[])
{
    int a, b;

    a = FindParent(i, Parent);
    b = FindParent(j, Parent);
    Parent[b] = a;
}
