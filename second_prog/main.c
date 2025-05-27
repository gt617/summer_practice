#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#define FIFO_1 "fifo_file1"
#define FIFO_2 "fifo_file2"

void start_proc1(int fd_write, int fd_read){
    char arr1[80];
    while(1){
        fgets(arr1, 80, stdin);
        write(fd_write, arr1, strlen(arr1)+1);

        read(fd_read, arr1, sizeof(arr1));
        printf("Proc2: %s\n", arr1);
    }
    close(fd_read);
    close(fd_write);
}

void start_proc2(int fd_write, int fd_read){
    char arr1[80];

    while(1){
        read(fd_read, arr1, sizeof(arr1));
        printf("Proc1: %s\n", arr1);
        fgets(arr1, 80, stdin);
        write(fd_write, arr1, strlen(arr1)+1);
    }
    close(fd_read);
    close(fd_write);
}

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Wrong usage: enter 1 or 2\n");
        return 1;
    }

    int fd_write, fd_read;
    mkfifo(FIFO_1, 0666);
    mkfifo(FIFO_2, 0666);

    if(strcmp(argv[1], "1") == 0){
        fd_write = open(FIFO_1, O_WRONLY);
        fd_read = open(FIFO_2, O_RDONLY);
        start_proc1(fd_write, fd_read);
    }else if(strcmp(argv[1], "2") == 0){
        fd_write = open(FIFO_2, O_WRONLY);
        fd_read = open(FIFO_1, O_RDONLY);
        start_proc2(fd_write, fd_read);
    }else{
        printf("Wrong arguments\n");
        return 1;
    }
    unlink(FIFO_1);
    unlink(FIFO_2);
    return 0;
}