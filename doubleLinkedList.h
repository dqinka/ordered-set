/**
 * @file doubleLinkedList.h
 * @brief Data types and operations for a double linked list of integers.
 *
 * The list is built around two sentinel nodes, @c head and @c tail, which
 * never hold user data. An empty list therefore consists of head and tail
 * only. A @c current pointer marks the node that the navigation, insert and
 * delete operations act on.
 *
 * Layout of a list holding 3 and 7, with current on 7:
 * @verbatim
   head <-> [3] <-> [7] <-> tail
                     ^
                  current
   @endverbatim
 *
 * @author Brian Redmond (data types, create/delete, getData, navigation)
 * @author Jamila Mohamed (insertAfter, insertBefore, deleteCurrent)
 */

#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <stdbool.h>

/**
 * @brief A single node of the double linked list.
 */
typedef struct ListNode
{
    int data;               /**< Integer stored in this node (0 for sentinels). */
    struct ListNode *next;  /**< Successor node, NULL for the tail sentinel.   */
    struct ListNode *prev;  /**< Predecessor node, NULL for the head sentinel. */
} ListNode;

/**
 * @brief A double linked list with head and tail sentinel nodes.
 */
typedef struct DoubleLinkedList
{
    ListNode *head;     /**< Head sentinel (holds no user data). */
    ListNode *tail;     /**< Tail sentinel (holds no user data). */
    ListNode *current;  /**< Node the list operations act on.     */
} DoubleLinkedList;

/**
 * @brief Result codes returned by the list operations that can fail.
 */
typedef enum
{
    LIST_OK,               /**< Operation succeeded.                              */
    LIST_INVALID_POSITION, /**< Not allowed at current position (head/tail rule). */
    LIST_ALLOCATION_ERROR  /**< malloc() failed, list is unchanged.               */
} ListResult;

/* ------------------------------------------------------------------------ */
/* Create / delete                                                          */
/* ------------------------------------------------------------------------ */

/**
 * @brief Creates a new empty double linked list.
 *
 * The new list consists only of the head and tail sentinels, linked to each
 * other. The current node is set to head.
 *
 * @pre  None.
 * @post An empty double linked list is created.
 * @return Pointer to the new list, or NULL if memory allocation failed.
 */
DoubleLinkedList *createDoubleLinkedList(void);

/**
 * @brief Deletes a list including all of its nodes.
 *
 * Frees every node (sentinels included) and then the list itself. The
 * caller must not use the pointer afterwards.
 *
 * @pre  @p list is a valid double linked list (NULL is accepted and ignored).
 * @post The entire list is deleted.
 * @param list List to delete.
 */
void deleteDoubleLinkedList(DoubleLinkedList *list);

/* ------------------------------------------------------------------------ */
/* Data access and navigation                                               */
/* ------------------------------------------------------------------------ */

/**
 * @brief Returns the data associated with the current node.
 *
 * If current is the head or tail sentinel, 0 is returned. That value is not
 * user data, so callers should check isAtHead() / isAtTail() first.
 *
 * @pre  @p list is a valid double linked list.
 * @post Data of the current node is returned, list is unchanged.
 * @param list List to read from.
 * @return Data of the current node.
 */
int getData(const DoubleLinkedList *list);

/**
 * @brief Sets the current node to the successor of current.
 *
 * @pre  @p list is a valid double linked list.
 * @post If current is not tail, current is set to its successor.
 *       Otherwise the list remains unchanged.
 * @param list List to navigate.
 */
void gotoNextNode(DoubleLinkedList *list);

/**
 * @brief Sets the current node to the predecessor of current.
 *
 * @pre  @p list is a valid double linked list.
 * @post If current is not head, current is set to its predecessor.
 *       Otherwise the list remains unchanged.
 * @param list List to navigate.
 */
void gotoPreviousNode(DoubleLinkedList *list);

/**
 * @brief Sets the current node to the head sentinel.
 *
 * @pre  @p list is a valid double linked list.
 * @post Current node is set to head.
 * @param list List to navigate.
 */
void gotoHead(DoubleLinkedList *list);

/**
 * @brief Sets the current node to the tail sentinel.
 *
 * @pre  @p list is a valid double linked list.
 * @post Current node is set to tail.
 * @param list List to navigate.
 */
void gotoTail(DoubleLinkedList *list);

/**
 * @brief Checks whether the current node is the head sentinel.
 *
 * Helper (not in the brief) so code using the list can detect the start of
 * the list when walking backwards.
 *
 * @pre  @p list is a valid double linked list.
 * @param list List to check.
 * @return true if current is head, false otherwise.
 */
bool isAtHead(const DoubleLinkedList *list);

/**
 * @brief Checks whether the current node is the tail sentinel.
 *
 * Helper (not in the brief) so code using the list can detect the end of
 * the list when walking forwards, e.g.:
 * @code
 * gotoHead(list);
 * gotoNextNode(list);
 * while (!isAtTail(list))
 * {
 *     int value = getData(list);
 *     ...
 *     gotoNextNode(list);
 * }
 * @endcode
 *
 * @pre  @p list is a valid double linked list.
 * @param list List to check.
 * @return true if current is tail, false otherwise.
 */
bool isAtTail(const DoubleLinkedList *list);

/* ------------------------------------------------------------------------ */
/* Insert / delete operations                                              */
/* ------------------------------------------------------------------------ */

/**
 * @brief Creates a new node holding @p newData and inserts it after current.
 *
 * @pre  @p list is a valid double linked list and @p newData is valid data.
 * @post If current is not tail, the new node is inserted after current and
 *       current is unchanged. Otherwise the list remains unchanged and an
 *       error is returned.
 * @param list    List to insert into.
 * @param newData Data for the new node.
 * @return LIST_OK, LIST_INVALID_POSITION (current is tail) or
 *         LIST_ALLOCATION_ERROR.
 */
ListResult insertAfter(DoubleLinkedList *list, int newData);

/**
 * @brief Creates a new node holding @p newData and inserts it before current.
 *
 * @pre  @p list is a valid double linked list and @p newData is valid data.
 * @post If current is not head, the new node is inserted before current and
 *       current is unchanged. Otherwise the list remains unchanged and an
 *       error is returned.
 * @param list    List to insert into.
 * @param newData Data for the new node.
 * @return LIST_OK, LIST_INVALID_POSITION (current is head) or
 *         LIST_ALLOCATION_ERROR.
 */
ListResult insertBefore(DoubleLinkedList *list, int newData);

/**
 * @brief Deletes the current node from the list.
 *
 * @pre  @p list is a valid double linked list.
 * @post If current is neither head nor tail, the current node is removed and
 *       current is set to its successor. Otherwise an error is returned.
 * @param list List to delete from.
 * @return LIST_OK or LIST_INVALID_POSITION (current is head or tail).
 */
ListResult deleteCurrent(DoubleLinkedList *list);

#endif /* DOUBLELINKEDLIST_H */
