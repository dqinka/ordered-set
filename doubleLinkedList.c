/**
 * @file doubleLinkedList.c
 * @brief Implementation of the double linked list operations.
 *
 * See doubleLinkedList.h for the data types and the full description of
 * each operation.
 *
 * @author Brian Redmond (data types, create/delete, getData, navigation)
 * @author Person 2 (insertAfter, insertBefore, deleteCurrent)
 */

#include <stdlib.h>
#include "doubleLinkedList.h"

/* ------------------------------------------------------------------------ */
/* Create / delete                                                          */
/* ------------------------------------------------------------------------ */

DoubleLinkedList *createDoubleLinkedList(void)
{
    DoubleLinkedList *list = malloc(sizeof *list);
    if (list == NULL)
    {
        return NULL;
    }

    list->head = malloc(sizeof *list->head);
    list->tail = malloc(sizeof *list->tail);
    if (list->head == NULL || list->tail == NULL)
    {
        /* free(NULL) is safe, so free whatever was allocated */
        free(list->head);
        free(list->tail);
        free(list);
        return NULL;
    }

    /* link the two sentinels to each other: head <-> tail */
    list->head->data = 0;
    list->head->prev = NULL;
    list->head->next = list->tail;

    list->tail->data = 0;
    list->tail->prev = list->head;
    list->tail->next = NULL;

    list->current = list->head;
    return list;
}

void deleteDoubleLinkedList(DoubleLinkedList *list)
{
    if (list == NULL)
    {
        return;
    }

    /* walk from head to tail, freeing each node (sentinels included) */
    ListNode *node = list->head;
    while (node != NULL)
    {
        ListNode *nextNode = node->next;
        free(node);
        node = nextNode;
    }

    free(list);
}

/* ------------------------------------------------------------------------ */
/* Data access and navigation                                               */
/* ------------------------------------------------------------------------ */

int getData(const DoubleLinkedList *list)
{
    if (list == NULL)
    {
        return 0;
    }
    return list->current->data;
}

void gotoNextNode(DoubleLinkedList *list)
{
    /* at tail there is no successor: leave the list unchanged */
    if (list != NULL && list->current != list->tail)
    {
        list->current = list->current->next;
    }
}

void gotoPreviousNode(DoubleLinkedList *list)
{
    /* at head there is no predecessor: leave the list unchanged */
    if (list != NULL && list->current != list->head)
    {
        list->current = list->current->prev;
    }
}

void gotoHead(DoubleLinkedList *list)
{
    if (list != NULL)
    {
        list->current = list->head;
    }
}

void gotoTail(DoubleLinkedList *list)
{
    if (list != NULL)
    {
        list->current = list->tail;
    }
}

bool isAtHead(const DoubleLinkedList *list)
{
    return list != NULL && list->current == list->head;
}

bool isAtTail(const DoubleLinkedList *list)
{
    return list != NULL && list->current == list->tail;
}

/* ------------------------------------------------------------------------ */
/* Insert / delete (Person 2)                                               */
/* ------------------------------------------------------------------------ */

/* TODO Person 2: implement insertAfter(), insertBefore() and deleteCurrent()
 * here, following the contracts documented in doubleLinkedList.h. */
