#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<getopt.h>
#define MCST_SIZE 5

const char *elbrus_value[] = {"1c+", "2c+", "2c3", "4c", "8c", "16c", NULL};

static struct option long_option[] = {
    {"elbrus", 1, 0, 'e'},
    {"help", 0, 0, 'h'},
    {0, 0, 0, 0}
};

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

int main(int argc, char *argv[]){
    int opt, i, point, elbrus_cnt = 0, mcst_cnt = 0;
    char mcst[MCST_SIZE] = {0};
    int elbrus_base_size = 3;
    char **elbrus_values = malloc(elbrus_base_size*sizeof(char *));

    while((opt = getopt_long(argc, argv, "mcste:h", long_option, NULL)) != -1){
        switch(opt){
	    case 'm':
		mcst[mcst_cnt++] = 'm';
		break;
	    case 'c':
		mcst[mcst_cnt++] = 'c';
		break;
	    case 's':
		mcst[mcst_cnt++] = 's';
		break;
	    case 't':
		mcst[mcst_cnt++] = 't';
		break;
	    case 'e':
		if(!elbrus_valid(optarg)){
		    printf("Error with elbrus arguments.\n");
		    return 1;
		}
		if(elbrus_cnt>=elbrus_base_size){
		    elbrus_base_size *= 2;
		    char **tmp = realloc(elbrus_values, elbrus_base_size*sizeof(char *));
		    elbrus_values = tmp;
		}
                elbrus_values[elbrus_cnt++] = optarg;
		break;
	    case 'h':
		help();
		free(elbrus_values);
		return 0;
	    case '?':
		fprintf(stderr, "Options are incorrect:");
		free(elbrus_values);
		return 1;
	    default:
		fprintf(stderr, "Not found\n");
		free(elbrus_values);
		return 1;
	}
    }

    printf("Options are correct: ");
    for(i = 0; i < mcst_cnt; i++){
	printf("%c, ", mcst[i]);
    }
    for(i = 0; i < elbrus_cnt; i++){
    	printf("elbrus=%s%s", elbrus_values[i], (i == elbrus_cnt-1) ? "":", ");
    }
    printf(" ");
    if(optind < argc){
        printf("non-options: ");
        for(i = optind; i < argc; i++){
            printf("%s%s", argv[i], (i == argc-1) ? "":", ");
        }
    }
    printf("\n");
    free(elbrus_values);
    return 0;
}


