/*

-- project: Component 2
-- file: data.h
-- created: 28/11/25
-- updated: 30/11/25

Header file for data reader & parser

*/
#ifndef data_h
#define data_h

/*
struct for stock items:
id: unique identifier for each item in a file
name: string name of the item
stock: current stock level of the item
*/
typedef struct {
    unsigned int id;
    const char* name;
    unsigned int stock;
} Item;

/*
struct for arrays of Items:
array: pointer to array of pointers to items
count: number of Items / Item pointers within the array

note:
    only made this to return both the pointer and count together, rather than using out / byRef parameters
    consider alternatives e.g. dedicated array file with functions and support for void* types
*/
typedef struct {
    Item** array;
    int count;
} ItemArray;

// function for opening file and reading data
ItemArray* get_items(char* path);
// function for saving modified items to file
int save_items(char* path, ItemArray* items);

// input functions
char* input_s(int* length);
int input_yn();
int input_i(int* out);

#endif