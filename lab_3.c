#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
#define SIZE 5

typedef struct{
    const char *name;
    unsigned left_fork;
    unsigned right_fork;
} philosopher_t;

typedef struct{
    pthread_mutex_t forks[SIZE];
} table_t;

typedef struct{
    const philosopher_t *philosopher;
    const table_t *table;
} philosopher_args_t;



void init_philosopher(philosopher_t *philosopher,
                      const char *name,
                      unsigned left_fork,
                      unsigned right_fork) {
    philosopher->name = name;
    philosopher->left_fork = left_fork;
    philosopher->right_fork = right_fork;
}

void init_table(table_t *table) {
    size_t i;
    for (i = 0; i < SIZE; i++) {
        pthread_mutex_init(&table->forks[i], NULL);
    }
}

void* eat(void *args) {
    philosopher_args_t *arg = (philosopher_args_t*) args;
    const philosopher_t *philosopher = arg->philosopher;
    const table_t *table = arg->table;
    do {
        pthread_mutex_lock(&mutex);
        pthread_mutex_lock(&table->forks[philosopher->left_fork]);
        pthread_mutex_lock(&table->forks[philosopher->right_fork]);
        printf("%s начинает обед\n", philosopher->name);
        sleep(5);
        pthread_mutex_unlock(&mutex);
        pthread_mutex_unlock(&table->forks[philosopher->right_fork]);
        pthread_mutex_unlock(&table->forks[philosopher->left_fork]);
        printf("%s завершает обед\n", philosopher->name);
    } while (1);
}

int main() {
    system("chcp 65001");

    pthread_t threads[SIZE];
    philosopher_t philosophers[SIZE];
    philosopher_args_t arguments[SIZE];
    table_t table;
    size_t i;

    init_table(&table);

    init_philosopher(&philosophers[0], "философ_1", 0, 1);
    init_philosopher(&philosophers[1], "философ_2",   1, 2);
    init_philosopher(&philosophers[2], "философ_3", 2, 3);
    init_philosopher(&philosophers[3], "философ_4", 3, 4);
    init_philosopher(&philosophers[4], "философ_5", 4, 0);

    for (i = 0; i < SIZE; i++) {
        arguments[i].philosopher = &philosophers[i];
        arguments[i].table = &table;
    }

    for (i = 0; i < SIZE; i++) {
        pthread_create(&threads[i], NULL, eat, &arguments[i]);
    }

    for (i = 0; i < SIZE; i++) {
        pthread_join(threads[i], NULL);
    }
}
