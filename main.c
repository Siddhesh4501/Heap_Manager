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
    student* st=Malloc(sizeof(student));
    st->id=100;
    strcpy(st->name,"siddhesh");
    printf("%s %d",st->name,st->id);
    return 0;
}