#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define SIZE 20

typedef struct thread_args{
    int *arr;
    int left, right;
} thread_args;

void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int get_part(int* arr, int left, int right){
    int pivot = arr[right];
    int less = left, i;

    for(i = left; i < right; i++){
        if(arr[i] <= pivot){
            swap(&arr[i], &arr[less]);
            less++;
        }
    }
    swap(&arr[less], &arr[right]);
    return less;
}

void *quick_sort(void *args){
    thread_args *cur_args = (thread_args*)args;
    int left = cur_args->left, right = cur_args->right;
    int* arr = cur_args->arr;
    if(left >= right){
        return NULL;
    }
    int pivot = get_part(arr, left, right);
    thread_args left_args = {arr, left, pivot - 1};
    thread_args right_args = {arr, pivot + 1, right};
    
    pthread_t left_thread, right_thread;
    int left_check = pthread_create(&left_thread, NULL, quick_sort, &left_args);
    int right_check = pthread_create(&right_thread, NULL, quick_sort, &right_args);
    
    if(left_check !=0 || right_check !=0){
        if(left_check == 0){
            pthread_join(left_thread, NULL);
            quick_sort(&right_args);
        }else if(right_check == 0){
            pthread_join(right_thread, NULL);
            quick_sort(&right_args);
        }else{
            quick_sort(&right_args);
            quick_sort(&left_args);
        }
    }else{
        pthread_join(left_thread, NULL);
        pthread_join(right_thread, NULL);
    }
    return NULL;
}

int main(){
    int i;
    int *arr = malloc(SIZE * sizeof(int));
    pthread_t pthread;
    srand(time(NULL));
    
    for(i = 0; i < SIZE; i++){
        arr[i] = rand() % 100;
    }
    printf("Before sort:\n");
    for(i = 0; i < SIZE; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");

    thread_args args = {arr, 0, SIZE - 1};
    if(pthread_create(&pthread, NULL, quick_sort, &args)){
        printf("Error while creating thread\n");
    }
    pthread_join(pthread, NULL);
    
    printf("After sort:\n");
    for(i = 0; i < SIZE; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
    return 0;
}