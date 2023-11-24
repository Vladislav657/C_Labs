#include <stdio.h>
#include <string.h>
#include <stdlib.h>


double operate_double(double a, double b, char op){
    if(op == '+') return a + b;
    else if (op == '-') return a - b;
    else if (op == 'x') return a * b;
    else if (op == '/') return a / b;
    return 0;
}


int operate_int(int a, int b, char op){
    if(op == '+') return a + b;
    else if (op == '-') return a - b;
    else if (op == 'x') return a * b;
    else if (op == '/') return a / b;
    else if (op == '%') return a % b;
    return 0;
}


int contains(char *str, char ch){
    for (int i = 0; i < strlen(str); ++i) {
        if(str[i] == ch) return 1;
    }
    return 0;
}


int isDigit(char *str){
    int dot_count = 0;
    if (contains("+-1234567890.", str[0]) == 0) return 0;
    if (str[0] == '.') dot_count++;
    for (int i = 1; i < strlen(str); ++i) {
        if (str[i] == '.') dot_count++;
        if(contains("1234567890.", str[i]) == 0) return 0;
    }
    if(dot_count <= 1) return 1;
    return 0;
}


void printTable(){
    printf("%s", "\nТип данных\tРазмер (в байтах)\n");
    printf("char\t\t%llu\n", sizeof(char));
    printf("int\t\t%llu\n", sizeof(int));
    printf("long\t\t%llu\n", sizeof(long));
    printf("float\t\t%llu\n", sizeof(float));
    printf("double\t\t%llu\n", sizeof(double));
    printf("long double\t%llu\n", sizeof(long double));
#if __STDC_VERSION__ > 199912
    printf("bool\t\t%llu\n", sizeof(_Bool));
#endif
}


void printHelp(){
    printf("%s", "\nфлаг -t (--table) - выдает в табличном виде размеры всех простых типов языка.\n\n"
                 "флаг -c (--calc) арифметическое выражение расчитывает простое арифметическое "
                 "выражение вида «число операция число»\n(числа целые и вещественные)\n"
                 "поддерживаемые операции: для целых - '+, -, x, /, %'; для вещественных - '+, -, x, /'\n\n"
                 "флаги к команде -с (--calc) изменяют формат вывода (писать после арифметического выражения)\n"
                 "-x (--hex) ответ в 16-ричном формате (по умолчанию в десятичном, работает для положительных целых);\n"
                 "-i (--int) входные числа целые (по умолчанию вещественные)\n");
}


void printWrong(){
    printf("\nввод не соответствует командам, воспользуйтесь справкой -h (--help)\n");
}


void printTask(){
    printf("\nЭто мини-калькулятор\nфлаг -h (--help) - выдает подробную справку по программе, с перечислением всех\n"
           "возможных команд\n");
}


int main(int argc, char *argv[]){
    system("chcp 65001");

    if (argc == 1){
        printTask();
    }

    else if (argc == 2){
        if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) printHelp();
        else if (strcmp(argv[1], "-t") == 0 || strcmp(argv[1], "--table") == 0) printTable();
        else printWrong();
    }

    else if (argc == 5){
        if((strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--calc") == 0) && isDigit(argv[2]) && isDigit(argv[4]) &&
           strlen(argv[3]) == 1 && contains("+-x/", argv[3][0]))
            printf("\n%lf\n", operate_double(atof(argv[2]), atof(argv[4]), argv[3][0]));
        else if(strlen(argv[3]) == 1 && argv[3][0] == '%')
            printf("%s", "\nвещественные числа не поддерживают операцию '%'\n");
        else
            printWrong();
    }

    else if(argc == 6){
        if((strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--calc") == 0) && isDigit(argv[2]) && isDigit(argv[4]) &&
           strlen(argv[3]) == 1) {
            if ((strcmp(argv[5], "-i") == 0 || strcmp(argv[5], "--int") == 0) && contains("+-x/%", argv[3][0]))
                printf("\n%d\n", operate_int(atoi(argv[2]), atoi(argv[4]), argv[3][0]));
            else if (strcmp(argv[5], "-x") == 0 || strcmp(argv[5], "--hex") == 0)
                printf("перевод в шестнадцатеричную систему не работает для вещественных чисел");
            else
                printWrong();
        } else{
            printWrong();
        }
    }

    else if (argc == 7){
        if((strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--calc") == 0) && isDigit(argv[2]) && isDigit(argv[4]) &&
           strlen(argv[3]) == 1 && (strcmp(argv[5], "-i") == 0 || strcmp(argv[5], "--int") == 0 ||
                                    strcmp(argv[6], "-i") == 0 || strcmp(argv[6], "--int") == 0) && (strcmp(argv[5], "-x") == 0 ||
                                                                                                     strcmp(argv[5], "--hex") == 0 || strcmp(argv[6], "-x") == 0 || strcmp(argv[6], "--hex") == 0)){
            if (contains("+-x/%", argv[3][0])){
                if (operate_int(atoi(argv[2]), atoi(argv[4]), argv[3][0]) < 0)
                    printf("\n-%x\n", -operate_int(atoi(argv[2]), atoi(argv[4]), argv[3][0]));
                else
                    printf("\n%x\n", operate_int(atoi(argv[2]), atoi(argv[4]), argv[3][0]));
            }else{
                printWrong();
            }
        } else{
            printWrong();
        }
    }

    else{
        printWrong();
    }
    return 0;
}//
// Created by vlad on 24.11.2023.
//
