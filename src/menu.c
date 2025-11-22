/*

-- project: Component 2
-- file: menu.c
-- created: 21/11/25
-- updated: 22/11/25

Main menu logic, handles option display and opens submenus.

*/
#include <stdlib.h>
#include <stdio.h>
#include "menu.h"
#include "codes.h"
#include "manage.h"
#include "report.h"

// Validate user input and map to MenuOption enum
static MenuOption validate_menu_input(int input) {
    // Outside of valid range
    if (input < 1 || input > 3) return MENU_INVALID;

    // Map to options
    switch (input) {
        case 1:     return MENU_MANAGE;
        case 2:     return MENU_REPORT;
        case 3:     return MENU_QUIT;
        // invalid inputs
        default:    return MENU_INVALID;
    }
}

// Open the manage stock levels sub-menu
static void open_manage(ItemArray* items) {
    //printf("\"Manage Stock Levels\" Entered: Allows control of stock levels\n");

    // manage stock levels loop
    init_managemenu(items);
}

// Open the reports sub-menu
static void open_report(ItemArray* items) {
    //printf("\"Generate reports\" Entered: Allows generation of reports\n");

    init_reportmenu(items);
}

// Quit the application
static void quit(char* path, ItemArray* items) {
    printf("\"Quit the program\" Entered: Program terminated\n");

    // save item array changes
    if (save_items(path, items)) {
        // terminate the process with exit code 0 (success)
        exit(EXIT_SUCCESS);
    } else {
        // terminate the process with exit code 102 (data fail)
        exit(EXIT_DATA_ERROR);
    }
}

// Single function to open sub-menu associated with option
static void open_menu(MenuOption option, char* path, ItemArray* items) {
    // note:
    //     may not be necessary to have wrapping functions in menu.c, could call inits directly
    switch (option) {
        case MENU_MANAGE: open_manage(items); break;
        case MENU_REPORT: open_report(items); break;
        case MENU_QUIT: quit(path, items); break;
        case MENU_INVALID: printf("Err: invalid menu option."); break;
    }
}

// Main menu loop logic
void init_mainmenu(char* path, ItemArray* items) {
    // forever loop, only way to exit is by quitting process
    while (1) {        
        MenuOption option = MENU_INVALID;
        while (1) {
            printf("1. Manage Stock Levels\n2. Generate Reports\n3. Quit the Program\n\nPlease enter your selection:\n");
            
            int selection;
            input_i(&selection);
            option = validate_menu_input(selection);

            // check if input was valid menu option
            if (option != MENU_INVALID) {
                break;
            }
            printf("Invalid option.\n\n");
        };

        // open the corresponding sub-menu, pass the loaded item array through
        open_menu(option, path, items);

        // Wait for input then dispose
        printf("Press 'return' to continue");
        char _[2];
        fgets(_, 2, stdin);
        printf("\n");
    }
}