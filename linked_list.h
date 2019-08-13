/*****************************************************************************
* AUTH: William Payne
* FILE: linked_list.h
* LAST MOD: 05/10/2018
* PURPOSE: LinkedList header file
*****************************************************************************/
/*HEADER GUARD--------------------------------------------------------------*/
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/*INCLUDE STATEMENTS--------------------------------------------------------*/
#include "common.h"
#include "g_command.h"

/*TYPEDEFS AND STRUCTS------------------------------------------------------*/

/*FreeFunc function pointer*/
typedef void (*FreeFunc)(void*);

/*----------------------------------------------------------------------------
* Generic ListNode:
* ---   ---   ---   ---
* Tag: ListNode
* Typedef: ListNode
* Purpose: ListNode in a linked list ADT.
* FIELDS:
*   value(void*)    ~ Pointer to any kind of data.
*   next(ListNode*) ~ Pointer to the next node in the list
*   prev(ListNode*) ~ Pointer to the previous node in the list
* ---   ---   ---   ---   ---   ---   ---   ---   ---   ---   ---   ---   ---
*/
typedef struct ListNode{
    void *value;
    struct ListNode *next;
    struct ListNode *prev;
}ListNode;

/*----------------------------------------------------------------------------
* Generic LinkedList:
* ---   ---   ---   ---
* Tag: --
* typedef: LinkedList
* Purpose: Holds the references to the first and last node in a linked list
*          as well as a function pointer for freeing the void data.
* FIELDS:
*   count(int)          ~ Keeps track of the number nodes in the list.
*   head(ListNode*)     ~ Pointer to the first node in the list.
*   tail(ListNode*)     ~ Pointer to the last node in the list.
*   freeFunc(FreeFunc)  ~ Function pointer for freeing the data void* 'value'
*                         points at.
* ---   ---   ---   ---   ---   ---   ---   ---   ---   ---   ---   ---   ---
*/
typedef struct{
    int count;
    ListNode *head;
    ListNode *tail;
    FreeFunc freeFunc;
}LinkedList;

/**
* createList():
* --- --- --- ---
* Creates, allocates and assigns an empty LinkedList to 'list'.
*/
int createList(LinkedList **list);

/**
* insertFirst():
* --- --- --- ---
* Place an GCommand struct in a new ListNode then insert it into the front
* of the imported list.
*/
int insertFirst(LinkedList *list, void *value);

/**
* insertLast():
* --- --- --- ---
* Assign a void pointer to a new ListNode then inserts it at the end
* of the imported list.
*/
int insertLast(LinkedList *list, void *value);

/**
* removeFirst():
* --- --- --- ---
* Returns the first value in the LinkedList 'list' then removes the node.
*/
void *removeFirst(LinkedList *list);

/**
* removeLast():
* --- --- --- ---
* Returns the last value in the LinkedList 'list' then removes the node
*/
void *removeLast(LinkedList *list);

/**
* get():
* --- --- --- ---
* Returns a pointer to the value located at the specified index in the list.
*/
void *get(LinkedList *list, int index);

/**
* freeList:
* --- --- --- ---
* Wrapper for freeListRec.
*/
int freeList(LinkedList *list);



/**
* completeFreeList:
* --- --- --- ---
* Wrapper for completeFreeRec.
*/
int completeFreeList(LinkedList *list);



#endif
