#include <iostream>
#include <pthread.h>
#include <atomic>
#include <chrono>

int32_t shared_data = 0;
std::atomic<int32_t> atomic_shared_data(0);
pthread_mutex_t mutex;

void *add(void *param) {
	for (int32_t i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex);
		shared_data++;
        pthread_mutex_unlock(&mutex);
	}

	pthread_exit(0);
}
void *sub(void *param) {
	for (int32_t i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex);
		shared_data--;
        pthread_mutex_unlock(&mutex);
	}

	pthread_exit(0);
}

void *atomic_add(void *param) {
	for (int32_t i = 0; i < 1000000; i++) {
		atomic_shared_data++;
	}

	pthread_exit(0);
}
void *atomic_sub(void *param) {
	for (int32_t i = 0; i < 1000000; i++) {
		atomic_shared_data--;
	}

	pthread_exit(0);
}

int main() {
    pthread_t tid[4];
	pthread_attr_t attr;

	pthread_attr_init(&attr);
    pthread_mutex_init(&mutex, NULL);

	auto start = std::chrono::high_resolution_clock::now();

	pthread_create(&tid[0], &attr, add, NULL);
	pthread_create(&tid[1], &attr, sub, NULL);
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	std::cout << "Mutex time taken: " << elapsed.count() << " seconds" << std::endl;

    std::cout << "mutex_shared_data: " << shared_data << std::endl;

	auto start2 = std::chrono::high_resolution_clock::now();

    pthread_create(&tid[2], &attr, atomic_add, NULL);
	pthread_create(&tid[3], &attr, atomic_sub, NULL);
	pthread_join(tid[2], NULL);
	pthread_join(tid[3], NULL);

	auto end2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed2 = end2 - start2;
	std::cout << "atomic time taken: " << elapsed2.count() << " seconds" << std::endl;

    std::cout << "atomic_shared_data: " << atomic_shared_data << std::endl;

	/*
		print:
		mutex: 0.137445 seconds
		atomic: 0.0355448 seconds

		result: mutex is slower than atomic. (overhead)
	*/
}