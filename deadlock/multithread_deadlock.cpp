#include <iostream>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t first_mutex;
pthread_mutex_t second_mutex;

void *first_thread(void *param) {
    pthread_mutex_lock(&first_mutex);
    sleep(1); // ready queue
    pthread_mutex_lock(&second_mutex);

    std::cout << "first thread run!" << std::endl;

    pthread_mutex_unlock(&second_mutex);
    pthread_mutex_unlock(&first_mutex);

	pthread_exit(0);
}
void *second_thread(void *param) {
	pthread_mutex_lock(&second_mutex);
    pthread_mutex_lock(&first_mutex);

    std::cout << "second thread run!" << std::endl;

    pthread_mutex_unlock(&first_mutex);
    pthread_mutex_unlock(&second_mutex);

	pthread_exit(0);
}

int main() {
    pthread_t tid[4];
	pthread_attr_t attr;

	pthread_attr_init(&attr);
    pthread_mutex_init(&first_mutex, NULL);
    pthread_mutex_init(&second_mutex, NULL);


	pthread_create(&tid[0], &attr, first_thread, NULL);
	pthread_create(&tid[1], &attr, second_thread, NULL);
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
}