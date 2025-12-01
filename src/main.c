/*

-- project: Component 2
-- file: main.c
-- created: 28/11/25
-- updated: 30/11/25

Initialises the program.

*/

// Include the menu header file
#include <stdio.h>
#include "codes.h"
#include "menu.h"
#include "data.h"

// The entry point of the program.
// No parameters used.
int main(int argc, char** argv) {

    // default file path if none provided
    char* path = "stock_items.txt";

    // check argument count
    if (argc == 2) {
        path = argv[1];
    } else if (argc > 2) { // too many arguments, usage error
        printf("usage: exec [file path]\n");
        return EXIT_USAGE_ERROR;
    }

    printf("Stock Control Program Started -");

    ItemArray* items = get_items(path);
    // check if read or parse failed
    // error messages should already have been printed from get_items
    if (items == NULL) {
        return EXIT_DATA_ERROR;
    }

    // Initial file output to check if read okay
    for (int i = 0; i < items->count; i++) {
        Item* item = items->array[i];
        printf("%d %s %d\n", item->id, item->name, item->stock);
    }

    printf("Total products loaded : %d\n\n", items->count);

    // Boot up the main menu loop
    init_mainmenu(path, items);

    // Exit 0: success
    // Unlikely for the program to reach this, as "quit" menu option manually exits
    return EXIT_SUCCESS;
}