#ifndef __heaph__
#define __heaph__
#include "mm.h"

typedef struct heap{
   int size;
   int rear;
   meta_block* arr[0];
} heap;

void insert_heap(heap* h,meta_block* mb);
meta_block* remove_heap(heap* h);
meta_block* top_heap(heap* h);

#endif