#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define SIZE 20
#define DEPTH 3

typedef struct thread_args{
    int *arr;
    int left, right;
    int depth;
} thread_args;

void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int get_part(thread_args* args){
    int left = args->left, right = args->right;
    if(left >= right) return left;
    int pivot = args->arr[right];
    int less = left, i;

    for(i = left; i < right; i++){
        if(args->arr[i] <= pivot){
            swap(&(args->arr[i]), &(args->arr[less]));
            less++;
        }
    }
    swap(&(args->arr[less]), &(args->arr[right]));
    return less;
}

void *quick_sort(void *args){
    thread_args *cur_args = (thread_args*)args;
    int left = cur_args->left, right = cur_args->right;
    if(left < right){
        int pivot = get_part(cur_args);
        thread_args left_args = {cur_args->arr, left, pivot - 1, cur_args->depth + 1};
        thread_args right_args = {cur_args->arr, pivot + 1, right, cur_args->depth + 1};

        if(cur_args->depth < DEPTH){
            pthread_t left_thread, right_thread;
            pthread_create(&left_thread, NULL, quick_sort, &left_args);
            pthread_create(&right_thread, NULL, quick_sort, &right_args);
            pthread_join(left_thread, NULL);
            pthread_join(right_thread, NULL);
        } else{
            quick_sort(&left_args);
            quick_sort(&right_args);
        }
    }
    return NULL;
}

int main(){
    int i;
    int *arr = malloc(SIZE * sizeof(int));
    pthread_t pthread;
    
    for(i = 0; i < SIZE; i++){
        arr[i] = rand() % 100;
    }
    printf("Before sort:\n");
    for(i = 0; i < SIZE; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    thread_args args = {arr, 0, SIZE - 1, 0};
    pthread_create(&pthread, NULL, quick_sort, &args);
    pthread_join(pthread, NULL);

    printf("After sort:\n");
    for(i = 0; i < SIZE; i++){
        printf("%d ", arr[i]);
    }
    free(arr);
    return 0;
}