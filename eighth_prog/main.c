#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define SIZE 2

void signal_hendler(int sif){
    
}

void random_fill(int *matrix){
    int i, j;
    srand(time(NULL));
    for(i = 0; i < SIZE; i++){  //Заполнение массива случайными числами
        for(j=0; j < SIZE; j++){
            matrix[i * SIZE + j] = rand() % 100;
        }
    }
}

void print_matrix(int *matrix){
    int i, j;
    for(i =0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            printf(j == SIZE-1 ? "%d\n" : "%d ", matrix[i * SIZE + j]);
        }
    }
}

void multiplay(int *matrix1, int *matrix2){
    int i, j, k, res;
    for(i =0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            res = 0;
            for(k = 0; k < SIZE; k++){
                sleep(1);
                res += matrix1[i * SIZE + k] * matrix2[k*SIZE + j];
            }
            printf(j == SIZE-1 ? "%d\n" : "%d ", res);
        }
    }
}

int main(){
    int matrix1[SIZE][SIZE] = {0}, matrix2[SIZE][SIZE] = {0};

    random_fill(*matrix1);
    random_fill(*matrix2);
    print_matrix(*matrix1);
    print_matrix(*matrix2);
    multiplay(*matrix1, *matrix2);
    return 1;
}