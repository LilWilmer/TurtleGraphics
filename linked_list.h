#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "common.h"
#include "g_command.h"

typedef struct ListNode{
    GCommand *value;
    struct ListNode *next;
    struct ListNode *prev;
}ListNode;

typedef struct{
    int count;
    ListNode *head;
    ListNode *tail;
}LinkedList;

int createList(LinkedList **list);
int insertFirst(LinkedList *list, GCommand *value);
int insertLast(LinkedList *list, GCommand *value);
GCommand *removeFirst(LinkedList *list);
GCommand *removeLast(LinkedList *list);
GCommand *get(LinkedList *list, int index);
/*void display(LinkedList *list);*/
int freeList(LinkedList *list);
void freeListRec(ListNode *currNode);
int lincolnList(LinkedList *list);
void lincolnListRec(ListNode *currNode);

#endif