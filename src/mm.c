#include <stdio.h>
#include <string.h>
#include <unistd.h>   //for getting one memory page
#include <sys/mman.h> //for using mmap
#include "mm.h"
#include "heap.h"

// global variables for heap and storing size of one memory page
heap *pointer_to_heap;
int sizeofonememorypage;

// function to get memory page from system
void *get_page_from_system(int units)
{

    void *vm_page = mmap(0, units * sizeofonememorypage, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, 0, 0);
    if (vm_page == MAP_FAILED)
    {
        printf("Error: VM page allocation failed\n");
        return NULL;
    }
    return (void *)vm_page;
}

// Function for initializing heap
void setheap()
{

    pointer_to_heap = get_page_from_system(1);
    pointer_to_heap->size = (sizeofonememorypage - sizeof(heap)) / sizeof(meta_block *);
    pointer_to_heap->rear = -1;
}

// Function for initializing our memory manager and getting one memory page size
void mm_init2(int size)
{
    // sizeofonememorypage=getpagesize();
    sizeofonememorypage = size+sizeof(meta_block);
    setheap();
}

void mm_init1()
{
    // 5000 is default memory page size we decide to allocate
    mm_init2(5000);
}
// Function for returning memory back to system
void *return_page_to_system(void *vm_page, int units)
{

    if (munmap(vm_page, sizeofonememorypage * units) == -1)
        printf("Error:could not free vm_page\n");
}

// Function for initializing new memory page get from system with meta-block and and inserting its meta block in heap
void initialize_new_page(page_for_memory *newpage)
{

    meta_block *mb = (meta_block *)newpage;
    // meta_block* mb=(meta_block*)((char*)newpage+offsetof(page_for_memory,meta_data_block));
    mb->is_free = 1;
    mb->next = NULL;
    mb->prev = NULL;
    mb->size = sizeofonememorypage - (sizeof(page_for_memory) + sizeof(meta_block));
    insert_heap(pointer_to_heap, mb);
}

// function to allocate required memory to user

void *Malloc(int size)
{

    meta_block *block = top_heap(pointer_to_heap);
    if (!block || block->size < size)
    {                                                       // if heap is empty or user request more amount free memory than available to us
        page_for_memory *newpage = get_page_from_system(1); // get new memory from system
        initialize_new_page(newpage);
        block = top_heap(pointer_to_heap);
        if (block->size < size)
        { // if still can not allocate then not possible to allocate memory as requested memory is huge
            printf("Could not allocate that much amount of size of structure size == %d \n", size);
            return NULL;
        }
    }
    block->is_free = 0; // initializing free block get from heap and removing from heap
    remove_heap(pointer_to_heap);
    int remaining_size = block->size - size;
    if (size + 2 * sizeof(meta_block) <= block->size)
    { // checking if free block can be splitted into smaller blocks or not
        block->size = size;
        meta_block *newblockadd = (char *)get_actual_add(block) + size; // finding address for meta-block of remaining size after allocation
        newblockadd->prev = block;
        newblockadd->next = block->next;
        newblockadd->is_free = 1;
        newblockadd->size = remaining_size - (sizeof(meta_block));
        block->next = newblockadd;
        insert_heap(pointer_to_heap, newblockadd); // inserting remaining free memory in heap
    }
    return get_actual_add(block);
}

