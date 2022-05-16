// #include<stdio.h>

#define MM_MAX_STRUCT_NAME 32

#define MAX_PAGE_FAMILY_PER_PAGE \
     (SYSTEM_PAGE_SIZE-(sizeof(vm_page_for_families_t*)))/sizeof(vm_page_family_t)

#define ITERATIVE_PAGE_FAMILES_BEGIN(vm_page_for_families_ptr,curr)\
{                                                                  \
    int count=0;                                             \  
    for(curr=(vm_page_family_t*)&vm_page_for_families_ptr->vm_page_family[0];count<MAX_PAGE_FAMILY_PER_PAGE && curr->struct_size;curr++,count++)\
    { 
#define ITERATIVE_PAGE_FAMILES_END(vm_page_for_families_ptr,curr)}}
  
// #define ITERATE_PAGE_FAMILIES_BEGIN(first_vm_page_family_ptr, curr)   \
// {                                       \
//     curr = first_vm_page_family_ptr;    \
//     vm_page_family_t *next = NULL;      \
//     for(; curr; curr = next){           \
//         next = curr->next;

// #define ITERATE_PAGE_FAMILIES_END(first_vm_page_family_ptr, curr)   \
//     }}


typedef struct vm_page_family{
    char struct_name[MM_MAX_STRUCT_NAME];
    int struct_size;
} vm_page_family_t;


typedef struct vm_page_for_families{
    struct vm_page_for_families* next;
    vm_page_family_t vm_page_family[0];
} vm_page_for_families_t;

