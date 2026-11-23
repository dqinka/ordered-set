
/**
 * @file testDoubleLinkedList.c
 * @brief Temporary tests for double linked list operations.
 * @details Tests insertion, deletion, navigation and error handling.
 * @author Jamila Mohamed
 */

#include <stdio.h>
#include <assert.h>
#include "doubleLinkedList.h"

/**
 * @brief Runs tests for the double linked list operations.
 * @details Checks insertion, deletion, navigation and invalid
 * positions using assertions.
 * @return 0 if all tests pass.
 */
int main(void)
{
    // Create a new empty double linked list.
    DoubleLinkedList *list = createDoubleLinkedList();

    // Check that the list was created successfully.
    assert(list != NULL);
    assert(isAtHead(list));

    // Test inserting a node after the current node.
    assert(insertAfter(list, 10) == LIST_OK);
    gotoNextNode(list);
    assert(getData(list) == 10);

    // Test inserting a node before the current node.
    assert(insertBefore(list, 5) == LIST_OK);
    gotoPreviousNode(list);
    assert(getData(list) == 5);

    // Test deleting the current node.
    assert(deleteCurrent(list) == LIST_OK);
    assert(getData(list) == 10);

    // Test inserting after the tail (should fail).
    gotoTail(list);
    assert(insertAfter(list, 20) == LIST_INVALID_POSITION);

    // Test inserting before the head (should fail).
    gotoHead(list);
    assert(insertBefore(list, 20) == LIST_INVALID_POSITION);

    // Test deleting the head (should fail).
    assert(deleteCurrent(list) == LIST_INVALID_POSITION);

    // Test deleting the tail (should fail).
    gotoTail(list);
    assert(deleteCurrent(list) == LIST_INVALID_POSITION);

    // Test inserting before the tail.
    assert(insertBefore(list, 30) == LIST_OK);
    gotoPreviousNode(list);
    assert(getData(list) == 30);

    // Test inserting after the current node.
    assert(insertAfter(list, 40) == LIST_OK);
    gotoNextNode(list);
    assert(getData(list) == 40);

    // Test deleting a node and moving current forward.
    assert(deleteCurrent(list) == LIST_OK);
    assert(isAtTail(list));

    // Free all allocated memory.
    deleteDoubleLinkedList(list);

    printf("All double linked list tests passed!\n");

    return 0;
}
