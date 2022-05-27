#include<stdio.h>
#include<string.h>
#include "mm.h"

typedef struct emp{
    char name[10];
    int id;
}emp;

typedef struct student{
    char name[10];
    int id;
} student;


int main(){
    mm_init();
    MM_REG_STRUCT(student);
    MM_REG_STRUCT(emp);
    Iterate_over_all_structures();
    setheap();
    student* st=(student*)Malloc(sizeof(student));
    student* st1=(student*)Malloc(sizeof(student));
    student* st2=(student*)Malloc(3920);
    int* arr=(int*)Malloc(sizeof(int)*3);
    arr[0]=1;
    arr[1]=2;
    arr[2]=3;
    for(int i=0;i<3;i++)
       printf("%d ",arr[i]);
    printf("\n");
    // printheap();
    st->id=100;
    st1->id=444;
    strcpy(st->name,"siddhesh");
    strcpy(st1->name,"tanmay");
    printf("%s %d\n",st->name,st->id);
    printf("%s %d\n",st1->name,st1->id);
    return 0;
}