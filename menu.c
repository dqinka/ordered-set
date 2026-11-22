/**
 * @file menu.c
 * @brief Menu loop, input helpers and menu option handlers.
 *
 * The handlers for options 1 to 9 are placeholders. Each one already reads
 * the right number of values from the input file, so the skeleton stays in
 * step with textInput.txt while the real code is being written. Replace the
 * body of your handler, but keep reading all of its values even when an
 * index is invalid, or the next numbers will be read as menu choices.
 *
 * @author Brian Redmond (skeleton, menu loop, input helpers, option 10)
 */

#include <stdio.h>
#include "menu.h"

/* ------------------------------------------------------------------------ */
/* Program skeleton (Brian)                                                 */
/* ------------------------------------------------------------------------ */

void runMenu(OrderedIntSet *setsArray[], FILE *input)
{
    bool running = true;

    while (running)
    {
        int choice;

        if (PRINT_MENU)
        {
            printMenu();
        }

        if (!readInt(input, &choice))
        {
            /* end of input file reached without option 10 */
            break;
        }

        switch (choice)
        {
        case MENU_CREATE_SET:
            menuCreateSet(setsArray, input);
            break;
        case MENU_DELETE_SET:
            menuDeleteSet(setsArray, input);
            break;
        case MENU_ADD_ELEMENTS:
            menuAddElements(setsArray, input);
            break;
        case MENU_REMOVE_ELEMENTS:
            menuRemoveElements(setsArray, input);
            break;
        case MENU_SAVE:
            menuSaveSets(setsArray);
            break;
        case MENU_LOAD:
            menuLoadSets(setsArray);
            break;
        case MENU_INTERSECTION:
            menuIntersection(setsArray, input);
            break;
        case MENU_UNION:
            menuUnion(setsArray, input);
            break;
        case MENU_DIFFERENCE:
            menuDifference(setsArray, input);
            break;
        case MENU_TERMINATE:
            running = false;
            break;
        default:
            printf("Error: invalid menu option %d.\n", choice);
            break;
        }

        /* the brief requires an extra blank line after each menu choice */
        printf("\n");
    }
}

void printMenu(void)
{
    printf("1. Create an empty Ordered Set\n");
    printf("2. Delete an Ordered Set\n");
    printf("3. Add Elements to Ordered Set\n");
    printf("4. Remove Elements from Ordered Set\n");
    printf("5. Store SetsArray to binary file\n");
    printf("6. Load SetsArray from binary file\n");
    printf("7. Set Intersection\n");
    printf("8. Set Union\n");
    printf("9. Set Difference\n");
    printf("10. Terminate the program\n");
    printf("Enter option: ");
}

bool readInt(FILE *input, int *value)
{
    int result = fscanf(input, "%d", value);

    if (result == 1)
    {
        return true;
    }
    if (result == 0)
    {
        /* something other than a number: stop rather than loop forever */
        fprintf(stderr, "Error: non-numeric input in %s.\n", INPUT_FILE_NAME);
    }
    return false; /* EOF or bad input */
}

bool isValidIndex(int index)
{
    return index >= 0 && index < NUM_SETS;
}

bool readIndex(FILE *input, int *index)
{
    if (!readInt(input, index))
    {
        printf("Error: could not read set index.\n");
        return false;
    }
    if (!isValidIndex(*index))
    {
        printf("Error: index %d is out of range (0 to %d).\n",
               *index, NUM_SETS - 1);
        return false;
    }
    return true;
}

void deleteAllSets(OrderedIntSet *setsArray[])
{
    for (int i = 0; i < NUM_SETS; i++)
    {
        if (setsArray[i] != NULL)
        {
            deleteOrderedSet(setsArray[i]);
            setsArray[i] = NULL;
        }
    }
}

/* ------------------------------------------------------------------------ */
/* Menu option handlers: placeholders that only consume their input         */
/* ------------------------------------------------------------------------ */

/**
 * @brief Reads numbers until a negative one (placeholder helper for 3 and 4).
 * @param input Open input file.
 */
static void skipUntilNegative(FILE *input)
{
    int value;
    while (readInt(input, &value) && value >= 0)
    {
        /* discard */
    }
}

void menuCreateSet(OrderedIntSet *setsArray[], FILE *input)
{
    int index;
    (void)setsArray;
    (void)readIndex(input, &index);
    /* TODO Person 2 */
}

void menuDeleteSet(OrderedIntSet *setsArray[], FILE *input)
{
    int index;
    (void)setsArray;
    (void)readIndex(input, &index);
    /* TODO Person 2 */
}

void menuAddElements(OrderedIntSet *setsArray[], FILE *input)
{
    int index;
    (void)setsArray;
    (void)readIndex(input, &index);
    skipUntilNegative(input);
    /* TODO Person 4 */
}

void menuRemoveElements(OrderedIntSet *setsArray[], FILE *input)
{
    int index;
    (void)setsArray;
    (void)readIndex(input, &index);
    skipUntilNegative(input);
    /* TODO Person 4 */
}

void menuSaveSets(OrderedIntSet *setsArray[])
{
    (void)setsArray;
    /* TODO Person 3: write to BINARY_FILE_NAME */
}

void menuLoadSets(OrderedIntSet *setsArray[])
{
    (void)setsArray;
    /* TODO Person 3: read from BINARY_FILE_NAME (delete existing sets first) */
}

void menuIntersection(OrderedIntSet *setsArray[], FILE *input)
{
    int i1, i2, i3;
    (void)setsArray;
    /* read all three before validating, so input stays in step */
    bool ok1 = readIndex(input, &i1);
    bool ok2 = readIndex(input, &i2);
    bool ok3 = readIndex(input, &i3);
    (void)ok1; (void)ok2; (void)ok3;
    /* TODO Person 5 */
}

void menuUnion(OrderedIntSet *setsArray[], FILE *input)
{
    int i1, i2, i3;
    (void)setsArray;
    bool ok1 = readIndex(input, &i1);
    bool ok2 = readIndex(input, &i2);
    bool ok3 = readIndex(input, &i3);
    (void)ok1; (void)ok2; (void)ok3;
    /* TODO Person 5 */
}

void menuDifference(OrderedIntSet *setsArray[], FILE *input)
{
    int i1, i2, i3;
    (void)setsArray;
    bool ok1 = readIndex(input, &i1);
    bool ok2 = readIndex(input, &i2);
    bool ok3 = readIndex(input, &i3);
    (void)ok1; (void)ok2; (void)ok3;
    /* TODO Person 5: i1 - i2, not i2 - i1 */
}
