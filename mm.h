#ifndef mmh
#define mmh

// used to find offset of specific field in given structure
#define offsetof(struct_name,field_name) (int)&((struct_name*)0)->field_name

// used to find actual memory address from given meta block address of specific block
#define get_actual_add(memadd) ((char*)memadd+sizeof(meta_block))





// struct which points to memory get through mmap call
typedef struct page_for_memory{
      char meta_data_block[0];
} page_for_memory;

// struct to store content of meta-block 24kb
typedef struct meta_block{
    struct meta_block *next;
    struct meta_block *prev;
    int size;
    int is_free;
    int pos;
} meta_block;




// Initialize the memory manager
void mm_init();

// For mallocation
void* Malloc(int size);

// For free memory
void Free(void* ptr);

// for reallocation of memory
void* Realloc(void* ptr,int size);

// for calloc call
void* Calloc(int n,int size);

void printheap();

#endif