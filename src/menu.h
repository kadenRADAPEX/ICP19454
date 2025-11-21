/*

-- project: Component 2
-- file: menu.h
-- created: 21/11/25
-- updated: 21/11/25

Header file for main menu

*/

// Include guard statement
#ifndef menu_h
#define menu_h

// Valid menu options stored as enumator
typedef enum {
    MENU_INVALID,
    MENU_MANAGE,
    MENU_REPORT,
    MENU_QUIT,
} MenuOption;

// Main menu init function
void init_mainmenu();

#endif