#include<stdio.h>
#include"thread.h"

int main(){
    int i;
    int *arr = malloc(SIZE * sizeof(int));
    pthread_t pthread;
    srand(time(NULL));
    
    for(i = 0; i < SIZE; i++){  //Заполнение массива случайными числами
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
