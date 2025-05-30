#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#define SIZE 1000

int signal_count = 0;
int i_cur = 0;
int j_cur = 0;

void signal_handler(int sig){
    if(sig == SIGINT){
        signal_count++;
        printf("\nSIGIN was recived. Current iterators: matrix1[%d][%d], matrix2[%d][%d]\n", i_cur, j_cur, j_cur, i_cur);
        if(signal_count == 1){
            signal(SIGINT, SIG_DFL);
        }
    }
}

void sigaction_handler(int sig, siginfo_t *info, void *context){
    if(sig == SIGINT){
        signal_count++;
        printf("\nSIGIN was recived. Current iterators: matrix1[%d][%d], matrix2[%d][%d]\n", i_cur, j_cur, j_cur, i_cur);
        if(signal_count == 1){
            struct sigaction act;
            act.sa_handler = SIG_DFL;
            sigemptyset(&act.sa_mask);
            act.sa_flags = 0;
            sigaction(SIGINT, &act, NULL);
        }
    }
}

void random_fill(int *matrix1, int *matrix2){
    int i, j;
    srand(time(NULL));
    for(i = 0; i < SIZE; i++){
        for(j=0; j < SIZE; j++){
            matrix1[i * SIZE + j] = rand() % 100;
            matrix2[i * SIZE + j] = rand() % 100;
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

void multiply(int *matrix1, int *matrix2, int *result){
    int i, j, k;
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            result[i * SIZE + j] = 0;
            for(k = 0; k < SIZE; k++){
                result[i * SIZE + j] += matrix1[i * SIZE + k] * matrix2[k*SIZE + j];
                i_cur = i;
                j_cur = j;
            }
            sleep(1);
        }
    }
}

int main(){
    int choose;
    int matrix1[SIZE][SIZE] = {0}, matrix2[SIZE][SIZE] = {0};
    int result[SIZE][SIZE] = {0};

    printf("Choose signal hendler 1.signal(), 2.sigaction(). Enter 1 or 2:\n");
    scanf("%d", &choose);
    if(choose == 1){
        signal(SIGINT, signal_handler);
    }else if(choose == 2){
        struct sigaction act;
        act.sa_sigaction = sigaction_handler;
        sigemptyset(&act.sa_mask);
        act.sa_flags = SA_SIGINFO;
        sigaction(SIGINT, &act, NULL);
    }else{
        printf("You`r wrong, repeat please!\n");
        return 1;
    }
    random_fill(*matrix1, *matrix2);
    printf("Multiplication has started. Press Ctrl+C to show current iterators.\n");
    printf("The second Ctrl+C will terminate the program.\n");
    multiply(*matrix1, *matrix2, *result);
    printf("Multiplication completed.\n");
    print_matrix(*result);
    return 1;
}