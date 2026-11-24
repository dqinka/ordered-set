/**
 * @file orderedIntSet.c
 * @brief
 *
 * Implementation of the ordered integer set, built on a double linked list.
 * See orderedIntSet.h for the data types and the full description of
 * each operation.
 *
 * @author Diana Sholomko (createOrderedSet, deleteOrderedSet, addElement and removeElement)
 * @author Person 4 (setIntersection and setUnion)
 * @date November 2026
 */

#include <stdlib.h>
#include <stdio.h>
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

/* ------------------------------------------------------------------------- */
/* Person 4: ordered set intersection and union                               */
/* ------------------------------------------------------------------------- */

/**
 * @brief Appends a value to the end of a result set.
 * @param result Set being built in ascending order.
 * @param value Next value, greater than the values already in result.
 * @return true on success, or false if a node could not be allocated.
 */
static bool appendSorted(OrderedIntSet *result, int value)
{
    gotoTail(result->list);

    if (insertBefore(result->list, value) != LIST_OK)
    {
        return false;
    }

    result->count++;
    return true;
}

OrderedIntSet *setIntersection(const OrderedIntSet *s1, const OrderedIntSet *s2)
{
    if (s1 == NULL || s2 == NULL)
    {
        return NULL;
    }

    OrderedIntSet *result = createOrderedSet();
    if (result == NULL)
    {
        return NULL;
    }

    /* Read the nodes directly so that the input sets' current pointers stay put. */
    const ListNode *a = s1->list->head->next;
    const ListNode *b = s2->list->head->next;

    while (a != s1->list->tail && b != s2->list->tail)
    {
        if (a->data < b->data)
        {
            a = a->next;
        }
        else if (a->data > b->data)
        {
            b = b->next;
        }
        else
        {
            if (!appendSorted(result, a->data))
            {
                deleteOrderedSet(result);
                return NULL;
            }

            a = a->next;
            b = b->next;
        }
    }

    return result;
}

OrderedIntSet *setUnion(const OrderedIntSet *s1, const OrderedIntSet *s2)
{
    if (s1 == NULL || s2 == NULL)
    {
        return NULL;
    }

    OrderedIntSet *result = createOrderedSet();
    if (result == NULL)
    {
        return NULL;
    }

    const ListNode *a = s1->list->head->next;
    const ListNode *b = s2->list->head->next;

    while (a != s1->list->tail || b != s2->list->tail)
    {
        int nextValue;

        if (b == s2->list->tail ||
            (a != s1->list->tail && a->data < b->data))
        {
            nextValue = a->data;
            a = a->next;
        }
        else if (a == s1->list->tail || b->data < a->data)
        {
            nextValue = b->data;
            b = b->next;
        }
        else
        {
            /* Equal values appear only once in the result. */
            nextValue = a->data;
            a = a->next;
            b = b->next;
        }

        if (!appendSorted(result, nextValue))
        {
            deleteOrderedSet(result);
            return NULL;
        }
    }

    return result;
}

/* Temporary shared helper for the team's incomplete Person 5 print function.
 * Remove/replace this one when the final group printToStdout is merged. */
void printToStdout(const OrderedIntSet *s)
{
    if (s == NULL)
    {
        printf("{}\n");
        return;
    }

    const ListNode *node = s->list->head->next;
    printf("{");

    while (node != s->list->tail)
    {
        printf("%d", node->data);
        if (node->next != s->list->tail)
        {
            printf(" , ");
        }
        node = node->next;
    }

    printf("}\n");
}
