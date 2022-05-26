#include<stdio.h>
#include<stdint.h>
#include<memory.h>
#include<unistd.h>     //for getting one virtual page 
#include<sys/mman.h>   //for using mmap
#include<assert.h>
#include "mm.h"

static size_t SYSTEM_PAGE_SIZE=0;
static struct_for_struct_storing* first_page_to_store_struct=NULL;

void mm_init(){
    SYSTEM_PAGE_SIZE=getpagesize();
}


static void* mm_get_new_virtual_memory_page_from_kernal(int units){
    void* vm_page=mmap(0,units*SYSTEM_PAGE_SIZE,PROT_READ|PROT_WRITE|PROT_EXEC,MAP_ANON|MAP_PRIVATE,0,0);
    if(vm_page==MAP_FAILED){
        printf("Error: VM page allocation failed\n");
        return NULL;
    }
    memset(vm_page,0,units*SYSTEM_PAGE_SIZE);
    return (void*)vm_page;
}

static void* return_vm_page_to_kernel(void* vm_page,int units){
    if(munmap(vm_page,SYSTEM_PAGE_SIZE*units)){
        printf("Error:could not free vm_page\n");
    }
}
struct_for_struct_info* find_location_to_allocate(struct_for_struct_storing* vm_page,int* count){
    struct_for_struct_info* current=&(vm_page->struct_group[0]);
    while(current->struct_size && (*count)<MAX_PAGE_FAMILY_PER_PAGE){
        current++;
        (*count)++;
    }
    return current;
}

void mm_instantiate_structure(char* struct_name,int struct_size){

  struct_for_struct_info* curr_for_finding_pos=NULL;
  struct_for_struct_storing* new_page_for_storing_struct=NULL;
  if(struct_size>SYSTEM_PAGE_SIZE){
      printf("Page size exceded");
      return;
  }
  if(!first_page_to_store_struct){
      first_page_to_store_struct=(struct_for_struct_storing*)mm_get_new_virtual_memory_page_from_kernal(1);
      first_page_to_store_struct->next=NULL;
      strcpy(first_page_to_store_struct->struct_group[0].struct_name,struct_name);
      first_page_to_store_struct->struct_group[0].struct_size=struct_size;
      return;
  }

  int count=0;
  curr_for_finding_pos=find_location_to_allocate(first_page_to_store_struct,&count);

  if(count==MAX_PAGE_FAMILY_PER_PAGE){
     new_page_for_storing_struct=(struct_for_struct_storing*)mm_get_new_virtual_memory_page_from_kernal(1);
     new_page_for_storing_struct->next=first_page_to_store_struct;
     first_page_to_store_struct=new_page_for_storing_struct;
     curr_for_finding_pos=&first_page_to_store_struct->struct_group[0];
  }
  strcpy(curr_for_finding_pos->struct_name,struct_name);
  curr_for_finding_pos->struct_size=struct_size;
//   printf("%s",curr_for_finding_pos->struct_name);


}


void Iterate_over_all_structures(){
     struct_for_struct_storing* page_itr=first_page_to_store_struct;
     while(page_itr){
         struct_for_struct_info* currpage=&page_itr->struct_group[0];
         while(currpage->struct_size){
            printf("struct Name: %s\n",currpage->struct_name);
            currpage++;
         }
         page_itr=page_itr->next;
     }
}





