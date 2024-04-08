#include "list.h"   //h

//static bool TestList();

int main ()
{

    // Add more colors!!!
    // Max 4 without flags!!!
    struct List_t list = {};

    elem_t code[] = { 10, 20, 30, 40, 50, 60, 0 };

    if ( List_Ctor ( &list, code, sizeof ( code ) / sizeof ( elem_t ) ) ) {

        return -1;  //
    }// size

    int new_place = List_Search ( &list, 2 );

    List_Insert ( &list, new_place, 15 );
    List_Insert ( &list, 2, 25 );
    List_Insert ( &list, 4, 35 );
    List_Delete ( &list, 5 );
    List_Insert ( &list, 1, 45 );

    Graph_Dump  ( &list );

    List_Dtor   ( &list );

    return 0;
}
