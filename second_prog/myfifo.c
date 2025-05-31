#include <stdio.h>
#include "myfifo.h"

// Создание FIFO канала
void make_fifo(char *filename){
    // Создаем, если файл не существует
    if(mkfifo(filename, 0666) == -1 && errno != EEXIST){
        perror("Mkfifo");
        exit(EXIT_FAILURE);
    }
}

// Удаление FIFO файлов
void clean(){
    unlink(FIFO_1);
    unlink(FIFO_2);
}

// Проверка успешности открытия файла
void check_file(int fd){
    if(fd == -1){
        perror("Open fifo");
        exit(EXIT_FAILURE);
    }
}

// Процесс 1 (отправитель)
void start_proc1(){
    char buf[80];
    int fd_write, fd_read;  // Индексные дескрипторы

    fd_write = open(FIFO_1, O_WRONLY);  // Открываем FIFO для записи в процесс 2
    fd_read = open(FIFO_2, O_RDONLY);  // Открываем FIFO для чтения в процесс 2
    check_file(fd_write);
    check_file(fd_read);
    
    printf("Pocess 1 has started. Enter 'quit' to quit\n");
    while(1){
        printf("> ");
        fgets(buf, 80, stdin);  //  Чтение ввода пользователя
        buf[strcspn(buf, "\n")] = '\0';  // Удаление \n
        write(fd_write, buf, strlen(buf)+1);  // Отправка сообщения процессу 2
        if(strcmp(buf, "quit") == 0){
            break;
        }

        read(fd_read, buf, sizeof(buf));  // Чтение ответа от процесса 2
        if(strcmp(buf, "quit") == 0){
            break;
        }
        printf("Proc2: %s\n", buf);
    }
    close(fd_read);
    close(fd_write);
}

// Процесс 2 (получатель)
void start_proc2(){
    char buf[80];
    int fd_write, fd_read;
    
    fd_read = open(FIFO_1, O_RDONLY);  // Открываем FIFO для чтения в процесс 2
    fd_write = open(FIFO_2, O_WRONLY);  // Открываем FIFO для записи в процесс 2
    check_file(fd_write);
    check_file(fd_read);

    printf("Process 2 has started. Waiting for message\n");
    while(1){
        read(fd_read, buf, sizeof(buf));
        printf("Proc1: %s\n", buf);
        if(strcmp(buf, "quit") == 0){
            break;
        }
       
        printf("> ");
        fgets(buf, 80, stdin);
        buf[strcspn(buf, "\n")] = '\0';
        write(fd_write, buf, strlen(buf)+1);
        if(strcmp(buf, "quit") == 0){
            break;
        }
    }
    close(fd_read);
    close(fd_write);
}
