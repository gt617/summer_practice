#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

void copy_file(char* main_file, char *filename){
    int fd, main_fd, sz_read;
    char buff[256];
    fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    main_fd = open(main_file, O_RDONLY);
    while((sz_read = read(main_fd, buff, 256)) > 0){
        if(write(fd, buff, sz_read) != sz_read){
            exit(EXIT_FAILURE);
        }
    }
    close(fd);
    close(main_fd);
}

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
    pid_t pid;
    char buff[256];
    int main_fd;

    if(argc != 2){
        perror("Usage: filename");
        return 1;
    }

    switch(pid = fork()){
    case -1:
        perror("Fork");
        return 1;
    case 0:
        copy_file(argv[1], "child.txt");
        print_file("child.txt");
        exit(0);
    default:
        copy_file(argv[1], "parent.txt");
        wait(0);
        print_file("parent.txt");
    }
    return 0;
}