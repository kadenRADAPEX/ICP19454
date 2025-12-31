/*

-- project: Component 2
-- file: menu.h
-- created: 28/11/25
-- updated: 30/11/25

Generates reports from ItemArray and outputs them to file stream or stdout stream

*/
#include <stdio.h>
#include <stdlib.h>
#include "report.h"
#include "data.h"

// Simple bubble sort implementation
// note:
//     I opted to create a second array so that when saving the modified products,
//     the order *should* be consistent to what was originally loaded from the file.
//     Also note that this is actually sorting the pointers, not the Items themselves
ItemArray* bubble_sort(ItemArray* unsorted) {
    int length = unsorted->count;

    // allocate a second Item array that will be sorted
    Item** u_array = unsorted->array;
    Item** s_array = (Item**)malloc(sizeof(Item*) * length);

    // initialize s_array to copy u_array
    for (int i = 0; i < length; i++) {
        s_array[i] = u_array[i];
    }

    // bubble sort logic
    int swapped = 0;
    do {
        swapped = 0;

        // compare item pairs in turn
        for (int i = 0; i < length - 1; i++) {
            Item* a = s_array[i];
            Item* b = s_array[i+1];
            // If a's stock greater than b's stock, swap
            if (a->stock > b->stock) {
                // set swap flag to true
                swapped = 1;
                s_array[i] = b;
                s_array[i+1] = a;
            }
        }

        // repeat until pass completed without swapping
    } while (swapped);

    // return a new ItemArray object
    ItemArray* sorted = (ItemArray*)malloc(sizeof(ItemArray));
    sorted->array = s_array;
    sorted->count = length;
    return sorted;
}

// Report generation and output logic
void init_reportmenu(ItemArray* items) {
    printf("Please enter file path to save report to : ");

    // input file path into string buffer
    int length = 0;
    char* path = input_s(&length);
    
    // check if input was blank, if so use stdout
    // otherwise attempt to open file
    FILE* fptr;
    if (length == 0) {
        fptr = stdout;
    } else {
        fptr = fopen(path, "w");
        // note:
        //     since we're in write mode, non-existant files should be created, however we still check for errors
        if (fptr == NULL) {
            printf("Could not open file at \"%s\".\n", path);
            return;
        }
    }

    printf("Should the report be sorted by stock (ascending)? ");

    int yes = input_yn();

    if (yes) items = bubble_sort(items);

    // output header of table
    fprintf(
        fptr,
        "------------------------------------------------------------------------\n"
        "ID     | Name                                           | Stock Level   \n"
        "------------------------------------------------------------------------\n"
    );

    // output each item on its own line
    for (int i = 0; i < items->count; i++) {
        Item* item = items->array[i];
        // uses spacing formats e.g. %-7d means int in a 7-character space
        fprintf(fptr, "%-7d| %-47s| %-15d\n", item->id, item->name, item->stock);
    }

    // output closing line of table
    fprintf(
        fptr,
        "------------------------------------------------------------------------\n"
    );

    // if not using stdout, close and save file
    if (length != 0) fclose(fptr);
}