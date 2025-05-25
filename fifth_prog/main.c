#include<stdio.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>

extern int _sys_nerr;
extern __const char *__const _sys_errlist[];

int main(){
    int fd = open("nonexist.txt", O_RDWR);
    int i = 0;
    if(fd == -1){
        printf("Error number: %d\n", errno);
        perror("Perror:");
        if(errno >= 0 && errno < _sys_nerr){
            printf("Errlist: %s", _sys_errlist[errno]);
        }else{
            printf("Unknown error\n");
        }
    }else{
    printf("File nonexist.txt opend seccessufully\nFile descriptor: %d\n", fd);
    close(fd);
    }
    return 0;
}
