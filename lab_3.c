#include <stdio.h>
#include <pthread.h>


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


typedef struct{
    unsigned left_fork;
    unsigned right_fork;
} philosopher_t;


typedef struct{
    pthread_mutex_t forks[5];
} table_t;


typedef struct{
    philosopher_t *philosopher;
    table_t *table;
} lunch_t;





int main(int argc, char *argv[]) {

    return 0;
}
