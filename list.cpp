#include "list.h"

static const int DUMP_COUNTER = 100;

List_Error_t Cache_Ctor ( struct Cache_t *cache, const int given_cache_size )
{
    assert ( cache!= nullptr );
    assert ( given_cache_size >= 2 * START_BUFFER_SIZE );

    cache->cache_size = given_cache_size;

    List_Error_t ret_code = List_Ctor ( &(cache->lirs) );
    if ( ret_code != OK ) {

        return ret_code;
    }
    ret_code = List_Ctor ( &(cache->hirs) );

    return ret_code;
}

List_Error_t List_Ctor ( struct List_t **list )
{
    assert ( list != nullptr );

    *list = (List_t *)calloc ( 1, sizeof ( List_t ) );
    if ( !(*list) ) {
        free ( *list );

        return ERR_CALLO;
    }

    (*list)->list_size = START_BUFFER_SIZE;

    (*list)->bottom = (Cache_Elem_t *)calloc ( 1, sizeof ( Cache_Elem_t ) );
    if ( !((*list)->bottom) ) {
        free ( *list );
        free ( (*list)->bottom );

        return ERR_CALLO;
    }

    (*list)->top = (*list)->bottom;

    return OK;
}

List_Error_t List_Insert ( struct List_t *list, int value )
{
    assert ( list != nullptr );
    assert ( list->list_size >= START_BUFFER_SIZE  );

    ++list->list_size;

    list->top->next = ( Cache_Elem_t *)calloc ( 1, sizeof ( Cache_Elem_t ) );
    if ( !(list->top->next) ) {
        free ( list->top->next );

        return ERR_CALLO;
    }

    list->top->code = value;
    list->top->next->prev = list->top;
    list->top             = list->top->next;


    return OK;
}

List_Error_t List_Swap ( struct Cache_Elem_t *lir_elem, struct Cache_Elem_t *hir_elem )
{
    assert ( lir_elem != nullptr );
    assert ( hir_elem != nullptr );

    if ( lir_elem->next == nullptr || hir_elem->next == nullptr ) {
        printf ( "WARNING : list top\n" );

        return OK;
    }

    if ( ( lir_elem->next == hir_elem && hir_elem->prev == lir_elem ) ||
         ( lir_elem->prev == hir_elem && hir_elem->next == lir_elem ) ||
         lir_elem->prev == nullptr || hir_elem->prev == nullptr ) {
        elem_t temp_code = lir_elem->code;
        lir_elem->code = hir_elem->code;
        hir_elem->code = temp_code;

        return OK;
    }

    Cache_Elem_t *temp_list = ( Cache_Elem_t *)calloc ( 1, sizeof ( Cache_Elem_t ) );
    temp_list->code = lir_elem->code;
    temp_list->next = lir_elem->next;
    temp_list->prev = lir_elem->prev;

    lir_elem->prev = hir_elem->prev;
    lir_elem->next = hir_elem->next;
    hir_elem->prev->next = lir_elem;
    hir_elem->next->prev = lir_elem;

    hir_elem->prev = temp_list->prev;
    hir_elem->next = temp_list->next;
    temp_list->prev->next = hir_elem;
    temp_list->next->prev = hir_elem;

    free ( temp_list );

    return OK;
}

void List_Delete ( struct List_t *list )
{
    assert ( list != nullptr );

    if ( list->list_size <= START_BUFFER_SIZE ) {
        printf ( "Size error in List_Delete\n" );

        return ;
    }

    --list->list_size;

    list->bottom->code = POISON; //
    list->bottom->prev = nullptr;
    list->bottom = list->bottom->next;

    free ( list->bottom->prev );
    list->bottom->prev = nullptr;
}

