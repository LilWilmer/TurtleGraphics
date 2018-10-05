#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "common.h"
#include "g_command.h"

/*TYPEDEFS AND STRUCTS------------------------------------------------------*/
/*FREEVALUE function pointer*/
typedef void (*FREEVALUE)(void*);

/*Generic ListNode*/
typedef struct ListNode{
    void *value;
    struct ListNode *next;
    struct ListNode *prev;
}ListNode;

typedef struct{
    int count;
    ListNode *head;
    ListNode *tail;
    FREEVALUE freeValuePtr;
}LinkedList;

int createList(LinkedList **list);
int insertFirst(LinkedList *list, void *value);
int insertLast(LinkedList *list, void *value);
void *removeFirst(LinkedList *list);
void *removeLast(LinkedList *list);
void *get(LinkedList *list, int index);
/*void display(LinkedList *list);*/
int freeList(LinkedList *list);
void freeListRec(ListNode *currNode);
int completeFreeList(LinkedList *list);
void completeFreeRec(ListNode *currNode, FREEVALUE freeValue);

#endif