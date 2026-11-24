/**
 * @file testOrderedIntSet.c
 * @brief Checks the three set operations with different input sets.
 * @author Shayan Khan
 * @date 2026-11-24
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "orderedIntSet.h"

/**
 * @brief Creates a set from an array of values.
 * @param values Values to add, or NULL when count is zero.
 * @param count Number of values.
 * @return New set, or NULL if allocation fails.
 */
static OrderedIntSet *makeSet(const int values[], int count)
{
    OrderedIntSet *set = createOrderedSet();
    if (set == NULL) {
        return NULL;
    }
    for (int i = 0; i < count; i++) {
        if (addElement(set, values[i]) == ALLOCATION_ERROR) {
            deleteOrderedSet(set);
            return NULL;
        }
    }
    return set;
}

/**
 * @brief Compares a set with an expected array of values.
 * @param set Set to check.
 * @param expected Expected values, in ascending order.
 * @param count Number of expected values.
 * @return true if the values and element count match.
 */
static bool matches(const OrderedIntSet *set, const int expected[], int count)
{
    if (set == NULL || set->count != count) {
        return false;
    }
    const ListNode *node = set->list->head->next;
    for (int i = 0; i < count; i++) {
        if (node == set->list->tail || node->data != expected[i]) {
            return false;
        }
        node = node->next;
    }
    return node == set->list->tail;
}

/**
 * @brief Checks a result, prints PASS or FAIL, and deletes the result set.
 * @param name Name of the check.
 * @param result Result set to check and delete.
 * @param expected Expected values, in ascending order.
 * @param count Number of expected values.
 * @return 0 if the check passes, or 1 if it fails.
 */
static int checkResult(const char *name, OrderedIntSet *result,
                       const int expected[], int count)
{
    bool passed = matches(result, expected, count);
    deleteOrderedSet(result);
    if (passed) {
        printf("PASS: %s\n", name);
        return 0;
    }
    printf("FAIL: %s\n", name);
    return 1;
}

/**
 * @brief Runs the set checks and checks that the input sets are unchanged.
 * @return EXIT_SUCCESS if no checks fail, otherwise EXIT_FAILURE.
 */
