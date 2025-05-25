#ifndef __GNU__
#include<stdio.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>

extern const char* const sys_errlist[];
extern int sys_nerr;

int main(){
    int fd = open("nonexist.txt", O_RDWR);
    int i = 0;
    if(fd == -1){
        printf("Erroe number: %d\n", errno);
        perror("Error opening file");
        printf("Errlist: %s", sys_errlist[errno]);
    }else{
    printf("Filr somefile.txt opend seccessufully\nFile descriptor: %d\n", fd);
    close(fd);
    }
    return 0;
}
#endif