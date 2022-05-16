// #include<stdint.h>
#include "mm.h"
#ifndef __UAPI_MM__
#define __UAPI_MM__


void mm_init();

void mm_instantiate_new_page_family(char* struct_name,int struct_size);

#define MM_REG_STRUCT(struct_name) \
       (mm_instantiate_new_page_family(#struct_name,sizeof(struct_name)))

void Iterate_Over_All_Page_Families();

#endif