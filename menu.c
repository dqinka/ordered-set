/**
 * @file menu.c
 * @brief Menu loop, input helpers and menu option handlers.
 *
 * Menu choices and their values are read from the same input file.
 *

 * @author Brian Redmond (skeleton, menu loop, input helpers, option 10)
 * @author Diana Sholomko (options 5 and 6)
 * @author Jamila Mohamed (options 1 and 2: create and delete ordered sets)
 * @author Jack Dillon (options 3 and 4: add and remove elements)
 * @author Shayan Khan (options 7, 8 and 9)
 */

#include <stdio.h>
#include "menu.h"

/* ------------------------------------------------------------------------ */
/* Menu loop and input helpers                                               */
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
/* Menu option handlers                                                  */
/* ------------------------------------------------------------------------ */

/**
 * @brief Consumes unused values up to and including the negative sentinel.
 *
 * Used when an index is invalid or when no set exists in the requested slot.
 * This keeps the next menu option aligned with the input file.
 * @param input Open input file.
 */
static void skipUntilNegative(FILE *input)
{
    int value;
    while (readInt(input, &value) && value >= 0)
    {
        /* discard values for the missing/invalid set */
    }
}


/**
 * @brief Creates an empty ordered set at the selected index.
 * @param setsArray Array of ordered set pointers.
 * @param input Input file containing the index.
 */
void menuCreateSet(OrderedIntSet *setsArray[], FILE *input)
{
    int index;

    // Read and validate the index (0 to 9).

    printf("Please enter index (0 - 9) for set to be created:\n");
    if (!readIndex(input, &index))
    {
        return;
    }

    // Check if a set already exists at this index.
    if (setsArray[index] != NULL)
    {
        printf("Error: set already exists at index %d.\n", index);
        return;
    }

    // Create a new empty ordered set.
    setsArray[index] = createOrderedSet();

    // Check if memory allocation failed.
    if (setsArray[index] == NULL)
    {
        printf("Error: could not create set at index %d.\n", index);
        return;
    }

    printf("Set at index %d created\n", index);
}


/**
 * @brief Deletes an ordered set at the selected index.
 * @param setsArray Array of ordered set pointers.
 * @param input Input file containing the set index.
 */
void menuDeleteSet(OrderedIntSet *setsArray[], FILE *input)
{
    int index;

    // Read and validate the index (0 to 9).

    printf("Please enter index (0 - 9) for set to be deleted:\n");

    if (!readIndex(input, &index))
    {
        return;
    }

    // Check if the set exists.
    if (setsArray[index] == NULL)
    {
        printf("Error: no set exists at index %d.\n", index);
        return;
    }

    // Delete the selected ordered set.
    deleteOrderedSet(setsArray[index]);

    // Clear the pointer to avoid using deleted memory.
    setsArray[index] = NULL;

    printf("Set at index %d deleted\n", index);
}

/**
 * @brief Runs option 3 or 4 using the selected ordered set.
 *
 * Every non-negative value is passed to addElement or removeElement.
 * A negative value ends this option. No matter what happens, the input
 * values are consumed up to the sentinel before returning to the menu.
 *
 * @param setsArray The ten set slots.
 * @param input Input file to read the index and integers from.
 * @param adding true for option 3, false for option 4.
 */
static void menuChangeElements(OrderedIntSet *setsArray[], FILE *input, bool adding)
{
    int index;
    int value;

    if (adding)
    {
        printf("Please enter index (0 - 9) for set to add elements:\n");
    }
    else
    {
        printf("Please enter index (0 - 9) for set to remove elements:\n");
    }

    if (!readIndex(input, &index))
    {
        /* Even a bad index may be followed by values and the sentinel. */
        skipUntilNegative(input);
        return;
    }

    if (setsArray[index] == NULL)
    {
        printf("Error: no set exists at index %d.\n", index);
        skipUntilNegative(input);
        return;
    }

    while (readInt(input, &value) && value >= 0)
    {
        SetResult result = adding ? addElement(setsArray[index], value)
                                  : removeElement(setsArray[index], value);

        switch (result)
        {
        case NUMBER_ADDED:
            printf("%d: NUMBER_ADDED\n", value);
            break;
        case NUMBER_ALREADY_IN_SET:
            printf("%d: NUMBER_ALREADY_IN_SET\n", value);
            break;
        case NUMBER_REMOVED:
            printf("%d: NUMBER_REMOVED\n", value);
            break;
        case NUMBER_NOT_IN_SET:
            printf("%d: NUMBER_NOT_IN_SET\n", value);
            break;
        case ALLOCATION_ERROR:
            printf("%d: ALLOCATION_ERROR\n", value);
            break;
        }
    }

    printToStdout(setsArray[index]);
    printf("\n");
}

/**
 * @brief Menu option 3: inserts values until the negative sentinel.
 * @param setsArray The set pointers to update.
 * @param input Open text input file.
 */
void menuAddElements(OrderedIntSet *setsArray[], FILE *input)
{
    menuChangeElements(setsArray, input, true);
}

/**
 * @brief Menu option 4: removes values until the negative sentinel.
 * @param setsArray The set pointers to update.
 * @param input Open text input file.
 */
void menuRemoveElements(OrderedIntSet *setsArray[], FILE *input)
{
    menuChangeElements(setsArray, input, false);
}

/**
 * @brief Writes one int to a binary file.
 * @param file  Binary file open for writing.
 * @param value Value to write.
 * @return true if the value was written, false otherwise.
 */
static bool writeBinaryInt(FILE *file, int value)
{
    return fwrite(&value, sizeof value, 1, file) == 1;
}

