#ifndef mmh
#define mmh

// used to find offset of specific field in given structure
#define offsetof(struct_name, field_name) (int)&((struct_name *)0)->field_name

// used to find actual memory address from given meta block address of specific block
#define get_actual_add(memadd) ((char *)memadd + sizeof(meta_block))

// struct which points to memory get through mmap call
typedef struct page_for_memory
{ // size 0 kb
    char meta_data_block[0];
} page_for_memory;


// struct to store content of meta-block
typedef struct meta_block
{ // size 24 kb
    struct meta_block *next;
    struct meta_block *prev;
    int size;
    int is_free;
} meta_block;


// For Initialization of memory manager
// Macros to call for specific Function based on argument passed to mm_init function
#define GET_MACRO(_0, _1, NAME, ...) NAME
#define mm_init(...) GET_MACRO(_0, ##__VA_ARGS__, mm_init2, mm_init1)(__VA_ARGS__)

// For mallocation
void *Malloc(int size);

// For free memory
void Free(void *ptr);

// for reallocation of memory
void *Realloc(void *ptr, int size);

// for calloc call
void *Calloc(int n, int size);

// void printheap();

#endif