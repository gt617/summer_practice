#include <stdio.h>
#include"mysignal.h"

int main(){
    int choose;
    int (*matrix1)[SIZE] = malloc(SIZE * sizeof(*matrix1));
    int (*matrix2)[SIZE] = malloc(SIZE * sizeof(*matrix2));
    int (*result)[SIZE] = malloc(SIZE * sizeof(*result));

    if(!matrix1 || !matrix2 || !result){
        perror("Malloc filed");
        return 1;
    }

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
    random_fill(matrix1, matrix2);
    printf("Multiplication has started. Press Ctrl+C to show current iterators.\n");
    printf("The second Ctrl+C will terminate the program.\n");
    multiply(matrix1, matrix2, result);
    printf("Multiplication completed.\n");
    print_matrix(result);

    free(matrix1); free(matrix2); free(result);
    return 1;
}
