#include<stdio.h>
#include"myMalloc.h"



int main()
{

    int *p1 = (int *)(int *)myMalloc(50);
    int *p =(int *) myMalloc(40);

    int *p2 = (int *)myMalloc(90);
     myFree(p1);

    // int *p3 = (int *)myMalloc(10);
    // int *p4 = (int *)myMalloc(110);

    printMyMemmory();

    return 0;
}