/**
 * @brief Reads one int from a binary file.
 * @param file  Binary file open for reading.
 * @param value Receives the int that was read.
 * @return true if a value was read, false at end of file or on error.
 */
static bool readBinaryInt(FILE *file, int *value)
{
    return fread(value, sizeof *value, 1, file) == 1;
}

/* Option 5: file layout and error handling are described in menu.h */
void menuSaveSets(OrderedIntSet *setsArray[])
{
    FILE *file = fopen(BINARY_FILE_NAME, "wb");   /* no path */
    bool ok = true;

    if (file == NULL)
    {
        printf("Error: could not open %s for writing.\n", BINARY_FILE_NAME);
        return;
    }

    for (int i = 0; i < NUM_SETS && ok; i++)
    {
        bool present = (setsArray[i] != NULL);
        ok = writeBinaryInt(file, present ? 1 : 0);

        if (ok && present)
        {
            DoubleLinkedList *list = setsArray[i]->list;
            ok = writeBinaryInt(file, setsArray[i]->count);

            /* walk through the real elements, from first to last */
            gotoHead(list);
            gotoNextNode(list);
            while (ok && !isAtTail(list))
            {
                ok = writeBinaryInt(file, getData(list));
                gotoNextNode(list);
            }
        }
    }

    if (fclose(file) != 0)
    {
        ok = false;
    }

    if (!ok)
    {
        printf("Error: writing to %s failed.\n", BINARY_FILE_NAME);
    }
}

/* Option 6: file layout and error handling are described in menu.h */
void menuLoadSets(OrderedIntSet *setsArray[])
{
    OrderedIntSet *loaded[NUM_SETS] = { NULL };   /* temporary array */
    bool ok = true;

    FILE *file = fopen(BINARY_FILE_NAME, "rb");   /* no path */
    if (file == NULL)
    {
        printf("Error: could not open %s for reading.\n", BINARY_FILE_NAME);
        return;
    }

    for (int i = 0; i < NUM_SETS && ok; i++)
    {
        int present = 0;
        ok = readBinaryInt(file, &present) && (present == 0 || present == 1);

        if (ok && present == 1)
        {
            int count = 0;

            loaded[i] = createOrderedSet();
            ok = (loaded[i] != NULL) &&
                 readBinaryInt(file, &count) && count >= 0;

            for (int j = 0; ok && j < count; j++)
            {
                int value = 0;
                ok = readBinaryInt(file, &value) &&
                     addElement(loaded[i], value) != ALLOCATION_ERROR;
            }
        }
    }

    fclose(file);

    if (!ok)
    {
        /* bad or incomplete file: discard what was read, keep the old sets */
        deleteAllSets(loaded);
        printf("Error: could not read %s correctly.\n", BINARY_FILE_NAME);
        return;
    }

    /* success: replace the existing sets with the loaded ones */
    deleteAllSets(setsArray);
    for (int i = 0; i < NUM_SETS; i++)
    {
        setsArray[i] = loaded[i];
    }
}

/**
 * @brief Reads indices and stores the result for menu option 7, 8 or 9.
 * @param setsArray Array of NUM_SETS set pointers.
 * @param input Shared input file.
 * @param operation MENU_INTERSECTION, MENU_UNION or MENU_DIFFERENCE.
 */
static void menuSetOperation(OrderedIntSet *setsArray[], FILE *input, MenuOption operation)
{
    const char *name;
    const char *label;
    if (operation == MENU_INTERSECTION) {
        name = "intersection";
        label = "Intersection";
    } else if (operation == MENU_UNION) {
        name = "union";
        label = "Union";
    } else {
        name = "difference";
        label = "Difference";
    }

    printf("Your choice: %d\n", operation);
    printf("Please enter three indices: two for sets to form %s of and one for the target set:\n",
           name);

    int i1, i2, i3;
    /* Read all three before acting, including when an earlier one is invalid. */
    bool ok1 = readIndex(input, &i1);
    bool ok2 = readIndex(input, &i2);
    bool ok3 = readIndex(input, &i3);
    if (!ok1 || !ok2 || !ok3) {
        return;
    }

    if (setsArray[i1] == NULL || setsArray[i2] == NULL) {
        if (setsArray[i1] == NULL) {
            printf("No ordered set available at index %d. ", i1);
        }
        if (setsArray[i2] == NULL) {
            printf("No ordered set available at index %d. ", i2);
        }
        printf("Cannot perform set %s.\n", name);
        return;
    }

    /* The destination may also be an input, so calculate the result first. */
    OrderedIntSet *result;
    if (operation == MENU_INTERSECTION) {
        result = setIntersection(setsArray[i1], setsArray[i2]);
    } else if (operation == MENU_UNION) {
        result = setUnion(setsArray[i1], setsArray[i2]);
    } else {
        result = setDifference(setsArray[i1], setsArray[i2]);
    }

    if (result == NULL) {
        printf("Cannot perform set %s: memory allocation failed.\n", name);
        return;
    }

    if (setsArray[i3] != NULL) {
        deleteOrderedSet(setsArray[i3]);
    }
    setsArray[i3] = result;
    printf("Set %s = ", label);
    printToStdout(result);
    printf("\n");
    /* runMenu prints the extra blank line after the choice. */
}

void menuIntersection(OrderedIntSet *setsArray[], FILE *input)
{
    menuSetOperation(setsArray, input, MENU_INTERSECTION);
}

void menuUnion(OrderedIntSet *setsArray[], FILE *input)
{
    menuSetOperation(setsArray, input, MENU_UNION);
}

void menuDifference(OrderedIntSet *setsArray[], FILE *input)
{
    menuSetOperation(setsArray, input, MENU_DIFFERENCE);
}
