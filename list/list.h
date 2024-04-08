#ifndef LIST
#define LIST

#include <stdio.h>            // ERROR +
#include <stdlib.h>
#include <assert.h>
#include <cstring>

const int POISON = 5674;
const int FREE_INDEX = -1;
const int REALLOC_CONST = 2;
const int FIRST_FREE_ELEM = 1;

typedef int elem_t;

/*
 * Struct list ....
 * Data structure scheme:
 * [null (poison) element] - [first free element] -
 * 0                         1
 *
 */

struct Node_t {
    elem_t *code = 0;
    int    *next = 0;
    int    *prev = 0;
};

struct List_t {
    elem_t *code = 0;
    int    *next = 0;
    int    *prev = 0;
    // Node_t *nodes;
    int     free = 0;
    int     size = 0;
    int capacity = 0;
    int     tail = FIRST_FREE_ELEM; /* first non poison element */
    int     head = FIRST_FREE_ELEM;
};

enum ListError_t {
    OK        = 0,
    CAL_ERR   = 1,
    REAL_ERR  = 2,
    CRASH_ERR = 3
};

ListError_t List_Ctor    ( struct List_t *list, elem_t start_buffer[], int buffer_size );
void        List_Dtor    ( struct List_t *list );   // ERROR +
ListError_t List_Realloc ( struct List_t *list );
ListError_t List_Insert  ( struct List_t *list, int prev, int value );
void        List_Delete  ( struct List_t *list, int index );
int         List_Search  ( struct List_t *list, int search_location );

void Text_Dump    ( const struct List_t *list );
void Graph_Dump   ( const struct List_t *list );


#endif      // LIST
