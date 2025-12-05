/*

-- project: Component 2
-- file: data.c
-- created: 28/11/25
-- updated: 30/11/25

Data loading, parsing, and saving with helper functions for string manipulation

*/
#include <stdio.h>
#include <stdlib.h>
#include "data.h"

// Helper function to check if entire string is composed of digit characters
// note:
//     allows for first character to be arithmetic operator ( + - )
static int is_numeric(char* string) {    
    // while not at the end of the line or the eof
    for (int i = 0; string[i] != '\0' && string[i] != '\n'; i++) {
        char c = string[i];
        // if ASCII code outside range for 0 and 9, it is not a digit
        if (i == 0 && (c > '9' || c < '0') && c != '+' && c != '-') return 0;
        if (i != 0 && (c > '9' || c < '0')) return 0;
    }

    return 1;
}

// Helper function to check if entire line is empty
static int is_empty_line(char* line, ssize_t length) {
    // if length < 0, the line wasn't read
    // in get_items, this is already checked but may not always be the case since ssize_t is signed
    if (length <= 0) return 1;
    for (size_t i = 0; i < (size_t)length; i++) {
        char c = line[i];
        // doesnt match whitespace characters (space, horizontal tab, vertical tab, new line, form feed, carriage return)
        if (c != ' ' && c != '\t' && c != '\v' && c != '\n' && c != '\f' && c != '\r') return 0;
    }
    // reached loop end without finding any non-whitespace characters, line is empty
    return 1;
}

// Input a string
// removes the new line from end of input
char* input_s(int* length) {
    char* buffer = (char*)malloc(sizeof(char) * 65);
    fgets(buffer, 65, stdin);

    // loop through characters
    for (int i = 0;;i++) {
        char c = buffer[i];

        // found end of string
        if (c == '\0') {
            *length = i;
            break;
        }

        // found new line, terminate string here
        if (c == '\n') {
            *length = i;
            buffer[i] = '\0';
            break;
        }
    }
    return buffer;
}

// Input yes or no
// returns 1 for yes or 0 for no
int input_yn() {
    while (1) {
        printf("[y/n] ");
        int length;
        char* buffer = input_s(&length);
        if (length == 1) {
            char c = buffer[0];
            if (c == 'y' || c == 'n') return c == 'y';
        }
        printf("only y or n will be accepted.\n");
    }
}

// Input an integer
// returns success code
int input_i(int* out) {
    // Store user input in a 64 character buffer
    char buffer[64];
    fgets(buffer, 64, stdin);

    // check if input is numeric
    if (!is_numeric(buffer)) return 0;

    // Will return 0 if input is not a number
    *out = atoi(buffer);
    return 1;
}

// Main data parsing function
ItemArray* get_items(char* path) {
    // open the file at [path]
    FILE* fptr = fopen(path, "rb");
    // check if file opened successfully (i.e. if it exists)
    if (fptr == NULL) {
        printf(" stock data file missing : %s\n", path);
        return NULL;
    }

    // output that the file loaded successfully
    printf(" using stock data file : %s\n", path);

    // allocate dynamic array size, initialise with space of 1 item only
    // note:
    //     may be more optimized to initialise with more space, to reduce number of reallocs
    Item** stack = (Item**)malloc(sizeof(Item*));
    int stack_size = 1;

    // macro to exit out of function with error message
    // frees stack pointer to avoid memory leak
    #define err(msg) \
        printf(msg); \
        free(stack); \
        return NULL

    // rotating variable item_name
    // first line read -> item_name is set to line chars
    // second line read -> item_name is used to create item then set back to NULL
    char* item_name = NULL;
    int entry = 0;
    while (1) {
        // should never be more than 1000 entries in file
        if (entry > 1000) { err("Too many entries in file.\n"); }

        // read a single line from the file
        // here, the actual length of the line content is bytes
        /*
            capacity is the "variable that holds the size of the input buffer"
            dgookin (n.d.). The getline() Function | C For Dummies Blog. [online]
            Available at: https://c-for-dummies.com/blog/?p=1112.
        */
        char* line = NULL;
        size_t capacity = 0;
        ssize_t bytes = getline(&line, &capacity, fptr);

        // check for end of file, empty lines, or too many characters
        if (bytes < 1 || line == NULL) break; // Reached end of file / <eof>
        if (is_empty_line(line, bytes)) { err("Empty line in file.\n"); } // Line is empty i.e. only \n character
        if (bytes > 64) { err("Too many characters in line.\n"); } // Line has too many characters

        // if item_name is NULL, we need to parse the item name from this line
        if (item_name == NULL) {
            // this loop removes the trailing \n from the name
            for (size_t i = 0; i < (size_t)bytes; i++) {
                char c = line[i];
                if (c == '\n') {
                    line[i] = '\0';
                    break;
                }
            }
            // assign the item_name variable, will be used next iteration
            item_name = line;
        } else {
            // if item_name is NOT NULL, we need to parse the stock level from this line
            // and then add a new Item to the item stack

            // check if the line is a number, if not then it is invalid
            if (!is_numeric(line)) { err("Invalid stock level.\n"); }

            // increment the entry count
            entry++;

            // parse the item_stock from the line
            int item_stock = atoi(line);
            // cannot have negative stock
            // note:
            //     here, 0 stock is allowed. None of the data files have a stock level of 0
            if (item_stock < 0) { err("Invalid stock level.\n"); }

            // allocate the Item object and initialise its fields
            Item* item = (Item*)malloc(sizeof(Item));
            item->id = entry - 1;
            item->name = item_name;
            item->stock = item_stock;

            // if entry count > stack count, we need to grow the array here
            if (entry > stack_size) {
                stack_size += 5; // increase the size by 5 Items at a time
                stack = (Item**)realloc(stack, sizeof(Item*)*stack_size); // reallocate the stack and update the pointer
            }
            // insert this new item into the stakc
            stack[entry - 1] = item;

            // reset the item_name variable
            // the next iteration will read the next item's name
            item_name = NULL;
        }
    }

    // check if we broke out of loop before finishing item definition
    if (item_name != NULL) {
        // i.e. no matching stock level in the file
        err("No stock level found.\n");
    }

    // undefine the err macro for next call
    #undef err

    // close data file
    // note:
    //     pretty sure fclose will free the file but may not be the case
    fclose(fptr);

    // allocate ItemArray with array and count
    ItemArray* items = (ItemArray*)malloc(sizeof(ItemArray));
    items->array = stack;
    items->count = entry;

    // return ItemArray pointer
    return items;
}

// Saves Items from items array to file located at path
// returns success code
// A lot simpler then the reverse...
// note:
//     does not guarantee that items will be saved in the same order they were read
int save_items(char* path, ItemArray* items) {
    // open file in write mode and check for null
    FILE* fptr = fopen(path, "w");
    if (fptr == NULL) {
        printf("could not write to file \"%s\".\n", path);
        return 0;
    }

    // loop through all items and write them to file
    for (int i = 0; i < items->count; i++) {
        Item* item = items->array[i];
        fprintf(fptr, "%s\n%d\n", item->name, item->stock);
    }

    // close and save file
    fclose(fptr);

    return 1;
}