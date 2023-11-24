#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int rightPart(int n){
    if(n < 0) n *= -1;
    int k = 1;
    while (n % 2 != 1){
        k *= 2;
        n /= 2;
    }
    return k;
}


int rightPartsSum(int a, int b){
    int sum = 0;
    for (int i = a; i <= b; ++i)
        sum += rightPart(i);
    return sum;
}


int main(void) {
    system("chcp 65001");

    char *path = (char *) malloc(100 * sizeof(char));
    scanf("%s", path);
    realloc(path, strlen(path));

    FILE *in = fopen(path, "r");
    int a, b;
    fscanf(in, "%d", &a);
    fscanf(in, "%d", &b);
    fclose(in);

    printf("%d", rightPartsSum(a, b));

    return 0;
}
