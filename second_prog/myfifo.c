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
    unlink(FIFO_1);
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
    int fd_write, fd_read;

    fd_write = open(FIFO_1, O_WRONLY);
    fd_read = open(FIFO_2, O_RDONLY);
    check_file(fd_write);
    check_file(fd_read);
    
    printf("Pocess 1 has started. Enter 'quit' to quit\n");
    while(1){
        printf("> ");
        fgets(buf, 80, stdin);
        buf[strcspn(buf, "\n")] = '\0';
        if(strcmp(buf, "quit") == 0){
            break;
        }
        write(fd_write, buf, strlen(buf)+1);

        read(fd_read, buf, sizeof(buf));
        printf("Proc2: %s\n", buf);
    }
    close(fd_read);
    close(fd_write);
}

// Процесс 2 (получатель)
void start_proc2(){
    char buf[80];
    int fd_write, fd_read;
    
    fd_read = open(FIFO_1, O_RDONLY);
    fd_write = open(FIFO_2, O_WRONLY);
    check_file(fd_write);
    check_file(fd_read);

    printf("Process 2 has started. Waiting for message\n");
    while(1){
        read(fd_read, buf, sizeof(buf));
        printf("Proc1: %s\n", buf);
       
        fgets(buf, 80, stdin);
        buf[strcspn(buf, "\n")] = '\0';
        if(strcmp(buf, "quit") == 0){
            break;
        }
        write(fd_write, buf, strlen(buf)+1);
    }
    close(fd_read);
    close(fd_write);
}
