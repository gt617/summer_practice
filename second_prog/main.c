#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#define FIFO_1 "fifo_file1"
#define FIFO_2 "fifo_file2"

void make_fifo(char *filename){
    if(mkfifo(filename, 0666) == -1){
        perror("Mkfifo");
        exit(EXIT_FAILURE);
    }
}

void clean(){
    unlink(FIFO_1);
    unlink(FIFO_1);
}

void check_file(int fd){
    if(fd == -1){
        perror("Open fifo");
        exit(EXIT_FAILURE);
    }
}

void start_proc1(){
    char buf[80];
    int fd_write, fd_read;

    fd_write = open(FIFO_1, O_WRONLY);
    fd_read = open(FIFO_2, O_RDONLY);
    check_file(fd_write);
    check_file(fd_read);
    
    printf("Pocess 1 has started. Enter 'quit' toquit\n");
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

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Wrong usage: enter 1 or 2\n");
        return 1;
    }
    make_fifo(FIFO_1);
    make_fifo(FIFO_2);
    atexit(clean);

    if(strcmp(argv[1], "1") == 0){
        start_proc1();
    }else if(strcmp(argv[1], "2") == 0){
        start_proc2();
    }else{
        printf("Wrong arguments\n");
        return 1;
    }
    return 0;
}