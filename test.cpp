bool Cache_Test ()
{
    List_Insert ( cache.lirs,  15 );
    List_Insert ( cache.lirs,  30 );
    List_Insert ( cache.lirs,  50 );
    List_Insert ( cache.lirs,  90 );
    List_Swap ( cache.lirs->tail->next, cache.lirs->head->prev );
