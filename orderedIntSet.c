/**
 * @file orderedIntSet.c
 * @brief
 *
 * Implementation of the ordered integer set, built on a double linked list.
 * See orderedIntSet.h for the data types and the full description of
 * each operation.
 *
 * @author Diana Sholomko (createOrderedSet, deleteOrderedSet, addElement and removeElement)
 * @date November 2026
 */

#include <stdlib.h>
#include "orderedIntSet.h"

/**
 * @brief Moves the list's current node to the first element that is not
 *        smaller than elem, or to the tail if there is no such element.
 * @param list Pointer to the list (must be sorted ascending).
 * @param elem Number to search for.
 */
static void gotoFirstNotLess(DoubleLinkedList *list, int elem)
{
    gotoHead(list);
    gotoNextNode(list);   /* first real element, or the tail if the list is empty */

    while (!isAtTail(list) && getData(list) < elem)
    {
        gotoNextNode(list);
    }
}

OrderedIntSet *createOrderedSet(void)
{
    OrderedIntSet *s = malloc(sizeof *s);
    if (s == NULL)
    {
        return NULL;
    }

    s->list = createDoubleLinkedList();
    if (s->list == NULL)
    {
        free(s);          /* do not leak the set if the list could not be created */
        return NULL;
    }

    s->count = 0;
    return s;
}

void deleteOrderedSet(OrderedIntSet *s)
{
    if (s == NULL)
    {
        return;
    }

    deleteDoubleLinkedList(s->list);   /* frees all nodes first ... */
    free(s);                           /* ... then the set itself */
}

SetResult addElement(OrderedIntSet *s, int elem)
{
    gotoFirstNotLess(s->list, elem);

    /* stopped on a real node with the same value: duplicate */
    if (!isAtTail(s->list) && getData(s->list) == elem)
    {
        return NUMBER_ALREADY_IN_SET;
    }

    /* insert before the node we stopped on (or before the tail) */
    if (insertBefore(s->list, elem) != LIST_OK)
    {
        return ALLOCATION_ERROR;   /* count is not changed on failure */
    }

    s->count++;
    return NUMBER_ADDED;
}

SetResult removeElement(OrderedIntSet *s, int elem)
{
    gotoFirstNotLess(s->list, elem);

    /* reached the tail, or stopped on a different (larger) value: not present */
    if (isAtTail(s->list) || getData(s->list) != elem)
    {
        return NUMBER_NOT_IN_SET;
    }

    deleteCurrent(s->list);
    s->count--;
    return NUMBER_REMOVED;
}