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
    int* arr=(int*)Malloc(sizeof(int)*5);
    student* st1=(student*)Malloc(sizeof(student));
    student* st2=(student*)Malloc(sizeof(student));
    student* st3=(student*)Malloc(sizeof(student));
    // student* st2=(student*)Malloc(3920);
    st1->id=101;
    st2->id=102;
    st3->id=103;
    st1->id=444;
    strcpy(st2->name,"siddhesh");
    strcpy(st1->name,"tanmay");
    // printf("%s %d\n",st->name,st->id);
    printf("%s %d\n",st1->name,st1->id);
    Free(st2);
    Free(st1);
    Free(st3);
    Free(arr);
    
    return 0;
}