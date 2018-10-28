 #include<stdio.h>
#include"myMalloc.h"



int main()
{

    int *p1 = (int *)(int *)myMalloc(20000);
     int *p =(int *) myMalloc(40);

    myFree(p1);
    int *p2 = (int *)myMalloc(90);
    
    //myFree(p);
    //  int *p4 = (int *)myMalloc(110);
    //  myFree(p2);
    //  int *p3 = (int *)myMalloc(10);
    //  int *p5 = (int *)myMalloc(18);

    
     printMyMemmory();

     return 0;
}
