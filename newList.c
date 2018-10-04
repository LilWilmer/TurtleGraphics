/******************************************************************************
* AUTH: William Payne
* FILE: linkedlist.c
* LAST MOD: 24/9/18
* PURPOSE: Linked list abstract data type.
******************************************************************************/
#include "newList.h"

/*****************************************************************************
* FUNCTION: createList
*-----------------------------------------------------------------------------
*  IMPORTS:
*  'list' ~ A NULL LinkedList pointer
*
*  EXPORTS: none 
*
*  PURPOSE: 
*  Creates, allocates and assigns an empty LinkedList to 'list'.
*
*  NOTES:
*  The returned LinkedList must be freed before the program ends.
*****************************************************************************/
int createList(LinkedList **list)
{
    *list = (LinkedList*)malloc(sizeof(LinkedList));
    (*list)->count = 0;
    (*list)->head = NULL;
    (*list)->tail = NULL;

    return 1;
}

/*****************************************************************************
* FUNCTION: insertFirst
*-----------------------------------------------------------------------------
*  IMPORTS:
*  'list'   ~ A LinkedList pointer.
*  'value'  ~ The GCommand pointer to be inserted.
*
*  EXPORTS: 
*  '0'  ~ An int representing the success of the function.
*
*  PURPOSE: 
*  Place an GCommand struct in a new ListNode then insert it into the front of
*  the imported list.
*
*  ERROR CODES: 
*  0 ~ Success.
*  NOTES: 
*  --
*****************************************************************************/
int insertFirst(LinkedList *list, void *value)
{
    ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->value = value;

    if( list->count == 0)
    {
        list->head = newNode;
        list->tail = newNode;   
    }
    else
    {
        newNode->prev = NULL;
        newNode->next = list->head;

        list->head->prev = newNode;
        list->head = newNode;

        list->count++;
    }
    return 0;
}

/*****************************************************************************
* FUNCTION: insertFirst
*-----------------------------------------------------------------------------
*  IMPORTS:
*  'list'   ~ A LinkedList pointer.
*  'value'  ~ The GCommand pointer to be inserted.
*
*  EXPORTS: 
*  '0'  ~ An int representing the success of the function.
*
*  PURPOSE: 
*  Place an GCommand struct in a new ListNode then insert it into the front of
*  the imported list.
*
*  ERROR CODES: 
*  0 ~ Success.
*  NOTES: 
*  --
*****************************************************************************/
int insertLast(LinkedList *list, void *value)
{
    ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));

    newNode->value = value;
    newNode->next = NULL;

    if( list->count == 0)
    {
        list->head = newNode;
        list->tail = newNode;
        newNode->prev = NULL;
    }
    else
    {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    
    list->count++;

    return 0;
}

/*****************************************************************************
* FUNCTION: removeFirst
*-----------------------------------------------------------------------------
*  IMPORTS:
*  'list'   ~ A LinkedList pointer.
*
*  EXPORTS: 
*  'value'  ~ A pointer to a GCommand struct.
*
*  PURPOSE: 
*  Removes the first value in the LinkedList 'list' then removes the node.
*
*  NOTES: 
*  Returns NULL if list is empty.
*****************************************************************************/
void *removeFirst(LinkedList *list)
{
    void *value = NULL;
    ListNode *temp = NULL;

    if(list->count > 0)
    {
        value = list->head->value;
        temp = list->head;
        list->head = list->head->next;
        if(list->head != NULL)
        {
            list->head->prev = NULL;
        }

        free(temp);

        list->count--;
    }

    return value;
}

/*****************************************************************************
* FUNCTION: removeLast
*-----------------------------------------------------------------------------
*  IMPORTS:
*  'list'   ~ A LinkedList pointer.
*
*  EXPORTS: 
*  'value'  ~ A pointer to a GCommand struct.
*
*  PURPOSE: 
*  Removes the last value in the LinkedList 'list' then removes the node.
*
*  NOTES: 
*  Returns NULL if list is empty.
*****************************************************************************/
GCommand *removeLast(LinkedList *list)
{
    GCommand *value = NULL;
    ListNode *temp;

    if(list->count > 0)
    {
        value = list->tail->value;
        temp = list->tail;
        list->tail = list->tail->prev;
        if(list->tail != NULL)
        {
            list->tail->next = NULL;
        }
        free(temp);

        list->count--;
    }
    return value;
}

