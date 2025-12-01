/*

-- project: Component 2
-- file: menu.h
-- created: 28/11/25
-- updated: 30/11/25

Header file for main menu

*/

// Include guard statement
#ifndef menu_h
#define menu_h

#include "data.h"

// Valid menu options stored as enumator
typedef enum {
    MENU_INVALID,
    MENU_MANAGE,
    MENU_REPORT,
    MENU_QUIT,
} MenuOption;

// Main menu init function
void init_mainmenu(char* path, ItemArray* items);

#endif