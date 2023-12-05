#include <pthread.h>
#include <iostream>
#include <unistd.h>

pthread_rwlock_t g_rwLock;
int g_read_count = 0;
int data = 5;

void* read_runner(void *arg) {
    int ret = pthread_rwlock_rdlock(&g_rwLock);
    if (ret == 0) {
        std::cout << "read lock complete: " << data << std::endl;
    }

    sleep(3);

    pthread_rwlock_unlock(&g_rwLock);
    std::cout << "Unlock the read lock" << std::endl;
}

void* write_runner(void *arg) {
    int ret = pthread_rwlock_wrlock(&g_rwLock);
    if (ret == 0) {
        data = 10;
        std::cout << "write lock complete" << std::endl;
    }

    pthread_rwlock_unlock(&g_rwLock);
    std::cout << "Unlock the write lock" << std::endl;
  }

int main() {
    int ret = pthread_rwlock_init(&g_rwLock, NULL);
    if (ret != 0) {
        std::cout << ret << std::endl;
        exit(1);
    }

    pthread_t read_thr[2];
    pthread_t write_thr[1];

    ret = pthread_create(&read_thr[0], NULL, read_runner, NULL);
    ret = pthread_create(&write_thr[0], NULL, write_runner, NULL);

    sleep(5);

    ret = pthread_create(&read_thr[1], NULL, read_runner, NULL);

    pthread_join(write_thr[1], NULL);
    pthread_join(read_thr[0], NULL);

    pthread_join(read_thr[1], NULL);
    

    pthread_rwlock_destroy(&g_rwLock);
}