/**
 * @file main.c
 * @brief Entry point of the CE4703 Assignment 2 ordered set test program.
 *
 * Opens textInput.txt, sets up SetsArray (10 pointers, all NULL), runs the
 * menu loop and frees all remaining sets before exiting.
 *
 * @mainpage CE4703 Assignment 2: Data Type "Ordered Set"
 *
 * An ordered set of integers built on a double linked list, with a
 * menu-driven test program that reads all of its input from textInput.txt.
 *
 * - doubleLinkedList.h: double linked list with head/tail sentinels
 * - orderedIntSet.h: ordered integer set and set operations
 * - menu.h: menu loop and option handlers
 *
 * @author Brian Redmond, Jamila, Diana, Jack, Shayan
 */

#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "orderedIntSet.h"

/**
 * @brief Program entry point.
 * @return EXIT_SUCCESS, or EXIT_FAILURE if textInput.txt cannot be opened.
 */
int main(void)
{
    /* no path, so the file is found in the executable's directory */
    FILE *input = fopen(INPUT_FILE_NAME, "r");
    if (input == NULL)
    {
        fprintf(stderr, "Error: could not open %s.\n", INPUT_FILE_NAME);
        return EXIT_FAILURE;
    }

    /* SetsArray is local (no global variables); NULL marks an empty slot */
    OrderedIntSet *setsArray[NUM_SETS];
    for (int i = 0; i < NUM_SETS; i++)
    {
        setsArray[i] = NULL;
    }

    runMenu(setsArray, input);

    /* free any sets still in use, whether we ended on option 10 or EOF */
    deleteAllSets(setsArray);
    fclose(input);

    return EXIT_SUCCESS;
}
