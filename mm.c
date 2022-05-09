#include<stdio.h>
#include<memory.h>
#include<unistd.h>     //for getting one virtual page 
#include<sys/mman.h>   //for using mmap


static size_t SYSTEM_PAGE_SIZE=0;

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

int main(){
    mm_init();
    printf("size of one virtual page %ld\n",SYSTEM_PAGE_SIZE);
    void * addr1=mm_get_new_virtual_memory_page_from_kernal(1);
    void * addr2=mm_get_new_virtual_memory_page_from_kernal(1);
    printf("addr1->%p, addr2->%p\n",addr1,addr2);
    printf("%c",*((char*)addr1));

    return 0;
}