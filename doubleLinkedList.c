/**
 * @file doubleLinkedList.c
 * @brief Implementation of the double linked list operations.
 *
 * See doubleLinkedList.h for the data types and the full description of
 * each operation.
 *
 * @author Brian Redmond (data types, create/delete, getData, navigation)
 * @author Jamila Mohamed (insertAfter, insertBefore, deleteCurrent)
 * @date November 2026
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

ListResult insertAfter(DoubleLinkedList *list, int newData)
{
    // Do not insert after the tail sentinel.
    if (list == NULL || list->current == list->tail)
    {
        return LIST_INVALID_POSITION;
    }

    // Allocate memory for a new node.
    ListNode *newNode = malloc(sizeof *newNode);

    if (newNode == NULL)
    {
        return LIST_ALLOCATION_ERROR;
    }

    // Store the new integer.
    newNode->data = newData;

    // Connect the new node between current and the next node.
    newNode->prev = list->current;
    newNode->next = list->current->next;

    list->current->next->prev = newNode;
    list->current->next = newNode;

    return LIST_OK;
}

ListResult insertBefore(DoubleLinkedList *list, int newData)
{
    // Cannot insert before the head sentinel.
    if (list == NULL || list->current == list->head)
    {
        return LIST_INVALID_POSITION;
    }

    // Allocate memory for the new node.
    ListNode *newNode = malloc(sizeof *newNode);

    if (newNode == NULL)
    {
        return LIST_ALLOCATION_ERROR;
    }

    // Store the new value.
    newNode->data = newData;

    // Connect the new node before the current node.
    newNode->next = list->current;
    newNode->prev = list->current->prev;

    list->current->prev->next = newNode;
    list->current->prev = newNode;

    return LIST_OK;

}


ListResult deleteCurrent(DoubleLinkedList *list)
{
    // Cannot delete the head or tail sentinel.
    if (list == NULL ||
        list->current == list->head ||
        list->current == list->tail)
    {
        return LIST_INVALID_POSITION;
    }

    // Remember the node that needs to be deleted.
    ListNode *nodeToDelete = list->current;

    // Connect the previous node to the next node.
    nodeToDelete->prev->next = nodeToDelete->next;
    nodeToDelete->next->prev = nodeToDelete->prev;

    // Move current to the next node before deleting.
    list->current = nodeToDelete->next;

    // Free the memory.
    free(nodeToDelete);

    return LIST_OK;
}

