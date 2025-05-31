#include<stdio.h>
#include"thread.h"

int main(){
    int i;
    int *arr = malloc(SIZE * sizeof(int));
    pthread_t pthread; // Переменная для идентификатора потока
    srand(time(NULL));
    
    for(i = 0; i < SIZE; i++){  // Заполнение массива случайными числами от 0 до 99
        arr[i] = rand() % 100;
    }
    printf("Before sort:\n");
    for(i = 0; i < SIZE; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");

    thread_args args = {arr, 0, SIZE - 1};
    // Создаем новый поток, который будет выполнять quick_sort с аргументами args
    if(pthread_create(&pthread, NULL, quick_sort, &args)){
        printf("Error while creating thread\n");
    }
    pthread_join(pthread, NULL); // Ожидаем завершения созданного потока
    
    printf("After sort:\n");
    for(i = 0; i < SIZE; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    free(arr);
    return 0;
}
