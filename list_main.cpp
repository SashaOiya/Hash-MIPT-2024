#include "list.h"   //h
#include "list_test.h"

//static bool TestList();

int main ()
{
    // Add more colors!!!

    Cache_Test ();

    struct Cache_t cache = {};

    if ( Cache_Ctor ( &cache, 10 ) ) {

        return -1;  //
    }

    List_Insert ( cache.lirs,  10 ); // macro with check
    List_Insert ( cache.lirs,  30 );
    List_Insert ( cache.lirs,  50 );
    List_Insert ( cache.lirs,  90 );
    //List_Delete ( cache.lirs ); // remove
    List_Insert ( cache.hirs,  15 );
    List_Insert ( cache.hirs,  35 );
    List_Insert ( cache.hirs,  55 );
    List_Insert ( cache.hirs,  95 );

    Cache_Graph_Dump  ( cache.lirs );
    Cache_Graph_Dump  ( cache.hirs );
    //List_Delete ( &list );

    List_Swap ( cache.lirs->tail, cache.hirs->tail );
    List_Text_Dump ( cache.lirs, "lirs" );

    Cache_Graph_Dump  ( cache.lirs );
    Cache_Graph_Dump  ( cache.hirs );
    //Text_Dump ( &list );

    //Cache_Graph_Dump  ( &cache );

    List_Dtor   ( cache.lirs );

    return 0;
}
