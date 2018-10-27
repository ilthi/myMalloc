#include<stdio.h>
#define MAX 25000

char array[MAX] = {'\0'};

struct node{
    int size;
    int status;
    struct node * next;
    //struct node * prev;
};

struct node * root=NULL;
struct node * temp;
struct node * point;

void splitSegment(struct node *ptr, int size){

    if (((void *)(((temp = (struct node *)((void *)ptr + sizeof(struct node) + size)) + 1)) >= (void *)(&array[25000]))){
        return;
    }
    
    
    temp->status=0;
    temp->size=ptr->size-sizeof(struct node)-size;
    
    //printf("Assigned %d\n\n",size);

    temp->next = ptr->next;
    ptr->next=temp;
    ptr->size=size;

    return;
    
}

void * myMalloc(int size){

    if(root==NULL){
        root=(struct node *)array;
        root->status=0;
        root->next=NULL;
        root->size=sizeof(array)-sizeof(struct node);
        //root->prev=NULL;

    }
    
    if(size<=0){
        return NULL;
    }else{
  
        point=root;
        while(point){
            
            if (size <= point->size && point->status==0){
               if(point->size>size){
                  // printf("point %d\n", point->size);
                   splitSegment(point, size);
                
                   point->status = 1;

                   return ((void *)((sizeof(struct node)+(void *)point)));

               }
            }

            point = point->next;
        }
        
    }
    return NULL;
    
}
void myFree(void * ptr){

    if(root==NULL) return ;
    point=root;
    struct node *pre;
    while(point){
        pre=point;
        if(point+sizeof(struct node)==ptr){
            point->status=0;

            pre->next=point->next;
            pre->size=pre->size+point->size;
            

        }
        
        point=point->next;
    }
    return;
}


void printMyMemmory(){
    point=root;
    while(point){

        printf("Meta:%p\t(%d, %d, %p)\n", point, point->status, point->size, point->next);
        
        point=point->next;
    }
    return;
    
}