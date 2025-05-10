#ifndef THREAD
#include<stdio.h>

typedef struct thread_args{
    int *arr;
    int left, right;
} thread_args;

void swap(int *, int *);
int get_part(int *, int, int);
void *quick_sort(void *);

#endif