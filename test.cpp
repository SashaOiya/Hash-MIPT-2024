#include "list_test.h"

void Cache_Test ()
{
    struct Cache_t cache = {};
    struct List_Test_t test;

    bool ret_val = Cache_Text_1 ( &cache, test.test_1 );
    if ( ret_val ==  true ) {
        printf ( "TRUE\n" );
    }
    else {
        printf ( "FALSE\n" );
    }
    ret_val = Cache_Text_2 ( &cache, test.test_2 );
    if ( ret_val ==  true ) {
        printf ( "TRUE\n" );
    }
    else {
        printf ( "FALSE\n" );
    }
    ret_val = Cache_Text_3 ( &cache, test.test_3 );
    if ( ret_val ==  true ) {
        printf ( "TRUE\n" );
    }
    else {
        printf ( "FALSE\n" );
    }
    ret_val = Cache_Text_4 ( &cache, test.test_4 );
    if ( ret_val ==  true ) {
        printf ( "TRUE\n" );
    }
    else {
        printf ( "FALSE\n" );
    }
}

bool Cache_Text_2 ( struct Cache_t *cache, const struct Test_Node_t *test )
{
    assert ( cache != nullptr );

    Cache_Ctor ( cache, 10 );
    // error
    List_Insert ( cache->lirs,  10 );
    List_Insert ( cache->lirs,  30 );
    List_Insert ( cache->lirs,  50 );
    List_Insert ( cache->lirs,  90 );
    List_Delete ( cache->lirs );

    List_Insert ( cache->hirs,  15 );
    List_Insert ( cache->hirs,  35 );
    List_Insert ( cache->hirs,  55 );
    List_Insert ( cache->hirs,  95 );
    List_Delete ( cache->hirs );

    List_Swap ( cache->lirs->tail->next, cache->hirs->head->prev );

    bool ret_val = Cache_Test_Check ( cache->lirs, test );
    if ( ret_val == false ) {

        return ret_val;
    }
    ret_val = Cache_Test_Check ( cache->hirs, &(test[4]) );

    Cache_Dtor ( cache );

    return ret_val;
}

bool Cache_Text_1 ( struct Cache_t *cache, const struct Test_Node_t *test )
{
    assert ( cache != nullptr );
    assert ( test  != nullptr );

    Cache_Ctor ( cache, 10 );
    // error

    List_Insert ( cache->lirs,  15 );
    List_Insert ( cache->lirs,  30 );
    List_Insert ( cache->lirs,  50 );
    List_Insert ( cache->lirs,  90 );
    List_Delete ( cache->lirs );

    bool ret_val = Cache_Test_Check ( cache->lirs, test );

    Cache_Dtor ( cache );

    return ret_val;
}

bool Cache_Text_3 ( struct Cache_t *cache, const struct Test_Node_t *test )
{
    assert ( cache != nullptr );
    assert ( test  != nullptr );

    Cache_Ctor ( cache, 10 );
    // error

    List_Insert ( cache->lirs,  10 ); // macro with check
    List_Insert ( cache->lirs,  30 );
    List_Insert ( cache->lirs,  50 );
    List_Insert ( cache->lirs,  90 );
    List_Insert ( cache->hirs,  15 );
    List_Insert ( cache->hirs,  35 );
    List_Insert ( cache->hirs,  55 );
    List_Insert ( cache->hirs,  95 );

    List_Swap ( cache->lirs->tail, cache->hirs->tail );

    bool ret_val = Cache_Test_Check ( cache->lirs, test );

    Cache_Dtor ( cache );

    return ret_val;
}

bool Cache_Text_4 ( struct Cache_t *cache, const struct Test_Node_t *test )
{
    assert ( cache != nullptr );
    assert ( test  != nullptr );

    Cache_Ctor ( cache, 10 );
    // error
    List_Insert ( cache->lirs,  10 );
    List_Insert ( cache->hirs,  15 );

    List_Swap ( cache->lirs->tail, cache->hirs->tail );

    bool ret_val = Cache_Test_Check ( cache->lirs, test );

    Cache_Dtor ( cache );

    return ret_val;
}

bool Cache_Test_Check ( struct List_t *cache, const struct Test_Node_t *test )
{
    assert ( cache != nullptr );
    assert ( test  != nullptr );

    int i = 0;
    if ( cache->tail->prev       != nullptr      ||
         cache->tail->code       != test[i].code ||
         cache->tail->next->code != test[i].next ) {

        return false;
    }
    ++i;

    struct Cache_Elem_t *temp_list_elem = cache->tail->next;
    for ( ; i < cache->list_size - 1; ++i ) {
        if ( temp_list_elem->prev->code != test[i].prev ||
             temp_list_elem->code       != test[i].code ||
             temp_list_elem->next->code != test[i].next ) {

            return false;
        }
        temp_list_elem = temp_list_elem->next;
    }

    if ( temp_list_elem->prev->code != test[i].prev ||
         temp_list_elem->code       != test[i].code ||
         temp_list_elem->next       != nullptr ) {

        return false;
    }

    return true;
}
