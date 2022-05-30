#ifndef __MMh__
#define __MMh__

// used to find offset of specific field in given structure
#define offsetof(struct_name,field_name) (int)&((struct_name*)0)->field_name

// used to find actual memory address from given meta block address of specific block
#define get_actual_add(memadd) ((char*)memadd+sizeof(meta_block))


// struct which points to memory get through mmap call
typedef struct vm_page_for_memory{
      char meta_data_block[0];
} vm_page_for_memory;

// struct to store content of meta-block
typedef struct meta_block{
    struct meta_block *next;
    struct meta_block *prev;
    int size;
    int is_free;
    int offset;
} meta_block;

// Initialize the memory manager
void mm_init();

// For mallocation
void* Malloc(int size);

// For free memory
void Free(void* ptr);

#endif