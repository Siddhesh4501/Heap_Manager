#include<stdio.h>
#include<stdint.h>
#include<memory.h>
#include<unistd.h>     //for getting one virtual page 
#include<sys/mman.h>   //for using mmap
#include "heap.h"

#define max(a,b) (a)>b?a:b


void heapifyup(heap* h){
    int i=h->rear;
    int parent=(i-1)/2;
    while(h->arr[i]->size>h->arr[parent]->size){
        meta_block* temp=h->arr[i];
        h->arr[i]=h->arr[parent];
        h->arr[parent]=temp;
    }
    return;
}
void heapifydown(heap* h){
    int i=0;
    while(1){
        int left=i*2+1;
        int right=i*2+2;
        int maxi=h->arr[i]->size;
        if(left<=h->rear)
           maxi=max(maxi,h->arr[left]->size);
        if(right<=h->rear)
           maxi=max(maxi,h->arr[right]->size);
        if(maxi==h->arr[i]->size)
           return;
        if(left<=h->rear && maxi==h->arr[left]->size){
            meta_block* temp=h->arr[i];
            h->arr[i]=h->arr[left];
            h->arr[left]=temp;
            i=left;
        }
        else{
            meta_block* temp=h->arr[i];
            h->arr[i]=h->arr[right];
            h->arr[right]=temp;
            i=right;
        }

    }
   
       
}

meta_block* remove_heap(heap* h){
    if(h->rear==-1) return NULL;
    meta_block* ans=h->arr[0];
    h->arr[0]=h->arr[h->rear];
    h->rear--;
    if(h->rear!=-1)
       heapifydown(h);
    return ans;
}

void insert_heap(heap* h,meta_block* mb){
    if(h->rear==h->size-1) return;
    h->arr[++h->rear]=mb;
    heapifyup(h);
    return;
}


meta_block* top_heap(heap* h){
    if(h->rear==-1) return NULL;
    return h->arr[0];
}