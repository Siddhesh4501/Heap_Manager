// #include<stdio.h>

#define MM_MAX_STRUCT_NAME 32

#define MAX_PAGE_FAMILY_PER_PAGE \
     (SYSTEM_PAGE_SIZE-(sizeof(struct_for_struct_storing*)))/sizeof(struct_for_struct_info)


typedef struct struct_for_struct_info{
    char struct_name[MM_MAX_STRUCT_NAME];
    int struct_size;
} struct_for_struct_info;


typedef struct struct_for_struct_storing{
    struct struct_for_struct_storing* next;
    struct_for_struct_info struct_group[0];
} struct_for_struct_storing;