int main(void)
{
    const int a[] = {1, 2, 3};
    const int b[] = {1, 3, 5};
    const int common[] = {1, 3};
    const int combined[] = {1, 2, 3, 5};
    const int difference[] = {2};
    const int reverseDifference[] = {5};
    const int disjoint[] = {7, 8};
    const int disjointUnion[] = {1, 2, 3, 7, 8};
    const int negatives[] = {-3, -1, 2};
    const int negativesOther[] = {-1, 0, 2};
    const int negativesCommon[] = {-1, 2};
    const int negativesUnion[] = {-3, -1, 0, 2};
    const int negativesDifference[] = {-3};
    const int extremes[] = {INT_MIN, 0, INT_MAX};
    const int extremesOther[] = {INT_MIN, INT_MAX};
    const int zero[] = {0};
    const int overlapFirst[] = {0, 1, 2, 3, 4, 5};
    const int overlapSecond[] = {1, 2, 3, 4, 5, 6};
    const int overlapUnion[] = {0, 1, 2, 3, 4, 5, 6};

    OrderedIntSet *sets[10];
    sets[0] = makeSet(a, 3);
    sets[1] = makeSet(b, 3);
    sets[2] = makeSet(NULL, 0);
    sets[3] = makeSet(disjoint, 2);
    sets[4] = makeSet(negatives, 3);
    sets[5] = makeSet(negativesOther, 3);
    sets[6] = makeSet(extremes, 3);
    sets[7] = makeSet(extremesOther, 2);
    sets[8] = makeSet(overlapFirst, 6);
    sets[9] = makeSet(overlapSecond, 6);

    for (int i = 0; i < 10; i++) {
        if (sets[i] == NULL) {
            printf("Could not create test sets.\n");
            for (int j = 0; j < 10; j++) {
                deleteOrderedSet(sets[j]);
            }
            return EXIT_FAILURE;
        }
    }
    ListNode *positions[10];
    for (int i = 0; i < 10; i++) {
        positions[i] = sets[i]->list->current;
    }
    int failures = 0;

    failures += checkResult("intersection: overlap", setIntersection(sets[0], sets[1]), common, 2);
    failures += checkResult("union: overlap", setUnion(sets[0], sets[1]), combined, 4);
    failures += checkResult("difference: overlap", setDifference(sets[0], sets[1]), difference, 1);
    failures += checkResult("difference: reverse order", setDifference(sets[1], sets[0]), reverseDifference, 1);
    failures += checkResult("intersection: equal", setIntersection(sets[0], sets[0]), a, 3);
    failures += checkResult("union: equal", setUnion(sets[0], sets[0]), a, 3);
    failures += checkResult("difference: equal", setDifference(sets[0], sets[0]), NULL, 0);
    failures += checkResult("intersection: disjoint", setIntersection(sets[0], sets[3]), NULL, 0);
    failures += checkResult("union: disjoint", setUnion(sets[0], sets[3]), disjointUnion, 5);
    failures += checkResult("difference: disjoint", setDifference(sets[0], sets[3]), a, 3);
    failures += checkResult("intersection: first empty", setIntersection(sets[2], sets[0]), NULL, 0);
    failures += checkResult("union: first empty", setUnion(sets[2], sets[0]), a, 3);
    failures += checkResult("difference: first empty", setDifference(sets[2], sets[0]), NULL, 0);
    failures += checkResult("intersection: second empty", setIntersection(sets[0], sets[2]), NULL, 0);
    failures += checkResult("union: second empty", setUnion(sets[0], sets[2]), a, 3);
    failures += checkResult("difference: second empty", setDifference(sets[0], sets[2]), a, 3);
    failures += checkResult("intersection: both empty", setIntersection(sets[2], sets[2]), NULL, 0);
    failures += checkResult("union: both empty", setUnion(sets[2], sets[2]), NULL, 0);
    failures += checkResult("difference: both empty", setDifference(sets[2], sets[2]), NULL, 0);
    failures += checkResult("intersection: negatives", setIntersection(sets[4], sets[5]), negativesCommon, 2);
    failures += checkResult("union: negatives", setUnion(sets[4], sets[5]), negativesUnion, 4);
    failures += checkResult("difference: negatives", setDifference(sets[4], sets[5]), negativesDifference, 1);
    failures += checkResult("intersection: integer limits", setIntersection(sets[6], sets[7]), extremesOther, 2);
    failures += checkResult("union: integer limits", setUnion(sets[6], sets[7]), extremes, 3);
    failures += checkResult("difference: integer limits", setDifference(sets[6], sets[7]), zero, 1);
    failures += checkResult("union: many shared values", setUnion(sets[8], sets[9]), overlapUnion, 7);

    if (!matches(sets[0], a, 3) || !matches(sets[1], b, 3)
        || !matches(sets[2], NULL, 0) || !matches(sets[3], disjoint, 2)
        || !matches(sets[4], negatives, 3) || !matches(sets[5], negativesOther, 3)
        || !matches(sets[6], extremes, 3) || !matches(sets[7], extremesOther, 2)
        || !matches(sets[8], overlapFirst, 6) || !matches(sets[9], overlapSecond, 6)) {
        printf("FAIL: input sets changed\n");
        failures++;
    }
    for (int i = 0; i < 10; i++) {
        if (sets[i]->list->current != positions[i]) {
            printf("FAIL: current position changed in set %d\n", i);
            failures++;
        }
    }

    /* Keep results while deleting the inputs to check that they own their data. */
    OrderedIntSet *intersection = setIntersection(sets[0], sets[1]);
    OrderedIntSet *setUnionResult = setUnion(sets[0], sets[1]);
    OrderedIntSet *setDifferenceResult = setDifference(sets[0], sets[1]);
    for (int i = 0; i < 10; i++) {
        deleteOrderedSet(sets[i]);
    }
    failures += checkResult("intersection: independent result", intersection, common, 2);
    failures += checkResult("union: independent result", setUnionResult, combined, 4);
    failures += checkResult("difference: independent result", setDifferenceResult, difference, 1);

    printf("Failed checks: %d\n", failures);
    if (failures == 0) {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
