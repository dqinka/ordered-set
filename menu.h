/**
 * @file menu.h
 * @brief Menu-driven test program: constants, input helpers and the
 *        handler for each menu option.
 *
 * All input (menu choices, indices and numbers) is read from the text file
 * INPUT_FILE_NAME, which is passed around as a FILE pointer. There are no
 * global variables: SetsArray lives in main() and is passed to every
 * function that needs it.
 *
 * @author Brian Redmond (skeleton, menu loop, input helpers, option 10)
 */

#ifndef MENU_H
#define MENU_H

#include <stdbool.h>
#include <stdio.h>
#include "orderedIntSet.h"

/** Number of slots in SetsArray (valid indices are 0 to NUM_SETS - 1). */
#define NUM_SETS 10

/** Input file, opened without a path so it is found next to the executable. */
#define INPUT_FILE_NAME "textInput.txt"

/** Binary file for options 5 and 6, opened without a path. */
#define BINARY_FILE_NAME "SetsArrayFile.bin"

/**
 * Set to 1 to print the menu text before each choice is read. Person 2
 * should set this to match the lecturer's expected output.
 */
#define PRINT_MENU 0

/**
 * @brief Menu option numbers, as listed in section 4 of the brief.
 */
typedef enum
{
    MENU_CREATE_SET     = 1,  /**< Create an empty ordered set.  */
    MENU_DELETE_SET     = 2,  /**< Delete an ordered set.        */
    MENU_ADD_ELEMENTS   = 3,  /**< Add elements to a set.        */
    MENU_REMOVE_ELEMENTS = 4, /**< Remove elements from a set.   */
    MENU_SAVE           = 5,  /**< Save SetsArray to binary file. */
    MENU_LOAD           = 6,  /**< Load SetsArray from binary file. */
    MENU_INTERSECTION   = 7,  /**< Set intersection.             */
    MENU_UNION          = 8,  /**< Set union.                    */
    MENU_DIFFERENCE     = 9,  /**< Set difference.               */
    MENU_TERMINATE      = 10  /**< Terminate the program.        */
} MenuOption;

/* ------------------------------------------------------------------------ */
/* Program skeleton (Brian)                                                 */
/* ------------------------------------------------------------------------ */

/**
 * @brief Runs the menu loop until option 10 or the end of the input file.
 *
 * Reads a menu choice, calls the matching handler, then prints the extra
 * blank line required after each menu choice.
 *
 * @param setsArray Array of NUM_SETS set pointers (NULL = empty slot).
 * @param input     Open input file.
 */
void runMenu(OrderedIntSet *setsArray[], FILE *input);

/**
 * @brief Prints the list of menu options to stdout.
 */
void printMenu(void);

/**
 * @brief Reads one integer from the input file.
 *
 * @param input Open input file.
 * @param value Receives the integer that was read.
 * @return true if an integer was read, false at end of file or on
 *         non-numeric input.
 */
bool readInt(FILE *input, int *value);

/**
 * @brief Checks whether @p index is a valid SetsArray index (0 to 9).
 * @param index Index to check.
 * @return true if valid, false otherwise.
 */
bool isValidIndex(int index);

/**
 * @brief Reads a SetsArray index from the input file and validates it.
 *
 * Prints an error message if the index cannot be read or is out of range.
 * The value is always consumed from the file, so input stays in step even
 * when the index is invalid.
 *
 * @param input Open input file.
 * @param index Receives the index that was read.
 * @return true if a valid index (0 to 9) was read, false otherwise.
 */
bool readIndex(FILE *input, int *index);

/**
 * @brief Deletes every set in SetsArray and sets each slot to NULL.
 * @param setsArray Array of NUM_SETS set pointers.
 */
void deleteAllSets(OrderedIntSet *setsArray[]);

/* ------------------------------------------------------------------------ */
/* Menu option handlers (one per option)                                    */
/* ------------------------------------------------------------------------ */

/** @brief Option 1: create an empty set at the index read from @p input (Person 2). */
void menuCreateSet(OrderedIntSet *setsArray[], FILE *input);

/** @brief Option 2: delete the set at the index read from @p input (Person 2). */
void menuDeleteSet(OrderedIntSet *setsArray[], FILE *input);

/** @brief Option 3: add numbers until a negative one, then print the set (Person 4). */
void menuAddElements(OrderedIntSet *setsArray[], FILE *input);

/** @brief Option 4: remove numbers until a negative one, then print the set (Person 4). */
void menuRemoveElements(OrderedIntSet *setsArray[], FILE *input);

/** @brief Option 5: save the whole SetsArray to BINARY_FILE_NAME (Person 3). */
void menuSaveSets(OrderedIntSet *setsArray[]);

/** @brief Option 6: load the whole SetsArray from BINARY_FILE_NAME (Person 3). */
void menuLoadSets(OrderedIntSet *setsArray[]);

/** @brief Option 7: intersection of i1 and i2 stored at i3, then printed (Person 5). */
void menuIntersection(OrderedIntSet *setsArray[], FILE *input);

/** @brief Option 8: union of i1 and i2 stored at i3, then printed (Person 5). */
void menuUnion(OrderedIntSet *setsArray[], FILE *input);

/** @brief Option 9: difference i1 - i2 stored at i3, then printed (Person 5). */
void menuDifference(OrderedIntSet *setsArray[], FILE *input);

#endif /* MENU_H */
