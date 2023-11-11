#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void printWrong(){
    printf("\nввод не соответствует командам\n"
           "-w (--word) выдать количество слов в заданном файле (разделители пробельные символы)\n"
           "--en выдать таблицу которая содержит количество и частоту встреч латинских букв\n"
           "--all (флаг по умолчанию) выдать таблицу которая содержит количество и частоту встреч всех ASCII символов\n"
           "--ir – игнорировать регист букв (для флага --en)\n");
}


void printTask(){
    printf("\nЭто программа для сбора статистики файла (ввод формата «путь_к_файлу флаг»)\n"
           "-w (--word) выдать количество слов в заданном файле (разделители пробельные символы)\n"
           "--en выдать таблицу которая содержит количество и частоту встреч латинских букв\n"
           "--all (флаг по умолчанию) выдать таблицу которая содержит количество и частоту встреч всех ASCII символов\n"
           "--ir – игнорировать регист букв (для флага --en)\n");
}


int countOfWords(FILE* in){
    int count = 0;
    char c;
    while((c = fgetc(in)) != EOF)
        if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\b') count++;
    if (count > 0) count++;
    return count;
}


int countOfChar(char ch, FILE* in){
    int count = 0;
    char c;
    while((c = fgetc(in)) != EOF)
        if (c == ch) count++;
    return count;
}


int countOfCharIr(char ch, FILE* in){
    int count = 0;
    char c;
    while((c = fgetc(in)) != EOF)
        if (tolower(c) == ch) count++;
    return count;
}


double countOfAllChars(FILE* in){
    double count = 0;
    while(fgetc(in) != EOF)
        count++;
    return count;
}


void printEn(char *chars, FILE* f){
    printf("\nсимвол\tколичество\tчастота\n");
    double countAll = countOfAllChars(f);
    for (int i = 0; i < strlen(chars); ++i) {
        fseek(f, -ftell(f), SEEK_END);
        int letterCount = countOfChar(chars[i], f);
        printf("%c\t%d\t\t%lf\n", chars[i], letterCount, letterCount / countAll);
    }
}


void printEnIr(char *chars, FILE* f){
    printf("\nсимвол\tколичество\tчастота\n");
    double countAll = countOfAllChars(f);
    for (int i = 0; i < strlen(chars); ++i) {
        fseek(f, -ftell(f), SEEK_END);
        int letterCount = countOfCharIr(chars[i], f);
        printf("%c\t%d\t\t%lf\n", chars[i], letterCount, letterCount / countAll);
    }
}


int main(int argc, char *argv[]) {
    system("chcp 65001");

    if(argc == 1){
        printTask();
    }

    else if(argc == 3){
        FILE* fp = fopen(argv[1], "r");
        if(fp == NULL){
            printf("\nТакого файла не существует\n");
            return 0;
        }
        else if(strcmp(argv[2], "-w") == 0 || strcmp(argv[2], "--word") == 0) printf("\n%d\n", countOfWords(fp));
        else if(strcmp(argv[2], "--en") == 0) printEn("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", fp);
        else if(strcmp(argv[2], "--all") == 0) printEn(" !#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                                       "[\\]\"^_~`{|}abcdefghijklmnopqrstuvwxyz", fp);
        else printWrong();
        fclose(fp);
    }

    else if(argc == 4){
        FILE* fp = fopen(argv[1], "r");
        if(fp == NULL){
            printf("\nТакого файла не существует\n");
            return 0;
        }
        if(strcmp(argv[2], "--en") == 0 && strcmp(argv[3], "--ir") == 0) printEnIr("abcdefghijklmnopqrstuvwxyz", fp);
        else printWrong();
        fclose(fp);
    }

    else{
        printWrong();
    }
    return 0;
}
