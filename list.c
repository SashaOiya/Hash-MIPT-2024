#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

struct ListElem* get_head(struct Cache* cache) 
{
    return cache->head;
}

struct ListElem* get_next(struct ListElem* celem) 
{
    return celem->next;
}


struct Cache* create_cache() 
{
    struct Cache* cpointer;
  
    cpointer = (struct Cache*) calloc(1, sizeof(struct Cache));
    assert(cpointer);
  
    return cpointer;
}

struct ListElem* create_celem(int value) 
{
    struct ListElem* tmp;
  
    tmp = (struct ListElem*) calloc(1, sizeof(struct ListElem));
    assert(tmp != NULL);
  
    tmp->value = value;
  
    return tmp;
}

void destruct_cache(struct Cache* cache) 
{
    struct ListElem* Tmp;
    assert(cache != NULL);

    Tmp = cache->tail;
  
    for(; Tmp != NULL; ) 
    {
        struct ListElem *Prev = Tmp->prev;
        
        destruct_celem(Tmp);
        Tmp = Prev;
    }
    
    free(cache);
}

void destruct_celem(struct ListElem* celem) 
{
    free(celem);
}

void insert_list(struct Cache* List, struct ListElem* celem) 
{
    struct ListElem *Head, *Tail;
    assert(List != NULL);
    assert(celem != NULL);

    Head = List->head;
    Tail = List->tail;

    if (Head == NULL) 
    {
        List->head = celem;
        List->tail = celem;
        
        return;
    }

    assert(Tail != NULL);
    if (Tail == Head) 
    {
        celem->next = Head;
        Head->prev = celem;
        List->head = celem;
        
        return;
    }

    assert(Head != NULL);
    
    Head->prev = celem;
    celem->next = Head;
    List->head = celem;
}

void lift_listelem(struct Cache* List, struct ListElem* ListElem) 
{
    struct ListElem *Next, *Prev;
    
    assert(List != NULL);
    assert(ListElem != NULL);
    assert(List->head != NULL);

    if (List->head == ListElem)
        return;

    if (List->tail == ListElem)
        List->tail = ListElem->prev;

    Next = ListElem->next;
    Prev = ListElem->prev;

    if (Prev != NULL)
        Prev->next = Next;

    if (Next != NULL)
        Next->prev = Prev;

    ListElem->prev = NULL;

    insert_list(List, ListElem);
    return;
}

void print_list(struct Cache* List) 
{
    struct ListElem* Tmp;

    assert(List);
    
    Tmp = List->head;
    
    while(Tmp != NULL) 
    {
        printf("%d ", Tmp->value);
        Tmp = Tmp->next;
    }
    printf("\n");
}

