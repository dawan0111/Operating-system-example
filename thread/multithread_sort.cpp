#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 10
/* global variables are shared by threads */
int array[MAX_NUM] = {5, 6, 3, 2, 1, 1, 6, 7, 5, 9};
size_t array_size = 10;

typedef struct {
    size_t low;
    size_t high;
} parameters;

int cmp(const void  *a, const void *b) {
    return *((int *)a) - *((int *)b);
}

void *runner(void *param) {
    size_t low, high;
    low = ((parameters *)param)->low;
    high = ((parameters *)param)->high;

    qsort(array + low, high - low, sizeof(int), cmp);

	pthread_exit(0);
}

void merge_array(int *result) {
    size_t low1 = 0, high1 = array_size / 2;
    size_t low2 = array_size / 2, high2 = array_size;
    size_t i = 0;
    while(low1 < high1 && low2 < high2) {
        if(array[low1] < array[low2]) {
            result[i++] = array[low1++];
        } else {
            result[i++] = array[low2++];
        }
    }
    if(low2 < high2) {
        low1 = low2, high1 = high2;
    }
    while(low1 < high1) {
        result[i++] = array[low1++];
    }
}

void print_array(int *arr, size_t size) {
    for(size_t i = 0; i != size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    pthread_t tid[2];
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    parameters data[2];
    data[0].low = 0, data[0].high = array_size / 2;
    data[1].low = array_size / 2, data[1].high = array_size;

    pthread_attr_init(&attr);

    for(size_t i = 0; i != 2; ++i) {
        pthread_create(&tid[i], &attr, runner, &data[i]);
    }

    for(size_t i = 0; i != 2; ++i) {
        pthread_join(tid[i], NULL);
    }

    int sorted_array[MAX_NUM];
    merge_array(sorted_array);
    printf("After merging:\n");
    print_array(sorted_array, array_size);
}