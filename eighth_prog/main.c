#include <stdio.h>
#include "mysignal.h"

int main(){
    int choose;
    // Выделяем память под матрицы размером SIZE*SIZE
    int (*matrix1)[SIZE] = malloc(SIZE * sizeof(*matrix1));
    int (*matrix2)[SIZE] = malloc(SIZE * sizeof(*matrix2));
    int (*result)[SIZE] = malloc(SIZE * sizeof(*result));

    // Проверка выделения памяти
    if(!matrix1 || !matrix2 || !result){
        perror("Malloc filed");
        return 1;
    }

    printf("Choose signal hendler 1.signal(), 2.sigaction(). Enter 1 or 2:\n");
    scanf("%d", &choose);
    // Установка обработчика сигнала в зависимости от выбора
    if(choose == 1){
        signal(SIGINT, signal_handler);  // Используем стандартну функцию signal
    }else if(choose == 2){  // Используем современную sigaction
        struct sigaction act;
        act.sa_sigaction = sigaction_handler;  // Устанавливаем собственный обработчик
        sigemptyset(&act.sa_mask);  // Очищаем маску сигналов
        act.sa_flags = SA_SIGINFO;  // Флаг для использования sa_sigaction
        sigaction(SIGINT, &act, NULL);  // Устанавливаем обработчик для SIGINT
    }else{
        printf("You`r wrong, repeat please!\n");
        return 1;
    }

    random_fill(matrix1, matrix2);  // Заполнение матриц случайными числами
    printf("Multiplication has started. Press Ctrl+C to show current iterators.\n");
    printf("The second Ctrl+C will terminate the program.\n");
    multiply(matrix1, matrix2, result);  // Умножение матриц
    printf("Multiplication completed.\n");

    free(matrix1);
    free(matrix2);
    free(result);
    return 0;
}
