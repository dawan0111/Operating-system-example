#include <pthread.h>
#include <stdio.h>
#define NUM_THREADS 5

void *runner(void *param);

int main(int argc, char *argv[]) {
    int i, scope;
    int values[NUM_THREADS];
    pthread_t tid[NUM_THREADS];
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    if (pthread_attr_getscope(&attr, &scope) != 0) {
        fprintf(stderr, "UNable to get scheduling scope \n");
    } else {
        if (scope == PTHREAD_SCOPE_PROCESS) {
            printf("PTHREAD_SCOPE_PROCESS \n");
        } else if (scope == PTHREAD_SCOPE_SYSTEM) {
            printf("PTHREAD_SCOPE_SYSTEM \n");
        } else {
            fprintf(stderr, "Illegal scope value. \n");
        }

        pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

        for (i = 0; i < NUM_THREADS; i++) {
            values[i] = i;
            pthread_create(&tid[i], &attr, runner, &values[i]);
        }

        for (i = 0; i < NUM_THREADS; i++) {
            pthread_join(tid[i], NULL);
        }
    }
}

void *runner(void *param) {
    printf("run: %d \n", *(int *) param);
    pthread_exit(0);
}