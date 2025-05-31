#include<stdio.h>
#include"thread.h"

// Обмен значениями
void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// Разделение массива на части
int get_part(int *arr, int left, int right){
    int pivot = arr[right];  // Опорный элемент
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

// Функция быстрой сортировки
void *quick_sort(void *args){
    thread_args *cur_args = (thread_args*)args;
    int left = cur_args->left, right = cur_args->right;
    int* arr = cur_args->arr;
    
    // Если границы сошлись, возвращаем NULL
    if(left >= right){
        return NULL;
    }
    int pivot = get_part(arr, left, right);  // Получаем индекс опорного элемента и разделяем массив
    thread_args left_args = {arr, left, pivot - 1};
    thread_args right_args = {arr, pivot + 1, right};
    
    pthread_t left_thread, right_thread;  // Создание потоков для сортировки левой и правой частей
    int left_check = pthread_create(&left_thread, NULL, quick_sort, &left_args);
    int right_check = pthread_create(&right_thread, NULL, quick_sort, &right_args);
    
    if(left_check !=0 || right_check !=0){
        if(left_check == 0){
            pthread_join(left_thread, NULL);  // Если левый поток создан, ждем его завершения
            quick_sort(&right_args);  // Правая часть сортеруется в текущем потоке
        }else if(right_check == 0){
            pthread_join(right_thread, NULL);  // Если правый поток создан, ждем его завершения
            quick_sort(&left_args);  // Левая часть сортируется в текущем потоке
        }else{  // Если оба потока не создались, сортируются обе части в текущем
            quick_sort(&right_args);
            quick_sort(&left_args);
        }
    }else{  // Если оба потока созданы, ждем их завершения
        pthread_join(left_thread, NULL);
        pthread_join(right_thread, NULL);
    }
    return NULL;
}
