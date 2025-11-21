/*

-- project: Component 2
-- file: menu.c
-- created: 21/11/25
-- updated: 21/11/25

Main menu logic, handles option display and opens submenus.

*/

#include <stdlib.h>
#include <stdio.h>
#include "menu.h"

// Input a decimal integer
int input_d() {
    // Store user input in a 50 character buffer
    char buffer[50];
    fgets(buffer, 50, stdin);

    // Will return 0 if input is not a number
    char* _;
    int d = strtod(buffer, &_);
    return d;
}

// Validate user input and map to MenuOption enum
MenuOption validate_menu_input(int input) {
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
void open_manage() {
    printf("\"Manage Stock Levels\" Entered: Allows control of stock levels\n");
}

// Open the reports sub-menu
void open_report() {
    printf("\"Generate reports\" Entered: Allows generation of reports\n");
}

// Quit the application
void quit() {
    printf("\"Quit the program\" Entered: Program terminated\n");

    // Terminate the process with exit code 0 (success)
    exit(0);
}

// Single function to open sub-menu associated with option
void open_menu(MenuOption option) {
    switch (option) {
        case MENU_MANAGE: open_manage(); break;
        case MENU_REPORT: open_report(); break;
        case MENU_QUIT: quit(); break;
        case MENU_INVALID: printf("Err: invalid menu option."); break;
    }
}

// Main menu loop logic
void init_mainmenu() {
    while (1) {        
        MenuOption option = MENU_INVALID;
        do {
            printf("1. Manage Stock Levels\n2. Generate Reports\n3. Quit the Program\n\nPlease enter your selection:\n");
            int selection = input_d();
            option = validate_menu_input(selection);
            if (option == MENU_INVALID) {
                printf("Invalid option.\n\n");
            }
        } while(option == MENU_INVALID);

        open_menu(option);

        printf("Press 'return' to continue");
        input_d();
    }
}