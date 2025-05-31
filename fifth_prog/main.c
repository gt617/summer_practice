#include<stdio.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>

extern int _sys_nerr;  // общее количество ошибок в системе
extern __const char *__const _sys_errlist[];  // Массив строк с описаниями ошибок

int main(){
    int fd = open("nonexist.txt", O_RDWR);  // Oткрываем несуществующий файл
    int i = 0;
    if(fd == -1){
        printf("Error number: %d\n", errno);  // Выводим номер ошибки (errno)
        perror("Perror");  // Выводим сообщение об ошибке через perror
        if(errno >= 0 && errno < _sys_nerr){ // Проверям, находится ли номер в диапазоне ошибок
            printf("Errlist: %s", _sys_errlist[errno]); // Выводим ошибку из системного списка
        }else{
            printf("Unknown error\n"); // Если номер вне диапазона
        }
    }else{
        printf("File nonexist.txt opend seccessufully\nFile descriptor: %d\n", fd);
        close(fd);
    }
    return 0;
}