/*****************************************************************************
* FUNCTION: 
*-----------------------------------------------------------------------------
*  IMPORTS: 
*  'list'   ~ A pointer to the Linked List
*  'index'  ~ An int representing the place in the list that a value exists
*
*  EXPORTS: 
*  'value'  ~ An GCommand pointer from the LinkedList.
*
*  PURPOSE: 
*  Returns a pointer to the value located at the specified index in the list.
*
*  NOTES: 
*  Returns NULL if index points exceeds the bounds of the list.
*****************************************************************************/
GCommand *get(LinkedList *list, int index)
{
    int ii;
    ListNode *temp;
    GCommand *value = NULL;

    if(list->count > index && index >= 0)
    {
        temp = list->head;
        for(ii = 0; ii < index; ii++)
        {
            temp = temp->next;
        }

        value = temp->value;
    }
    return value;
}

/*****************************************************************************
* FUNCTION: display
*-----------------------------------------------------------------------------
*  IMPORTS:
*  'list'   ~ A pointer to a Linked List
*
*  EXPORTS: none
*  ''
*
*  PURPOSE: 
*  Prints out the contents of the list.
*
*  NOTES: 
*  --
*****************************************************************************/
/*void display(LinkedList *list)
{
    ListNode *temp = NULL;
    if(list->count == 0)
    {
        printf("List is empty");
    }
    else
    {
        temp = list->head;
        do
        {
            displayEntry(temp->value);
            temp = temp->next;
        }
        while(temp != NULL);
    }
}*/

/*****************************************************************************
* FUNCTION: freeList
*-----------------------------------------------------------------------------
*  IMPORTS: 
*  'list'       ~ Pointer to LinkedList for freeing.
*
*  EXPORTS: 
*  'success'    ~ Int representing the success of the function.
*
*  PURPOSE: 
*  Wrapper for freeListRec.
*
*  ERROR CODES: 
*  0 ~ List freed
*  1 ~ List not freed
*
*  NOTES: 
*  WRAPPER METHOD.
*****************************************************************************/
int freeList(LinkedList *list)
{
    int success = 1;

    freeListRec(list->head);
    free(list);
    success = 0;

    return success;
}

/*****************************************************************************
* FUNCTION: freeListRec
*-----------------------------------------------------------------------------
*  IMPORTS: 
*  'list'   ~ A pointer to a LinkedList
*
*  EXPORTS: 
*  '0'      ~ An int representing the success of the free
*
*  PURPOSE: 
*  --
*
*  ERROR CODES: 
*  --
*
*  NOTES: 
*  DOES NOT FREE THE THE ENTRIES
*****************************************************************************/
void freeListRec(ListNode *currNode)
{
    if(currNode != NULL)
    {
        freeListRec(currNode->next);
    }
    free(currNode);
}
/*****************************************************************************
* FUNCTION: licolnList
*-----------------------------------------------------------------------------
*  IMPORTS: 
*  'list'       ~ Pointer to LinkedList for freeing.
*
*  EXPORTS: 
*  'success'    ~ Int representing the success of the function.
*
*  PURPOSE: 
*  Wrapper for freeListRec.
*
*  ERROR CODES: 
*  0 ~ List freed
*  1 ~ List not freed
*
*  NOTES: 
*  WRAPPER METHOD.
*****************************************************************************/
int lincolnList(LinkedList *list)
{
    int success = 1;

    if(list != NULL)
    {
        lincolnListRec(list->head);
        free(list);
    }
    success = 0;

    return success;
}

/*****************************************************************************
* FUNCTION: lincolnListRec
*-----------------------------------------------------------------------------
*  IMPORTS: 
*  'list'   ~ A pointer to a LinkedList
*
*  EXPORTS: 
*  '0'      ~ An int representing the success of the free
*
*  PURPOSE: 
*  --
*
*  ERROR CODES: 
*  --
*
*  NOTES: 
*  FREES EVERYTHING
*****************************************************************************/
void lincolnListRec(ListNode *currNode)
{
    if(currNode != NULL)
    {
        lincolnListRec(currNode->next);
        freeCommand(currNode->value);
        free(currNode);
    }
}
