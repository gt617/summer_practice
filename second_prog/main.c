#include <stdio.h>
#include "myfifo.h"

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Wrong usage: enter 1 or 2\n");
        return 1;
    }

    make_fifo(FIFO_1);  // Создаем первый FIFO канал
    make_fifo(FIFO_2);  // Создаем второй FIFO канал
    atexit(clean);  // Регистрация clean для выполнения при завершении программы

    if(strcmp(argv[1], "1") == 0){
        start_proc1();  // Запуск первого процесса
    }else if(strcmp(argv[1], "2") == 0){
        start_proc2();  // Запуск второго процесса
    }else{
        printf("Wrong arguments\n");
        return 1;
    }
    return 0;
}
