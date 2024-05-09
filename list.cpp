#include "list.h"

FILE *logfile = fopen ( "logs/log.html", "w" );

// FILE* html_file; // "list_dump.html"
    // const char *const ....

// SWAP

List_Error_t Cache_Ctor ( struct Cache_t *cache, const int given_cache_size )
{
    assert ( cache!= nullptr );

    cache->lirs = (List_t *)calloc ( 1, sizeof ( List_t ) );
    cache->hirs = (List_t *)calloc ( 1, sizeof ( List_t ) );

    cache->cache_size = given_cache_size;
    cache->lirs->list_size = START_BUFFER_SIZE;
    cache->hirs->list_size = START_BUFFER_SIZE;

    cache->lirs->tail = (Cache_Elem_t *)calloc ( 1, sizeof ( Cache_Elem_t ) );
    cache->hirs->tail = (Cache_Elem_t *)calloc ( 1, sizeof ( Cache_Elem_t ) );

    if ( !(cache->lirs->tail && cache->hirs->tail) ) {
        free ( cache->lirs->tail );
        free ( cache->hirs->tail );

        return ERR_CALLO;
    }

    cache->lirs->head = cache->lirs->tail;
    cache->hirs->head = cache->hirs->tail;

    //Text_Dump ( list );  // macro

    return OK;
}

List_Error_t List_Insert ( struct List_t *list, int value )
{
    assert ( list != nullptr );
    assert ( list->list_size >= START_BUFFER_SIZE  );

    ++list->list_size;

    list->head->next       = ( Cache_Elem_t *)calloc ( 1, sizeof ( Cache_Elem_t ) );
    //assert
    list->head->code = value;
    list->head->next->prev = list->head;
    list->head             = list->head->next;

    List_Text_Dump ( list, "list" );

    return OK;
}

List_Error_t List_Swap ( struct Cache_Elem_t *lir_elem, struct Cache_Elem_t *hir_elem )
{
    assert ( lir_elem != nullptr );
    assert ( hir_elem != nullptr );

    // tail or head
    if ( ( lir_elem->next == hir_elem && hir_elem->prev == lir_elem ) ||
         ( lir_elem->prev == hir_elem && hir_elem->next == lir_elem ) ||
           lir_elem->prev == nullptr || hir_elem->next == nullptr ) {
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

    printf ("LOX SWAP\n"); //

    return OK;
}

void List_Delete ( struct List_t *list )  // name delete hears
{
    assert ( list != nullptr );

    if ( list->list_size <= START_BUFFER_SIZE ) {
        printf ( "Size error in List_Delete\n" );

        return ;
    }

    --list->list_size;

    list->tail->code = POISON; //
    list->tail->prev = nullptr;
    list->tail = list->tail->next;

    free ( list->tail->prev );
    list->tail->prev = nullptr;
}

void List_Text_Dump ( struct List_t *list, const char *list_name )  // color
{
    assert ( list != nullptr );
    assert ( list_name != nullptr );

    printf ( "%s tail [%p] :\n"
             "\t     value : %d"
             "\t     prev  : [%p]"
             "\t     next  : [%p]\n", list_name, list->tail, list->tail->code, list->tail->prev, list->tail->next );

    printf ( "%s head [%p] :\n"
             "\t     value : %d"
             "\t     prev  : [%p]\n", list_name, list->head, list->head->code, list->head->prev );

    printf ( "size : %d\n\n", list->list_size );
}

void Cache_Graph_Dump ( const struct Cache_t *cache )
{
    assert ( cache != nullptr );

    static int file_count = 0;

    FILE *dot = fopen ( "list.dot", "w" );
    if ( !dot ) {
        perror ( "File opening failed" );

        return ;
    }

    Graph_Dump_Body ( cache->lirs, dot );
    //Graph_Dump_Body ( cache->hirs, dot );
    // size

    fprintf ( dot, "}\n" );
    fclose ( dot );

    const int SIZE = 100;
    char name[SIZE] = {};
    fprintf( logfile, "<img src=\"tree%d.png\" alt=\"-\" width=\"500\" height=\"600\">\n", file_count);
    sprintf( name, "dot -T png list.dot -o logs/tree%d.png", file_count++ );
    system ( name );
}

void Graph_Dump_Body ( const struct List_t *list, FILE *dot )
{
    assert ( list != nullptr );
    assert ( dot  != nullptr );

    // tail head

    fprintf ( dot, "digraph G { \n"
                   "rankdir = LR;\n"
                   "node [shape = record];\n"
                   " \"%p\" ", list->tail );

    struct Cache_Elem_t *temp_list_elem = list->tail;
    for ( int i = 0; i < list->list_size - 1; ++i ) {
        fprintf ( dot, "-> \"%p\" ", temp_list_elem );
        temp_list_elem = temp_list_elem->next;
    }
    printf ( "LOX DUMP\n" ); //

    fprintf ( dot, "[arrowsize = 0.0, weight = 10000, color = \"#FFFFFF\"];\n" );

    if ( list->list_size == START_BUFFER_SIZE ) {
        fprintf ( dot, " \"%p\" [shape = Mrecord, style = filled, fillcolor = lightpink "
                       " label = \"tail: %d \"];\n ",list->tail, list->tail->code );
        return;
    }

    fprintf ( dot, " \"%p\" [shape = Mrecord, style = filled, fillcolor = lightpink "
                   " label = \"tail: %d | next: %d\"];\n ",list->tail, list->tail->code,
                                                                       list->tail->next->code );
    printf ( "LOX DUMP\n" ); //
    temp_list_elem = list->tail->next;
    for ( int i = 0; i < list->list_size - 2; ++i ) {
        fprintf ( dot, " \"%p\" [shape = Mrecord, style = filled, fillcolor = lightpink "
                       " label = \"data: %d | next: %d | prev: %d\"];\n ",temp_list_elem, temp_list_elem->code,
                                                                                          temp_list_elem->next->code,
                                                                                          temp_list_elem->prev->code );
        temp_list_elem = temp_list_elem->next;
    }
    printf ( "LOX DUMP\n" );//
    fprintf ( dot, " \"%p\" [shape = Mrecord, style = filled, fillcolor = lightpink "
                   " label = \"head: %d | prev: %d\"];\n ",temp_list_elem, temp_list_elem->code,
                                                                           temp_list_elem->prev->code );
    temp_list_elem = list->tail;
    for ( int i = 0; i < list->list_size - 1; ++i ) {
        fprintf ( dot, "\"%p\" -> \"%p\";\n", temp_list_elem, temp_list_elem->next );
        temp_list_elem = temp_list_elem->next;
    }
    printf ( "LOX DUMP\n" );//
}

void List_Dtor ( struct List_t *list )
{
    assert ( list != nullptr );

    Cache_Elem_t *temp_list_elem = list->tail;
    for ( int i = 0; i < list->list_size -1; ++i ) {   // nullptr
        temp_list_elem = temp_list_elem->next;
        free (temp_list_elem->prev );
    }
}


