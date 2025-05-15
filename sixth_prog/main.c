#include<stdio.h>
#include<sys/stat.h>
#include<time.h>

void print_file_stats(const char *filename, const struct stat *file_stat){
    printf("=================Info about: %s=================\n", filename);
    printf("File type: ");

    // Определене типа файла
    if(S_ISREG(file_stat->st_mode)){
    	printf("regular\n");
    }else if(S_ISBLK(file_stat->st_mode)){
    	printf("block device\n");
    }else if(S_ISCHR(file_stat->st_mode)){
    	printf("character device\n");
    }else if(S_ISDIR(file_stat->st_mode)){
    	printf("directory\n");
    }else{
    	printf("No such type found\n");
    }

    printf("File size: %ld byte\n", file_stat->st_size);
    printf("Inode number: %ld\n", file_stat->st_ino);
    printf("Link count: %ld\n", file_stat->st_nlink);
    printf("Access rights: %o\n", file_stat->st_mode & 0777);
    printf("User ID: %d\n", file_stat->st_uid);
    printf("Group ID: %d\n", file_stat->st_gid);
    printf("Last access timestamp: %s", ctime(&file_stat->st_atime));
    printf("Last modification timestamp: %s", ctime(&file_stat->st_mtime));
    printf("Last status change timestamo: %s\n", ctime(&file_stat->st_ctime));
}

int main(int argc, char *argv[]){
    int i;
    if(argc < 2){
        printf("You need to pass filename\n");
	return 1;
    }

    // Проход по всем переданным файлам
    for(i = 1; i < argc; i++){
    	struct stat file_stat;
	    if(stat(argv[i], &file_stat) == -1){
	        perror("Error while getting file stats");
	    }
	    print_file_stats(argv[i], &file_stat);
    }
    return 0;
}	
