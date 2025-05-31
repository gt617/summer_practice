#ifndef THREAD
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define SIZE 20

// Структура для аргументов потока
typedef struct thread_args{
    int *arr; // Указатель на массив
    int left, right; // Левая и правая границы
} thread_args;

void swap(int *, int *);
int get_part(int *, int, int);
void *quick_sort(void *);

#endif
