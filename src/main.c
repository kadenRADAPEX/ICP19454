/*

-- project: Component 2
-- file: main.c
-- created: 21/11/25
-- updated: 21/11/25

Initialises the program.

*/

// Include the menu header file
#include "menu.h"

// The entry point of the program.
// No parameters used.
int main(void) {
    
    // Boot up the main menu loop
    init_mainmenu();

    // Exit 0: success
    // Unlikely for the program to reach this, as "quit" menu option manually exits
    return 0;
}