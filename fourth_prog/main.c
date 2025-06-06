#include<stdio.h>
#include"parser.h"

int main(int argc, char *argv[]){
    int opt, i;
    int report = 1;  // Флаг (на проверку аргументов)
    int elbrus_cnt = 0, mcst_cnt = 0;  // счетчик аргументов elbrus, счетчик аргусентов mcst
    int elbrus_base_size = 3;  // начальный размер массива для elbrus
    char mcst[MCST_SIZE] = {0}; // Массив для аргументов mcst
    char **elbrus_val = malloc(elbrus_base_size*sizeof(char *));  // Массив для аргументов elbrus
    check_alloc(elbrus_val);

    if(argc < 2){
        printf("Usage: %s -options\n", argv[0]);
        printf("For help enter %s -h\n", argv[0]);
        return 1;
    }
	
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
                if(!elbrus_valid(optarg)){  // Проверка валидности данных
                    printf("Error with elbrus arguments.\n");
                    free(elbrus_val);
                    return 1;
                }
                if(elbrus_cnt>=elbrus_base_size){  // Если аргументов много, массив увеличивается
                    elbrus_base_size *= 2;  // Удваиваем размер
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

    if(!report){  // Если введены неверные данные
        printf("Options are incorrect\n");
        free(elbrus_val);
        return 1;
    }

    printf("Options are correct: ");  // Вывод корректных опций
    for(i = 0; i < mcst_cnt; i++){
        printf("%c, ", mcst[i]);
    }

    for(i = 0; i < elbrus_cnt; i++){
        printf("elbrus=%s%s", elbrus_val[i], (i == elbrus_cnt-1) ? "":", ");
    }
	
    printf(" ");
    if(optind < argc){  // Вывод неопциональных аргументов
        printf("non-options: ");
        for(i = optind; i < argc; i++){
            printf("%s%s", argv[i], (i == argc-1) ? "":", ");
        }
    }
    printf("\n");
    free(elbrus_val);
    return 0;
}
