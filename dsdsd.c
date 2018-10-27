#include <stdio.h>
#include <stdlib.h>
#include "MyMalloc.h"

char Memory[25000];

struct Segment
{

    char isFree;
    int size;
    struct Segment *next;
};

static struct Segment *initial_segment = NULL;
static struct Segment *pointer;
static struct Segment *pre;
static struct Segment *temp;

static void split_segment(struct Segment *ptr, int size)
{

    if (((void *)(((temp = (struct Segment *)((void *)ptr + sizeof(struct Segment) + size)) + 1)) >= (void *)(&Memory[25000])))
        return;

    temp->isFree = 'T';
    temp->size = ptr->size - sizeof(struct Segment) - size;

    if (temp->size > sizeof(struct Segment) + 1)
    {
        temp->next = ptr->next;
        ptr->next = temp;

        ptr->size = size;
    }

    return;
}

static void initializer()
{

    initial_segment = (struct Segment *)Memory;

    initial_segment->isFree = 'T';
    initial_segment->size = sizeof(Memory) - sizeof(struct Segment);
    initial_segment->next = NULL;

    return;
}

void *MyMalloc(int size)
{

    if (initial_segment == NULL)
        initializer();

    if (size <= 0)
        return NULL;

    pointer = initial_segment;

    while (pointer)
    {
        if (pointer->isFree == 'T' && pointer->size >= size)
        {
            if (pointer->size > size)
                split_segment(pointer, size);
            pointer->isFree = 'F';

            return ((void *)((void *)pointer + sizeof(struct Segment)));
        }

        pointer = pointer->next;
    }
    return NULL;
}

static void combine_segment(struct Segment *ptr)
{

    ptr->size = ptr->size + sizeof(struct Segment) + ptr->next->size;

    ptr->next = ptr->next->next;

    return;
}

void MyFree(void *fre)
{

    if (initial_segment == NULL)
        return;

    pointer = initial_segment;
    pre = NULL;
    while (pointer)
    {
        if (((void *)((void *)pointer + sizeof(struct Segment))) == fre)
        {

            pointer->isFree = 'T';

            if ((pointer->next != NULL) && (pointer->next->isFree == 'T'))
                combine_segment(pointer);

            if ((pre != NULL && pre->isFree == 'T'))
                combine_segment(pre);

            return;
        }

        pre = pointer;
        pointer = pointer->next;
    }

    return;
}

void print()
{

    printf("My heap\n");
    pointer = initial_segment;

    while (pointer)
    {
        printf("Meta:%p\t(%c, %d, %p)\n", pointer, pointer->isFree, pointer->size, pointer->next);
        pointer = pointer->next;
    }

    return;
}