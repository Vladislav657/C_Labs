#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define ASCII_COUNT 95


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
    int is_previous_space = 1;
    char c = ' ';
    while(c != EOF){
        c = fgetc(in);
        if (isspace(c) || c == EOF) {
            if (is_previous_space == 0) count++;
            is_previous_space = 1;
        } else {
            is_previous_space = 0;
        }
    }
    return count;
}


double countOfAllChars(FILE* in){
    double count = 0;
    while(fgetc(in) != EOF)
        count++;
    return count;
}


void printAll(FILE* in){
    printf("\nсимвол\tколичество\tчастота\n");
    int charCounts[ASCII_COUNT];
    for (int i = 0; i < ASCII_COUNT; ++i) charCounts[i] = 0;
    double countAll = countOfAllChars(in);
    char c;
    fseek(in, -ftell(in), SEEK_END);
    while((c = fgetc(in)) != EOF){
        charCounts[(int)c - 32]++;
    }
    for (int i = 0; i < ASCII_COUNT; ++i) {
        printf("%c\t%d\t\t%lf\n", (char)(i + 32), charCounts[i], charCounts[i] / countAll);
    }
}


void printEn(FILE* in){
    printf("\nбуква\tколичество\tчастота\n");
    int charCounts[ASCII_COUNT];
    for (int i = 0; i < ASCII_COUNT; ++i) charCounts[i] = 0;
    double countAll = countOfAllChars(in);
    char c;
    fseek(in, -ftell(in), SEEK_END);
    while((c = fgetc(in)) != EOF){
        charCounts[(int)c - 32]++;
    }
    for (int i = 0; i < ASCII_COUNT; ++i) {
        if(i + 32 <= 90 && i + 32 >= 65 || i + 32 <= 122 && i + 32 >= 97)
            printf("%c\t%d\t\t%lf\n", (char)(i + 32), charCounts[i], charCounts[i] / countAll);
    }
}


void printEnIr(FILE* in){
    printf("\nбуква\tколичество\tчастота\n");
    int charCounts[ASCII_COUNT];
    for (int i = 0; i < ASCII_COUNT; ++i) charCounts[i] = 0;
    double countAll = countOfAllChars(in);
    char c;
    fseek(in, -ftell(in), SEEK_END);
    while((c = fgetc(in)) != EOF){
        charCounts[(int) tolower(c) - 32]++;
    }
    for (int i = 0; i < ASCII_COUNT; ++i) {
        if(i + 32 <= 122 && i + 32 >= 97)
            printf("%c\t%d\t\t%lf\n", (char)(i + 32), charCounts[i], charCounts[i] / countAll);
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
        else if(strcmp(argv[2], "--en") == 0) printEn(fp);
        else if(strcmp(argv[2], "--all") == 0) printAll(fp);
        else printWrong();
        fclose(fp);
    }

    else if(argc == 4){
        FILE* fp = fopen(argv[1], "r");
        if(fp == NULL){
            printf("\nТакого файла не существует\n");
            return 0;
        }
        if(strcmp(argv[2], "--en") == 0 && strcmp(argv[3], "--ir") == 0) printEnIr(fp);
        else printWrong();
        fclose(fp);
    }

    else{
        printWrong();
    }
    return 0;
}
