#include<stdio.h>
#include<stdint.h>
#include<memory.h>
#include<unistd.h>     //for getting one virtual page 
#include<sys/mman.h>   //for using mmap
#include "mm.h"
#include<assert.h>

static size_t SYSTEM_PAGE_SIZE=0;
static vm_page_for_families_t* first_vm_page_for_families=NULL;

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


void mm_instantiate_new_page_family(char* struct_name,int struct_size){

  vm_page_family_t* vm_page_family_curr=NULL;
  vm_page_for_families_t* new_vm_page_for_families=NULL;
  if(struct_size>SYSTEM_PAGE_SIZE){
      printf("Page size exceded");
      return;
  }
  if(!first_vm_page_for_families){
      first_vm_page_for_families=(vm_page_for_families_t*)mm_get_new_virtual_memory_page_from_kernal(1);
      first_vm_page_for_families->next=NULL;
      strcpy(first_vm_page_for_families->vm_page_family[0].struct_name,struct_name);
      first_vm_page_for_families->vm_page_family[0].struct_size=struct_size;
      return;
  }
  int count=0;

  ITERATIVE_PAGE_FAMILES_BEGIN(first_vm_page_for_families,vm_page_family_curr){
      if(strcmp(vm_page_family_curr->struct_name,struct_name)!=0){
        count++;
        continue;
      }
      assert(0);

  } ITERATIVE_PAGE_FAMILES_END(first_vm_page_for_families,vm_page_family_curr);

  if(count==MAX_PAGE_FAMILY_PER_PAGE){
     new_vm_page_for_families=(vm_page_for_families_t*)mm_get_new_virtual_memory_page_from_kernal(1);
     new_vm_page_for_families->next=first_vm_page_for_families;
     first_vm_page_for_families=new_vm_page_for_families;
     vm_page_family_curr=&first_vm_page_for_families->vm_page_family[0];
  }
  strcpy(vm_page_family_curr->struct_name,struct_name);
  vm_page_family_curr->struct_size=struct_size;
//   printf("%s",vm_page_family_curr->struct_name);


}




