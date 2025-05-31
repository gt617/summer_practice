#ifndef MYSIGNAL_H
#define MYSIGNAL_H
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#define SIZE 1000

// Глобальные атомарные переменные для безопасного доступа из обработчиков сигналов
extern volatile sig_atomic_t signal_count;  // Счетчик сигналов SIGINT
extern volatile sig_atomic_t i_cur;  // Текущий итератор
extern volatile sig_atomic_t j_cur;  // Текущий итератор

void signal_handler(int);
void sigaction_handler(int, siginfo_t *, void *);
void random_fill(int [SIZE][SIZE], int [SIZE][SIZE]);
void multiply(int [SIZE][SIZE], int [SIZE][SIZE], int [SIZE][SIZE]);
void print_matrix(int [SIZE][SIZE]);

#endif
