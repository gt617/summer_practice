#include "parser.h"

// Функция проверки аргументов elbrus
int elbrus_valid(const char *value){
    int i;
    for(i = 0; elbrus_value[i] != NULL; i++){
        if(strcmp(value, elbrus_value[i]) == 0){
	    return 1;
	}
    }
    return 0;
}

void help(){
    printf("SYNOPSIS: ./main [OPTIONS]... [FILE]...\n");
    printf("DESCRIPTION\n");
    printf("	-m\n");
    printf("	-c\n");
    printf("	-s\n");
    printf("	-t\n");
    printf("	--elbrus=[1c+, 2c+, 2c3, 4c, 8c, 16c]\n");
}

int check_alloc(char **array){
    if(!array){
        fprintf(stderr, "Memory error");
	free(array);
	return 1;
    }
}