void Free(void *ptr)
{

    meta_block *mbcurr = (char *)ptr - sizeof(meta_block); // finding address of meta-block from give address
    mbcurr->is_free = 1;                                   // updating it to free memory
    meta_block *mbnext = mbcurr->next;
    meta_block *mbprev = mbcurr->prev;

    if (!mbnext && !mbprev)
    {
        return_page_to_system(mbcurr, 1);
        return;
    }

    int flag1 = 0, flag2 = 0;
    if (mbprev && mbprev->is_free)
    { // check if prev and next blocks are free or not
        flag1 = 1;
        findandremove(pointer_to_heap, mbprev);
    }

    if (mbnext && mbnext->is_free)
    {
        flag2 = 1;
        findandremove(pointer_to_heap, mbnext);
    }

    // if anyone of the prev or next or both blocks are free then memory merging will happen.

    // 1) if both prev and next block are free
    if (flag1 && flag2)
    {
        int total_size = mbprev->size + mbcurr->size + mbnext->size + 2 * (sizeof(meta_block)); // finding new size of merged block
        mbprev->size = total_size;
        if (mbprev->size == sizeofonememorypage - (sizeof(page_for_memory) + sizeof(meta_block)))
        { // if our whole system page get free then return it back to system
            return_page_to_system(mbprev, 1);
            return;
        }
        mbprev->next = mbnext->next; // adjusting pointers
        if (mbnext->next)
            mbnext->next->prev = mbprev;
        insert_heap(pointer_to_heap, mbprev);
        return;
    }

    // 2) if only prev block is free
    if (flag1)
    {
        int total_size = mbprev->size + mbcurr->size + sizeof(meta_block); // finding new size of merged block
        mbprev->size = total_size;
        if (mbprev->size == sizeofonememorypage - (sizeof(page_for_memory) + sizeof(meta_block)))
        {
            return_page_to_system(mbprev, 1);
            return;
        }
        mbprev->next = mbcurr->next; // adjusting pointers
        if (mbnext)
            mbnext->prev = mbprev;
        insert_heap(pointer_to_heap, mbprev);
        return;
    }

    // 3) if only next block is free
    if (flag2)
    {
        int total_size = mbnext->size + mbcurr->size + sizeof(meta_block); // finding new size of merged block
        mbcurr->size = total_size;
        if (mbcurr->size == sizeofonememorypage - (sizeof(page_for_memory) + sizeof(meta_block)))
        {
            return_page_to_system(mbcurr, 1);
            return;
        }
        mbcurr->next = mbnext->next; // adjusting pointers
        if (mbnext->next)
            mbnext->next->prev = mbcurr;
        insert_heap(pointer_to_heap, mbcurr);
        return;
    }

    // 4) if no one is free
    insert_heap(pointer_to_heap, mbcurr);
    return;
}

void *Realloc(void *ptr, int size)
{

    meta_block *mb = (char *)ptr - sizeof(meta_block);
    int mbsize = mb->size;
    meta_block *next = mb->next;

     //if realloc size is same as current size
    if (mbsize == size)
        return ptr;

    // if realloc size is more than current size
    if (mbsize < size)
    {
        int nextblocksize = next->size;
        meta_block *nextnextblockadd = next->next;

        // if next block is free can merge to form relloc size
        if (next && next->is_free && mbsize + sizeof(meta_block) + nextblocksize >= size)
        {
            findandremove(pointer_to_heap, next);

            // if new meta-free block can be created
            if (mbsize + sizeof(meta_block) + nextblocksize >= size + sizeof(meta_block))
            {
                mb->size = size;
                meta_block *newmb = (char *)mb + size + sizeof(meta_block);
                newmb->is_free = 1;
                newmb->next = nextnextblockadd;
                newmb->prev = mb;
                newmb->size = mbsize + sizeof(meta_block) + nextblocksize - size - sizeof(meta_block);
                mb->next = newmb;
                if (nextnextblockadd)
                    nextnextblockadd->prev = newmb;
                Free(get_actual_add(newmb));
                return ptr;
            }

            // if new-meta block can not be created then allocate all free memory of next block to curr block
            else
            {
                mb->size = mbsize + sizeof(meta_block) + nextblocksize;
                mb->next = nextnextblockadd;
                if (nextnextblockadd)
                    nextnextblockadd->prev = mb;
                return ptr;
            }
        }
        // if next block is not free then mallocate required size of memory, copy content of current memory to that location and free current one
        else
        {
            void *newadd = Malloc(size);
            if (!newadd)
                return NULL;
            memcpy(newadd, ptr, mbsize);
            mb->is_free = 1;
            Free(ptr);
            return newadd;
        }
    }
    // if realloc size is less than current size

    // if meta-data block can be created then split current block and Free newly created block
    if (mbsize >= sizeof(meta_block) + size)
    {
        mb->size = size;
        meta_block *newmb = (char *)mb + size + sizeof(meta_block);
        newmb->is_free = 1;
        newmb->size = mbsize - size - sizeof(meta_block);
        newmb->next = next;
        newmb->prev = mb;
        if (next)
            next->prev = newmb;
        mb->next = newmb;
        Free(get_actual_add(newmb));
        return ptr;
    }

    // else return same ptr without any changes
    return ptr;
}

void *Calloc(int n, int size)
{

    // allocate n*size of memory using malloc
    void *mem = Malloc(size * n);

    // set all the bytes in allocated memory to 0 as required in calloc
    memset(mem, 0, size * n);
    return mem;
}


// print heap used for checking whether block remove or add in right way or not

// void printheap()
// {

//     // printf("%d\n",pointer_to_heap->rear);
//     for (int i = 0; i <= pointer_to_heap->rear; i++)
//         printf("sizeofblock %d\n", pointer_to_heap->arr[i]->size);
// }
