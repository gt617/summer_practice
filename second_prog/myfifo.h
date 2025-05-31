#ifndef MYFIFO_H
#define MYFIFO_H
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#define FIFO_1 "fifo_file1"
#define FIFO_2 "fifo_file2"

void make_fifo(char *);
void clean();
void check_file(int);
void start_proc1();
void start_proc2();

#endif
