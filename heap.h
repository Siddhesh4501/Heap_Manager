#ifndef __heaph__
#define __heaph__
#include "mm.h"

// heap structure
typedef struct heap{
   int size;
   int rear;
   meta_block* arr[0];
} heap;



// insert in heap
void insert_heap(heap* h,meta_block* mb);

// finding top element from heap
meta_block* top_heap(heap* h);

// remove top element from heap
void remove_heap(heap* h);

// deleting some intermidiate element from heap
void findandremove(heap *h,meta_block* mb);



#endif