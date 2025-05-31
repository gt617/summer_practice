#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

// Функция копирования файла
void copy_file(char* main_file, char *filename){
    int fd, main_fd, sz_read;
    char buff[256];  // Буфер для чтения/записи данных

    fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);  // Открываем файл для записи
    main_fd = open(main_file, O_RDONLY);  // Открываем исходный файл

    while((sz_read = read(main_fd, buff, 256)) > 0){
        // Проверяем, что прочитано столько же байтов, сколько прочитано
        if(write(fd, buff, sz_read) != sz_read){
            exit(EXIT_FAILURE);
        }
    }

    close(fd);
    close(main_fd);
}

// Функция вывода содержимого файла
void print_file(char *filename){
    FILE *file;
    char buff[256];

    file = fopen(filename, "r");

    printf("---------------------%s---------------------\n", filename);
    while(fgets(buff, 256, file) != NULL){
        printf("%s", buff);
    }
    printf("\n");
    fclose(file);
}

int main(int argc, char *argv[]){
    pid_t pid;  // Для хранение ID процесса
    char buff[256];
    int main_fd;

    if(argc != 2){
        perror("Usage: filename");
        return 1;
    }

    // Создаем новый процесс
    switch(pid = fork()){
    case -1:
        perror("Fork");
        return 1;
    case 0:  // Код, выполняемый в дочернем процессе
        copy_file(argv[1], "child.txt");
        print_file("child.txt");
        exit(0);  // Завершем дочерний процесс
    default:  // Код, выполняемый в родительском процессе
        copy_file(argv[1], "parent.txt");
        wait(0);  // Ждем завершения дочернего процесса
        print_file("parent.txt");
    }
    return 0;
}
