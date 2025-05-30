#include <stdio.h>
#include"mysignal.h"

volatile sig_atomic_t signal_count = 0;
volatile sig_atomic_t i_cur = 0;
volatile sig_atomic_t j_cur = 0;

void signal_handler(int sig){
    if(sig == SIGINT){
        signal_count++;
        printf("\nSIGINT was recived. Current iterators: matrix1[%d][%d], matrix2[%d][%d]\n", i_cur, j_cur, j_cur, i_cur);
        if(signal_count == 1){
            signal(SIGINT, SIG_DFL);
        }
    }
}

void sigaction_handler(int sig, siginfo_t *info, void *context){
    if(sig == SIGINT){
        signal_count++;
        printf("\nSIGINT was recived. Current iterators: matrix1[%d][%d], matrix2[%d][%d]\n", i_cur, j_cur, j_cur, i_cur);
        if(signal_count == 1){
            struct sigaction act;
            act.sa_handler = SIG_DFL;
            sigemptyset(&act.sa_mask);
            act.sa_flags = 0;
            sigaction(SIGINT, &act, NULL);
        }
    }
}

void random_fill(int matrix1[SIZE][SIZE], int matrix2[SIZE][SIZE]){
    int i, j;
    srand(time(NULL));
    for(i = 0; i < SIZE; i++){
        for(j=0; j < SIZE; j++){
            matrix1[i][j] = rand() % 100;
            matrix2[i][j] = rand() % 100;
        }
    }
}

void print_matrix(int matrix[SIZE][SIZE]){
    int i, j;
    for(i =0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            printf(j == SIZE-1 ? "%d\n" : "%d ", matrix[i][j]);
        }
    }
}

void multiply(int matrix1[SIZE][SIZE], int matrix2[SIZE][SIZE], int result[SIZE][SIZE]){
    int i, j, k;
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            result[i][j] = 0;
            for(k = 0; k < SIZE; k++){
                result[i][j] += matrix1[i][k]* matrix2[k][j];
                i_cur = i;
                j_cur = j;
            }
            sleep(1);
        }
    }
}
