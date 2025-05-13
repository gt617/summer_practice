#include<stdio.h>
#include"parser.h"

int main(int argc, char *argv[]){
    int opt, i;
	int report = 1, elbrus_cnt = 0, mcst_cnt = 0, elbrus_base_size = 3;
    char mcst[MCST_SIZE] = {0};
    
    char **elbrus_val = malloc(elbrus_base_size*sizeof(char *));
    check_alloc(elbrus_val);

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
		    		free(elbrus_val);
		    		return 1;
				}
				if(elbrus_cnt>=elbrus_base_size){
					elbrus_base_size *= 2;
					char **tmp = realloc(elbrus_val, elbrus_base_size*sizeof(char *));
					check_alloc(tmp);
					elbrus_val = tmp;
				}
						elbrus_val[elbrus_cnt++] = optarg;
				break;
				case 'h':
				help();
					free(elbrus_val);
				return 0;
				case '?':
				report = 0;
				break;
				default:
				report = 0;
		}
	}
    if(!report){
    	printf("Options are incorrect\n");
		free(elbrus_val);
		return 1;
    }

    printf("Options are correct: ");
    for(i = 0; i < mcst_cnt; i++){
		printf("%c, ", mcst[i]);
    }

    for(i = 0; i < elbrus_cnt; i++){
    	printf("elbrus=%s%s", elbrus_val[i], (i == elbrus_cnt-1) ? "":", ");
    }
	
    printf(" ");
    if(optind < argc){
        printf("non-options: ");
        for(i = optind; i < argc; i++){
            printf("%s%s", argv[i], (i == argc-1) ? "":", ");
        }
    }
    printf("\n");
    free(elbrus_val);
    return 0;
}


