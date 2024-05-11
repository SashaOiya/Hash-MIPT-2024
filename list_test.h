#ifndef LIST_TEST
#define LIST_TEST

#include "list.h"

struct Test_Node_t {
    int prev;
    int code;
    int next;
};

struct List_Test_t {
    const struct Test_Node_t test_1[4] = {
                                          { POISON, 30, 50 }, { 30, 50, 90 }, { 50, 90, 0 }, { 90, 0, POISON }
                                         };
    const struct Test_Node_t test_2[8] = {
                                          { POISON, 30, 95 }, { 30, 95, 90 }, { 95, 90, 0 }, { 90, 0, POISON },
                                          { POISON, 35, 55 }, { 35, 55, 50 }, { 55, 50, 0 }, { 50, 0, POISON }
                                         };

};

void Cache_Test ();
bool Cache_Text_1 ( struct Cache_t *cache, const struct Test_Node_t *test );
bool Cache_Text_2 ( struct Cache_t *cache, const struct Test_Node_t *test );
bool Cache_Test_Check ( struct List_t *cache, const struct Test_Node_t *test );

#endif  // LIST_TEST
