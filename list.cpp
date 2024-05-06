#include "list.h"

FILE *logfile = fopen ( "logs/log.html", "w" );

void Text_Dump ( struct List_t *list )
{
    // FILE* html_file; // "list_dump.html"
    // const char *const ....
    printf ( "\tList tail [%p] :\n"
             "\t         value : %d"
             "\t         prev  : [%p]"
             "\t         next  : [%p]\n", list->tail, list->tail->code, list->tail->prev, list->tail->next );

    printf ( "\tList head [%p] :\n"
             "\t         value : %d"
             "\t         prev  : [%p]\n", list->head, list->head->code, list->head->prev );

    printf ( "size : %d\n\n", list->list_size );
}

List_Error_t List_Insert ( struct List_t *list, int value )
{
    assert ( list != nullptr );

    ++list->list_size;

    /*if ( list->head->prev == list->tail ) {
        //list->head = ( Cache_Elem_t *)calloc ( 1, sizeof ( Cache_Elem_t ) );
        list->head->code = value;
        //list->head->prev = list->tail;

        Text_Dump ( list );

        return OK;
    }*/

    list->head->next       = ( Cache_Elem_t *)calloc ( 1, sizeof ( Cache_Elem_t ) );
    printf ( "list head next [%p]\n", list->head->next );
    // nullpt r
    list->head->code = value;
    list->head->next->prev = list->head;
    //printf ( "list head next prev [%p]\n", list->head->next->prev );
    list->head             = list->head->next;
    //printf ( "list head next prev [%p]\n", list->head->next->prev );
    //printf ( "list head [%p]\n", list->head );

    Text_Dump ( list );

    return OK;
}

/*void List_Delete ( struct List_t *list, int place )
{
    if ( place == list->tail ) {
        list->tail = list->prev[list->tail];
    }
    if ( place == list->head ) {
        list->next[0] = list->next[place];
    }
    --(list->size);

    list->code[place] = 0;

    int temp_prev = list->prev[place];
    int temp_next = list->next[place];

    list->next[place] = list->free;
    list->free        = place;
    list->prev[place] = FREE_INDEX;
    list->next[temp_prev] = temp_next;
    list->prev[temp_next] = temp_prev;

    Text_Dump ( list );
}  */

List_Error_t List_Ctor   ( struct List_t *list )
{
    assert ( list != nullptr );

    list->list_size     = START_BUFFER_SIZE;
    //list->capacity = list->size - 1 ;

    list->head = (Cache_Elem_t *)calloc ( 1, sizeof ( Cache_Elem_t ) );
    list->tail = (Cache_Elem_t *)calloc ( 1, sizeof ( Cache_Elem_t ) );

    if ( ! ( list->head && list->tail ) ) {
        free ( list->tail );
        free ( list->head );

        return ERR_CALLO;
    }

    list->tail->code = POISON;
    list->tail->next = list->head;
    list->head->prev = list->tail;

    Text_Dump ( list );

    return OK;
}

/*List_Error_t List_Realloc ( struct List_t *list )
{
    assert ( list       != nullptr );
    assert ( list->code != nullptr );

    list->capacity *= REALLOC_CONST;

    list->code = ( elem_t *) realloc ( list->code, list->capacity * sizeof ( list->code[0] ) );
    list->next = ( int *)    realloc ( list->next, list->capacity * sizeof ( list->next[0] ) );
    list->prev = ( int *)    realloc ( list->prev, list->capacity * sizeof ( list->prev[0] ) );

    if ( ! ( list->code && list->next && list->prev ) ) {
        free ( list->code );
        free ( list->next );
        free ( list->prev );

        return ERR_REALL;
    }

    for ( int i = list->capacity / REALLOC_CONST; i < list->capacity; ++i ) {
        list->code[i] = 0;
        list->next[i] = i + 1;
        list->prev[i] = REALLOC_CONST;
    }

    return OK;
} */

void Graph_Dump ( const struct List_t *list )
{
    static int file_count = 0;

    FILE *dot = fopen ( "list.dot", "w" );
    if ( !dot ) {
        perror ( "File opening failed" );

        return ;
    }

    fprintf ( dot, "digraph G { \n"
                   "rankdir = LR;\n"
                   "node [shape = record];\n"
                   " 0 " );

    /*for ( int i = 0; i < list->list->size - 1; ++i ) {
        fprintf ( dot, "-> %d", i );
    } */

    fprintf ( dot, "[arrowsize = 0.0, weight = 10000, color = \"#FFFFFF\"];\n" );

    struct Cache_Elem_t *temp_list_elem = list->tail;
    for ( int i = 0; i < list->list_size - 1; ++i ) {
        fprintf ( dot, "%d [shape = Mrecord, style = filled, fillcolor = lightpink "
                       " label = \"idx: %d | data: %d | next: %d | prev: %d\"];\n ",i, i, temp_list_elem->code,
                                                                                          temp_list_elem->next->code,
                                                                                          temp_list_elem->prev->code );
        temp_list_elem = temp_list_elem->next;
    }
    temp_list_elem = list->tail;
    for ( int i = 0; i < list->list_size -1; ++i ) {
        fprintf ( dot, "%p -> %p;\n", temp_list_elem, temp_list_elem->next );
        temp_list_elem = temp_list_elem->next;
    }

    fprintf ( dot, "}\n" );
    fclose ( dot );

    const int SIZE = 100;
    char name[SIZE] = {};
    fprintf( logfile, "<img src=\"tree%d.png\" alt=\"-\" width=\"500\" height=\"600\">\n", file_count);
    sprintf( name, "dot -T png list.dot -o logs/tree%d.png", file_count++ );
    system ( name );
}

void List_Dtor ( struct List_t *list )
{
    assert ( list != nullptr );

    Cache_Elem_t *temp_list_elem = list->tail;
    for ( int i = 0; i < list->list_size -1; ++i ) {
        temp_list_elem = temp_list_elem->next;
        free (temp_list_elem->prev );
    }

    //memset( list, 0, sizeof(List_t));
}


