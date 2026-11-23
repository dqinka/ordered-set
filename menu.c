/**
 * @file menu.c
 * @brief Menu loop, input helpers and menu option handlers.
 *
 * The handlers for options 1 to 9 are placeholders. Each one already reads
 * the right number of values from the input file, so the skeleton stays in
 * step with textInput.txt while the real code is being written. Replace the
 * body of your handler, but keep reading all of its values even when an
 * index is invalid, or the next numbers will be read as menu choices.

 * @author Brian Redmond (skeleton, menu loop, input helpers, option 10)
 * @author Diana Sholomko (options 5 and 6)
 * @author Jamila Mohamed (options 1 and 2: create and delete ordered sets)
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
