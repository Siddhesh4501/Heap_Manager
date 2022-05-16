#include "uapi.h"

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



    return 0;
}