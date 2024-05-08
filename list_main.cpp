#include "list.h"   //h

//static bool TestList();

int main ()
{
    // Add more colors!!!
    // Max 4 without flags!!!
    struct Cache_t cache = {};

    if ( Cache_Ctor ( &cache, 10 ) ) {

        return -1;  //
    }

    List_Insert ( cache.lirs,  15 ); // macro with check
    List_Insert ( cache.lirs,  30 );
    List_Insert ( cache.lirs,  50 );
    //List_Insert ( &list,  60 ); // remove

    Cache_Graph_Dump  ( &cache );
    //List_Delete ( &list );

    List_Swap ( cache.lirs->tail, cache.lirs->head );
    //Text_Dump ( &list );

    Cache_Graph_Dump  ( &cache );

    List_Dtor   ( cache.lirs );

    return 0;
}
