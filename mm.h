// #include<stdio.h>
#ifndef __MMh__
#define __MMh__


void mm_init();

void mm_instantiate_structure(char* struct_name,int struct_size);

#define MM_REG_STRUCT(struct_name) \
       (mm_instantiate_structure(#struct_name,sizeof(struct_name)))

void Iterate_over_all_structures();

void* mm_get_new_virtual_memory_page_from_kernal(int units);
void* return_vm_page_to_kernel(void* vm_page,int units);

void* Malloc(int size);
void setheap();
void printheap();


#define MM_MAX_STRUCT_NAME 32
#define MAX_PAGE_FAMILY_PER_PAGE \
     (SYSTEM_PAGE_SIZE-(sizeof(struct_for_struct_storing*)))/sizeof(struct_for_struct_info)

#define offsetof(struct_name,field_name) (unsigned int)&((struct_name*)0)->field_name
#define get_actual_add(memadd) ((char*)memadd+sizeof(meta_block))

typedef struct struct_for_struct_info{
    char struct_name[MM_MAX_STRUCT_NAME];
    int struct_size;
} struct_for_struct_info;


typedef struct struct_for_struct_storing{
    struct struct_for_struct_storing* next;
    struct_for_struct_info struct_group[0];
} struct_for_struct_storing;

typedef struct vm_page_for_memory{
      struct vm_page_for_memory *next,*prev;
      char meta_data_block[0];
} vm_page_for_memory;

typedef struct meta_block{
    struct meta_block *next;
    struct meta_block *prev;
    int size;
    int is_free;
    int offset;
} meta_block;




#endif