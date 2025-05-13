#ifndef PARSER_H
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<getopt.h>
#define MCST_SIZE 5

static const char *elbrus_value[] = {
    "1c+", "2c+", "2c3", "4c", "8c", "16c", NULL};

static struct option long_option[] = {
    {"elbrus", 1, 0, 'e'},
    {"help", 0, 0, 'h'},
    {0, 0, 0, 0}
};

int elbrus_valid(const char *);
void help();
int check_alloc(char **);

#endif