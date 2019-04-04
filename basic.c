//
// Created by 1605491 on 21-Oct-17.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int data;
    struct node *left,*right;
}tree;
typedef struct link
{
    tree *t1;
    struct link *next;
}stack;

typedef struct qnode
{
    tree *t1;
    struct qnode *next;
}Qnode;

typedef struct links
{
    Qnode *front,*rear;
}queue;

tree* newtree(int data)
{
    tree *newtree=(tree*)malloc(sizeof(tree));
    newtree->data=data;
    newtree->left=NULL;
    newtree->right=NULL;
    return newtree;
}
int isEmpty(stack *a)
{
    if(a==NULL)
        return 1;
    return 0;
}
void push(tree *t,stack **a)
{
    stack *b=(stack*)malloc(sizeof(stack));
    b->t1 = t;
    b->next = (*a);
    (*a) = b;
}
tree* pop(stack **a)
{
    if(isEmpty(*a))
        return NULL;
    tree *tr;
    tr=(*a)->t1;
    (*a)=(*a)->next;
    return tr;
}
Qnode *create(tree *t)
{
    Qnode *newnode=(Qnode*)malloc(sizeof(Qnode));
    newnode->t1=t;
    newnode->next=NULL;
    return newnode;
}
queue *createQ()
{
    queue *q=(queue*)malloc(sizeof(queue));
    q->front=q->rear=NULL;
    return q;
}
int isEmptyQueue(queue *q)
{
    if (q->front == NULL)
        return 1;
    return 0;
}
void enQueue(queue *q,tree *t)
{
    Qnode *temp=create(t);
    if(q->rear==NULL)
    {
        q->front=q->rear=temp;
        return;
    }
    q->rear->next=temp;
    q->rear=temp;
}
tree *deQueue(queue *q)
{
    if(isEmptyQueue(q))
        return NULL;
    Qnode *temp=q->front;
    q->front=q->front->next;
    if(q->front==NULL)
        q->rear=NULL;
    tree *tem=temp->t1;
    free(temp);
    return tem;
}
/*void preOrder(tree *root)
{
    if(root==NULL)
        return;
    printf("%d ",root->data);
    preOrder(root->left);
    preOrder(root->right);
}
void inOrder(tree *root)
{
    if(root==NULL)
        return;
    inOrder(root->left);
    printf("%d ",root->data);
    inOrder(root->right);
}
void postOrder(tree *root)
{
    if(root==NULL)
        return;
    postOrder(root->left);
    postOrder(root->right);
    printf("%d ",root->data);
}*/
void preOrder(tree *root)
{
    stack *a=NULL;
    tree *curr=root;
    while(curr!=NULL||a!=NULL)
    {
        if(curr!=NULL)
        {
            printf("%d ",curr->data);
            push(curr,&a);
            curr=curr->left;
        }
        else
        {
            curr=pop(&a);
            curr=curr->right;
        }
    }
}
void inOrder(tree *root)
{
    stack *a=NULL;
    tree *curr=root;
    while(curr!=NULL||a!=NULL)
    {
        if(curr!=NULL)
        {
            push(curr,&a);
            curr=curr->left;
        }
        else
        {
            if(a!=NULL)
            {
                curr = pop(&a);
                printf("%d ", curr->data);
                curr = curr->right;
            }
        }
    }
}
void postOrder(tree *root)
{
    stack *b=NULL,*c=NULL;
    tree *curr=root;
    if(curr==NULL)
        return;
    push(curr,&b);
    while (!isEmpty(b))
    {
        curr=pop(&b);
        push(curr,&c);
        if(curr->left!=NULL)
            push(curr->left,&b);
        if(curr->right!=NULL)
            push(curr->right,&b);
    }
    while (!isEmpty(c))
    {
        curr=pop(&c);
        printf("%d ",curr->data);
    }
}
/*int height(tree *t)
{
    if(t==NULL)
        return 0;
    int l=(height(t->left));
    int r=(height(t->right));
    if(l>r)
        return (l+1);
    else
        return (r+1);
}
void levelOrder(tree *root,int level)
{
    if(root==NULL)
        return;
    if(level==1)
        printf("%d ",root->data);
    else if(level>1)
    {
        levelOrder(root->left,level-1);
        levelOrder(root->right,level-1);
    }
}
void printBreadthTraverse(tree *root)
{
    int level=height(root);
    int i;
    for(i=0;i<=level;i++)
        levelOrder(root,i);
}*/
void printBreadthTraverse(tree *root)
{
    queue *q=createQ();
    tree *curr=root;
    while (curr!=NULL)
    {
        printf("%d ",curr->data);
        if(curr->left!=NULL)
            enQueue(q,curr->left);
        if(curr->right!=NULL)
            enQueue(q,curr->right);
        curr=deQueue(q);
    }
}
int search(int s[], int start, int end, int val)
{
    int i;
    for(i = start; i <= end; i++)
    {
        if(s[i] == val)
            return i;
    }
}
tree* construct_Pre_and_In(int in[], int pre[], int inF, int inL)
{
    static int index=0;
    if(inF>inL)
        return NULL;
    tree *n=newtree(pre[index++]);
    if(inF==inL)
        return n;
    int inIndex=search(in,inF,inL,n->data);
    n->left=construct_Pre_and_In(in,pre,inF,inIndex-1);
    n->right=construct_Pre_and_In(in,pre,inIndex+1,inL);
    return n;
}
tree* construct_In_and_Post(int in[],int pos[], int inF, int inL, int *index)
{
    if(inF>inL)
        return NULL;
    tree *n=newtree(pos[*index]);
    (*index)--;
    if(inF==inL)
        return n;
    int inIndex=search(in,inF,inL,n->data);
    n->right=construct_In_and_Post(in,pos,inIndex+1,inL,index);
    n->left=construct_In_and_Post(in,pos,inF,inIndex-1,index);
    return n;
}
tree *insert(tree *t1, int val)
{
    tree *tree1=newtree(val);
    if(t1==NULL||t1->data==val)
        return tree1;
    else
    {
        if(t1->data<val)
            t1->right=insert(t1->right,val);
        else if(t1->data>val)
            t1->left=insert(t1->left,val);
    }
    return t1;
}
tree *search_bst(tree *t1,int data)
{
    if(t1==NULL||t1->data==data)
        return t1;
    if(t1->data>data)
        return search_bst(t1->left,data);
    else if(t1->data<data)
        return search_bst(t1->right,data);
}
tree* minNode(tree *root)
{
    tree *curr=root;
    while (curr->left!=NULL)
        curr=curr->left;
    return curr;
}
tree* delete(tree *root,int data)
{
    if(root==NULL)
        return NULL;
    if (data < root->data)
        root->left=delete(root->left,data);
    else if (data > root->data)
        root->right=delete(root->right,data);
    else
    {
        if (root->left==NULL)
        {
            tree *temp=root->right;
            free(root);
            return temp;
        }
        else if(root->right==NULL)
        {
            tree *temp=root->left;
            free(root);
            return temp;
        }
        tree *temp=minNode(root->right);
        root->data=temp->data;
        root->right=delete(root->right,temp->data);
    }
    return root;
}
void postOrder1(tree *root)
{
    if(root==NULL)
        return;
    int x=0;
    if(root->left==NULL && root->right==NULL)
        x=1;
    postOrder1(root->left);
    postOrder1(root->right);
    if(x)
    {
        printf("%d",root->data);
        root=delete(root,root->data);
        printf("%d",root->data);
        return;
    }
}
int main()
{
    /*int n;
    printf("Enter no of terms: ");
    scanf("%d",&n);
    //int pre[n],in[n];
    int pos[n],in[n];
    int i;
    //int choice;
    //printf("Enter your choice: 1 for Pre-Order")
    printf("Enter post-order: ");
    for(i=0;i<n;i++)
        scanf("%d",&pos[i]);
    printf("Enter in-order: ");
    for (i=0;i<n;i++)
        scanf("%d",&in[i]);
    int h= sizeof(in)/ sizeof(in[0]);
    int index=h-1;
    //tree *new1=construct_Pre_and_In(in,pre,0,h-1);
    //tree *new1=construct_In_and_Post(in,pos,0,h-1,&index);
    //new1->left=newtree(5);
    //new1->right=newtree(15);
    //new1->left->left=newtree(3);
    //new1->left->right=newtree(6);*/
    int choice;
    int data;
    tree *new1=NULL,*temp=NULL;
    do
    {
        printf("Enter 1 to insert, 2 to search, 3 to delete a node, 0 to exit: ");
        scanf("%d",&choice);
        switch (choice)
        {
            case 1:
                printf("Enter data: ");
                scanf("%d", &data);
                new1=insert(new1,data);
                break;
            case 0:
                break;
            case 2:
                printf("Enter value to be searched: ");
                scanf("%d",&data);
                temp=search_bst(new1,data);
                if(temp->data==data)
                    printf("\n%d found in the tree.",temp->data);
                else
                    printf("\nValue not found in the tree.");
                break;
            case 3:
                printf("Enter value to be deleted: ");
                scanf("%d",&data);
            case 4:
                postOrder1(new1);
                break;
            default:
                printf("\nSorry, Wrong Input");
        }
    }while (choice);
    printf("\nTree printed in Pre Order: ");
    preOrder(new1);
    printf("\nTree printed in In Order: ");
    inOrder(new1);
    printf("\nTree printed in Post Order: ");
    postOrder(new1);
    printf("\nTree printed in Breadth Order Traversal: ");
    printBreadthTraverse(new1);
    return 0;
}