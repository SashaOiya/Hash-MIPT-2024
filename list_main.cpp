#include "list.h"   //h

//static bool TestList();

int main ()
{
    // Add more colors!!!
    // Max 4 without flags!!!
    struct List_t list = {};

    if ( List_Ctor ( &list ) ) {

        return -1;  //
    }// size

    List_Insert ( &list,  15 );
    List_Insert ( &list,  30 );

    Graph_Dump  ( &list );
    List_Delete ( &list );

    Graph_Dump  ( &list );
    List_Dtor   ( &list );

    return 0;
}
