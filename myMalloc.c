#include<stdio.h>
#define MAX 25000

char array[MAX] = {'\0'};

struct node{
    int size;
    int status;// o if null
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

void combine(struct node *tempPtr){
    tempPtr->size=tempPtr->size+tempPtr->next->size;
    tempPtr->next=tempPtr->next->next;

        return;
}
void myFree(void * ptr){

    if(root==NULL) return ;
    

    point=root;

    struct node *pre=NULL;
    while(point){
        if ((void *)((void *)root + sizeof(struct node)) == ptr)
        {
           root->status=0;

           if(root->next->status==0)
            
            combine(root);
            return;
        }

        if((void *)((void *)point+sizeof(struct node))==ptr){ //*
            point->status=0;
            //struct node *tempPtr=point;

            if(point->next->status==0 && point->next!=NULL){
                // point->next=point->next->next;
                // point->size = point->size + point->next->size;
                combine(point);
                
                
            }
            if (pre->status == 0 && pre != NULL)
            {
                // pre->next = point->next;
                // pre->size = pre->size + point->size;
                combine(pre);
            }
            
            return;
        }
        
        pre = point;
        
        point=point->next;
    }
    return;
}


void printMyMemmory(){
    point=root;
    while(point){

        printf("Point :%p\t\n\tStatus\t:%d\n\tSize\t:%d\n\tNext\t:%p\n", point, point->status, point->size, point->next);

        point=point->next;
    }
    return;
    
}