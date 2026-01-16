/*

-- project: Component 2
-- file: manage.c
-- created: 28/11/25

Displays menu for managing stock levels. Allows user to input product id and stock adjustment.

*/
#include <stdio.h>
#include "manage.h"
#include "data.h"

// Main logic function, requires loaded items from data.h :: get_items
void init_managemenu(ItemArray* items) {
    // id of the product to manage
    int id = -1;
    while (1) {
        printf("Please Enter a Unique Product Number : ");

        // input a number and check if it is a valid integer (including sign)
        if (!input_i(&id)) {
            printf("Malformed integer.\n\n");
            continue;
        }

        // check if input is within bounds of stock items array
        if (id >= 0 && id < items->count) {
            break;
        }
        printf("A product with that number does not exist.\n\n");
    }

    // get pointer to the item to manage
    Item* item = items->array[id];

    // operation to perform on item (plus or minus)
    int op = 0;
    while (1) {
        printf("Please Enter a stock level adjustment value : ");

        // input a number and check if it is a valid integer (including sign)
        if (!input_i(&op)) {
            printf("Malformed integer.\n\n");
            continue;
        }

        // check if new stock would be below 0
        // cast is required because stock is stored as unsigned int
        if ((int)item->stock + op >= 0) {
            break;
        }
        printf("There is insufficient stock to allow that.\n\n");
    }

    // apply operation to item
    item->stock += op;
    // output change
    printf("Stock level update as follows -\n%s\n%d (%+d applied)\n", item->name, item->stock, op);
}