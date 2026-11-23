/**
 * @file orderedIntSet.h
 * @brief Ordered set of integers, built on a double linked list.
 *
 * An OrderedIntSet stores its integers in ascending order and never holds
 * the same number twice. The numbers are kept in a DoubleLinkedList, and
 * the set also keeps a counter of how many elements it contains. The
 * counter increases when an element is added and decreases when one is
 * removed.
 *
 * The operations report their outcome with the SetResult enumeration.
 *
 * @author Diana (set type, createOrderedSet, deleteOrderedSet, addElement, removeElement)
 */

#ifndef ORDEREDINTSET_H
#define ORDEREDINTSET_H

#include "doubleLinkedList.h"

/**
 * @brief Return values of the ordered set operations.
 */
typedef enum {
    NUMBER_ADDED,           /**< Element was inserted into the set. */
    NUMBER_ALREADY_IN_SET,  /**< Element already exists in the set. */
    NUMBER_REMOVED,         /**< Element was removed from the set. */
    NUMBER_NOT_IN_SET,      /**< Element does not exist in the set. */
    ALLOCATION_ERROR        /**< Memory allocation failed; the set was not changed. */
} SetResult;

/**
 * @brief Ordered set of integers, stored in ascending order without duplicates.
 */
typedef struct {
    DoubleLinkedList *list; /**< Double linked list holding the elements. */
    int count;              /**< Number of elements currently in the set. */
} OrderedIntSet;

/**
 * @brief Creates an empty ordered set.
 * @return Pointer to the new set, or NULL if allocation fails.
 */
OrderedIntSet *createOrderedSet(void);

/**
 * @brief Removes an ordered set from memory, including all its elements.
 * @param s Pointer to the set to delete.
 */
void deleteOrderedSet(OrderedIntSet *s);

/**
 * @brief Adds an element to the set at its correct (ascending) position.
 * @param s Pointer to the set.
 * @param elem Number to add.
 * @return NUMBER_ADDED if the element was added,
 *         NUMBER_ALREADY_IN_SET if it was already present,
 *         ALLOCATION_ERROR if memory allocation failed.
 */
SetResult addElement(OrderedIntSet *s, int elem);

/**
 * @brief Removes an element from the set.
 * @param s Pointer to the set.
 * @param elem Number to remove.
 * @return NUMBER_REMOVED if the element was removed,
 *         NUMBER_NOT_IN_SET if it was not in the set.
 */
SetResult removeElement(OrderedIntSet *s, int elem);

#endif // ORDEREDINTSET_H
