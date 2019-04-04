//
// Created by 1605491 on 21-Oct-17.
//

#ifndef TREE_QUEUE_H
#define TREE_QUEUE_H

#endif //TREE_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef struct queue{
    int size,front,rear;
    int capacity;
    int *array;
}queue;
queue *create(int capacity)
{
    queue *node=(queue*)malloc(sizeof(queue));
    node->capacity=capacity;
    node->front=0;
    node->rear=capacity-1;
    node->array=(int*)malloc(node->capacity* sizeof(int));
    return node;
}
int isFull(queue *arg)
{
    return (arg->size==arg->capacity);
}
int isEmpty(queue *arg)
{
    return (arg->size==0);
}
void enqueue(queue *arr, int data)
{
    if(isFull(arr))
    {
        printf("Queue is Full, insertion not possible.\n");
        return;
    }
    arr->rear+=1;
    arr->array[arr->rear]=data;
    arr->size+=1;
    printf("%d entered in queue.\n",data);
}
int dequeue(queue *arr)
{
    if(isEmpty(arr))
    {
        printf("Queue is Empty, deletion is not possible.\n");
        return INT_MIN;
    }
    int data=arr->array[arr->front];
    arr->front+=1;
    arr->size-=1;
    return data;
}
int front(queue *arr)
{
    if(isEmpty(arr))
        return INT_MIN;
    return arr->array[arr->front];
}
int rear(queue *arr)
{
    if(isEmpty(arr))
        return INT_MIN;
    return arr->array[arr->rear];
}
void printelements(queue *arr)
{
    if(isEmpty(arr))
        return;
    for(int i=arr->front;i<=arr->rear;i++)
    {
        printf("%d ",arr->array[i]);
    }
    printf("NULL\n");
}