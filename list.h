#ifndef LIST
#define LIST

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <cstring>

const int POISON = 5674;
const int START_BUFFER_SIZE = 1;

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
    Cache_Elem_t *tail = nullptr;
    Cache_Elem_t *head = nullptr;
};

struct Cache_t {
    struct List_t *lirs  = nullptr;
    struct List_t *hirs  = nullptr;
    int cache_size = 0;  // const
};

enum List_Error_t {
    OK        = 0,
    ERR_CALLO = 1,
    ERR_REALL = 2
};

List_Error_t Cache_Ctor ( struct Cache_t *cache, const int given_cache_size );
List_Error_t List_Ctor  ( struct List_t **list );

void         List_Delete ( struct List_t *list );
List_Error_t List_Insert ( struct List_t *list, int value );
List_Error_t List_Swap   ( struct Cache_Elem_t *lir_elem, struct Cache_Elem_t *hir_elem );

void List_Text_Dump   ( struct List_t *list, const char *list_name );
void Cache_Graph_Dump ( const struct Cache_t *cache );
void Graph_Dump_Body  ( const struct List_t  *list, FILE *dot );


void List_Dtor  ( struct List_t  *list  );
void Cache_Dtor ( struct Cache_t *cache );


#endif      // LIST
