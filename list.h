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
const int START_BUFFER_SIZE = 2;

typedef int elem_t;

/*
 * Struct list ....
 * Data structure scheme:
 * [null (poison) element] - [first free element] -
 * 0                         1
 *
 */

struct Cache_Elem_t {
    elem_t code  = 0;
    Cache_Elem_t *next = 0;
    Cache_Elem_t *prev = 0;
};

struct List_t {
    int list_size = 0;
    Cache_Elem_t *tail = nullptr;// = FIRST_FREE_ELEM; /* first non poison element */
    Cache_Elem_t *head = nullptr;// = FIRST_FREE_ELEM;
};

struct Cache_t {
    struct List_t lirs  = {};
    struct List_t hears = {};
    int cache_size = 0;  // const
};

enum List_Error_t {
    OK        = 0,
    ERR_CALLO = 1,
    ERR_REALL = 2
};

List_Error_t List_Ctor    ( struct List_t *list );
void         List_Dtor    ( struct List_t *list );   // ERROR +
//List_Error_t List_Realloc ( struct List_t *list );
List_Error_t List_Insert  ( struct List_t *list, int value );
void         List_Delete  ( struct List_t *list );
//int          List_Search  ( struct List_t *list, int search_location );

void Text_Dump  ( struct List_t *list );
void Graph_Dump ( const struct List_t *list );
void Graph_Dump_Body ( const struct List_t *list, FILE *dot );


#endif      // LIST