#include<stdio.h>
#include<string.h>
#include<sys/stat.h>

void print_file_stats(const char *filename, const struct stat *file_stats){
    printf("Info about: %s\n", filename);
    printf("File type: ");
    if(S_ISREG(file_stats->st_mode)){
    	printf("regular\n");
    }else if(S_ISBLK(file_stats->st_mode)){
    	printf("block device\n");
    }else if(S_ISCHR(file_stats->st_mode)){
    	printf("character device\n");
    }else if(S_ISDIR(file_stats->st_mode)){
    	printf("directory\n");
    }else{
    	printf("No such type found\n");
    }
    return NULL;
}

int main(int argc, char *argv[]){
    int i;
    if(argc < 2){
        printf("You need to pass filename\n");
	return 1;
    }

    for(i = 1; i < argc; i++){
    	struct stat file_stats;
	if(stat(argv[i], &file_stats) == -1){
	    perror("Error while getting file stats");
	}
	print_file_stats(argv[i], &file_stats);
    }
    return 0;
}	
