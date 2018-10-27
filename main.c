#include<stdio.h>
#include"myMalloc.h"



int main()
{

    int *p1 = (int *)(int *)myMalloc(50);
    int *p =(int *) myMalloc(40);

    int *p2 = (int *)myMalloc(90);
     int *p4 = (int *)myMalloc(110);
    // myFree(p1);
     myFree(p);
     myFree(p2);
     int *p3 = (int *)myMalloc(10);

     printMyMemmory();

     return 0;
}
