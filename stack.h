//
// Created by 1605491 on 22-Oct-17.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#ifndef TREE_STACK_H
#define TREE_STACK_H

#endif //TREE_STACK_H
typedef struct slink
{
    int data1;
    struct slink *next;
}stack;
stack* newnode(int data1)
{
    stack *n=(stack*)malloc(sizeof(stack));
    n->data1=data1;
    n->next=NULL;
    return n;
}
int isEmptyStack(stack *start)
{
    return !start;
}
void push(stack **start,int data1)
{
    stack *n= newnode(data1);
    n->next=*start;
    *start=n;
    printf("%d pushed to stack\n",data1);
}
int pop(stack **start)
{
    if(isEmptyStack(*start))
        return INT_MIN;
    stack *curr=*start;
    int data1=curr->data1;
    *start=(*start)->next;
    free(curr);
    return data1;
}
int peek(stack *start)
{
    if(isEmptyStack(start))
        return INT_MIN;
    return start->data1;
}
void printlist(stack *start)
{
    stack *curr=start;
    while(curr)
    {
        printf("%d-->",curr->data1);
        curr=curr->next;
    }
    printf("NULL");
}