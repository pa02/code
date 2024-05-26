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
