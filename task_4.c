#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


int is_prime(int n){
    if(n < 0) n *= -1;
    for (int i = 2; i < (int) sqrt(n) + 1; ++i) {
        if(n % i == 0) return 0;
    }
    return 1;
}


int main(void) {
    system("chcp 65001");

    char *path = (char *) malloc(100 * sizeof(char));
    scanf("%s", path);
    realloc(path, strlen(path));

    FILE *in = fopen(path, "r");
    int n;
    fscanf(in, "%d", &n);
    int primes = 0;
    for (int i = n + 1; i < 2 * n; ++i) {
        if (is_prime(i)) primes++;
    }
    fclose(in);

    FILE *out = fopen("primes_count", "w");
    fprintf(out, "%d", primes);
    fclose(out);

    free(path);

    return 0;
}