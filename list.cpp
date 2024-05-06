#include "list.h"

FILE *logfile = fopen ( "logs/log.html", "w" );

List_Error_t List_Ctor   ( struct List_t *list )
{
    assert ( list != nullptr );

    list->list_size     = START_BUFFER_SIZE;

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

    Text_Dump ( list );  // macro

    return OK;
}

List_Error_t List_Insert ( struct List_t *list, int value )
{
    assert ( list != nullptr );

    ++list->list_size;

    list->head->next       = ( Cache_Elem_t *)calloc ( 1, sizeof ( Cache_Elem_t ) );
    //assert
    list->head->code = value;
    list->head->next->prev = list->head;
    list->head             = list->head->next;

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

void Graph_Dump ( const struct List_t *list )
{
    static int file_count = 0;

    FILE *dot = fopen ( "list.dot", "w" );
    if ( !dot ) {
        perror ( "File opening failed" );

        return ;
    }

    Graph_Dump_Body ( list, dot );

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

    fprintf ( dot, "digraph G { \n"
                   "rankdir = LR;\n"
                   "node [shape = record];\n"
                   " \"%p\" ", list->tail );

    struct Cache_Elem_t *temp_list_elem = list->tail;
    for ( int i = 0; i < list->list_size - 1; ++i ) {
        fprintf ( dot, "-> \"%p\" ", temp_list_elem );
    }

    fprintf ( dot, "[arrowsize = 0.0, weight = 10000, color = \"#FFFFFF\"];\n" );

    fprintf ( dot, " \"%p\" [shape = Mrecord, style = filled, fillcolor = lightpink "
                   " label = \"tail: %d | next: %d\"];\n ",temp_list_elem, temp_list_elem->code,
                                                                           temp_list_elem->next->code );
    temp_list_elem = list->tail->next;
    for ( int i = 0; i < list->list_size - 2; ++i ) {
        fprintf ( dot, " \"%p\" [shape = Mrecord, style = filled, fillcolor = lightpink "
                       " label = \"data: %d | next: %d | prev: %d\"];\n ",temp_list_elem, temp_list_elem->code,
                                                                                          temp_list_elem->next->code,
                                                                                          temp_list_elem->prev->code );
        temp_list_elem = temp_list_elem->next;
    }
    fprintf ( dot, " \"%p\" [shape = Mrecord, style = filled, fillcolor = lightpink "
                   " label = \"head: %d | prev: %d\"];\n ",temp_list_elem, temp_list_elem->code,
                                                                           temp_list_elem->prev->code );

    temp_list_elem = list->tail;
    for ( int i = 0; i < list->list_size - 1; ++i ) {
        fprintf ( dot, "\"%p\" -> \"%p\";\n", temp_list_elem, temp_list_elem->next );
        temp_list_elem = temp_list_elem->next;
    }
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