void List_Text_Dump ( struct List_t *list, const char *list_name )  // color
{
    assert ( list != nullptr );
    assert ( list_name != nullptr );

    printf ( "%s bottom [%p] :\n"
             "\t     value : %d"
             "\t     prev  : [%p]"
             "\t     next  : [%p]\n", list_name, list->bottom, list->bottom->code, list->bottom->prev, list->bottom->next );

    printf ( "%s top [%p] :\n"
             "\t     value : %d"
             "\t     prev  : [%p]\n", list_name, list->top, list->top->code, list->top->prev );

    printf ( "size : %d\n\n", list->list_size );
}

void Cache_Graph_Dump ( const struct Cache_t *cache )
{
    assert ( cache != nullptr );

    FILE *dot = fopen ( "list.dot", "w" );
    if ( !dot ) {
        perror ( "File opening failed" );

        return ;
    }

    fprintf ( dot, "digraph G { \n"
                   "rankdir = LR;\n"
                   "node [shape = record];\n" );

    Graph_Dump_Body ( cache->lirs, dot );
    Graph_Dump_Body ( cache->hirs, dot );

    fprintf ( dot, "}\n" );
    fclose ( dot );

    static int file_counter = 0;
    char command_buffer[DUMP_COUNTER] = {};
    //fprintf( log(), "<img src=\"tree%d.png\" alt=\"-\" width=\"500\" height=\"600\">\n", file_counter );
    sprintf( command_buffer, "dot -T png list.dot -o logs/tree%d.png", file_counter++ );
    system ( command_buffer );
}

void Graph_Dump_Body ( const struct List_t *list, FILE *dot )
{
    assert ( list != nullptr );
    assert ( dot  != nullptr );

    fprintf ( dot, " \"%p\" ", list->bottom );

    struct Cache_Elem_t *temp_list_elem = list->bottom;
    for ( int i = 0; i < list->list_size - 1; ++i ) {
        fprintf ( dot, "-> \"%p\" ", temp_list_elem );
        temp_list_elem = temp_list_elem->next;
    }

    fprintf ( dot, "[arrowsize = 0.0, weight = 10000, color = \"#FFFFFF\"];\n" );

    if ( list->list_size == START_BUFFER_SIZE ) {
        fprintf ( dot, " \"%p\" [shape = Mrecord, style = filled, fillcolor = lightpink "
                       " label = \"bottom: %d \"];\n ",list->bottom, list->bottom->code );
        return;
    }

    fprintf ( dot, " \"%p\" [shape = Mrecord, style = filled, fillcolor = lightpink "
                   " label = \"bottom: %d | next: %d\"];\n ",list->bottom, list->bottom->code,
                                                                       list->bottom->next->code );

    temp_list_elem = list->bottom->next;
    for ( int i = 0; i < list->list_size - 2; ++i ) {
        fprintf ( dot, " \"%p\" [shape = Mrecord, style = filled, fillcolor = lightpink "
                       " label = \"data: %d | next: %d | prev: %d\"];\n ",temp_list_elem, temp_list_elem->code,
                                                                                          temp_list_elem->next->code,
                                                                                          temp_list_elem->prev->code );
        temp_list_elem = temp_list_elem->next;
    }

    fprintf ( dot, " \"%p\" [shape = Mrecord, style = filled, fillcolor = lightpink "
                   " label = \"top: %d | prev: %d\"];\n ",temp_list_elem, temp_list_elem->code,
                                                                           temp_list_elem->prev->code );
    temp_list_elem = list->bottom;
    for ( int i = 0; i < list->list_size - 1; ++i ) {
        fprintf ( dot, "\"%p\" -> \"%p\";\n", temp_list_elem, temp_list_elem->next );
        temp_list_elem = temp_list_elem->next;
    }
}

void Cache_Dtor ( struct Cache_t *cache )
{
    assert ( cache != nullptr );

    cache->cache_size = 0;
    List_Dtor ( cache->lirs );
    List_Dtor ( cache->hirs );
}

void List_Dtor ( struct List_t *list )
{
    assert ( list != nullptr );

    Cache_Elem_t *temp_list_elem = list->bottom;
    for ( int i = 0; i < list->list_size -1; ++i ) {
        temp_list_elem = temp_list_elem->next;
        free (temp_list_elem->prev );
    }
}


