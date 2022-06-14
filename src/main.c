#include <stdio.h>
#include <string.h>
#include "mm.h"

typedef struct student // size 16 kb
{
    char name[10];
    int id;
} student;

int main()
{
    mm_init();
    // printf("%d",sizeof(student));




    // For malloc Testing
    // student* st1=Malloc(sizeof(student)*1);
    // st1->id = 12;
    // strcpy(st1->name, "siddhesh");
    // printf("%d %s\n", st1->id, st1->name);
    // student* st2=Malloc(sizeof(student)*2);
    // student* st3=Malloc(sizeof(student)*3);
    // student* st4=Malloc(sizeof(student)*4);
    // student* st5=Malloc(sizeof(student)*5);
    // student* st6=Malloc(sizeof(student)*6);
    // Free(st1);
    // Free(st3);
    // Free(st5);
    // printheap();




    // // for Free Testing
    //  student* st1=Malloc(sizeof(student)*1);
    //  student* st2=Malloc(sizeof(student)*2);
    //  student* st3=Malloc(sizeof(student)*3);
    //  student* st4=Malloc(sizeof(student)*1);
    //  // student* st5=Malloc(sizeof(student)*5);
    //  // student* st6=Malloc(sizeof(student)*6);
    //  Free(st2);
    //  Free(st1);
    //  // Free(st3);
    //  // Free(st5);
    //  // student* st7=Malloc(4496);
    //  printheap();





    // // for Calloc testing
    // student *st1 = Calloc(1,sizeof(student));;
    // student *st2 = Calloc(2,sizeof(student));
    // printf("%d %s\n",st1->id,st1->name);
    // st1->id = 12;
    // strcpy(st1->name, "siddhesh");
    // printf("%d %s\n", st1->id, st1->name);
    



    // For Realloc
    // student* st1=Malloc(sizeof(student)*10);
    // st1->id = 12;
    // strcpy(st1->name, "siddhesh");
    // printf("%d %s\n", st1->id, st1->name);
    // printheap();
    // st1=Realloc(st1,sizeof(student)*2);
    // printf("%d %s\n", st1->id, st1->name);
    // printheap();
    // st1=Realloc(st1,sizeof(student)*5);
    // printf("%d %s\n", st1->id, st1->name);
    // printheap();

    return 0;
}