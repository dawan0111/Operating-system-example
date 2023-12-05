#include <iostream>
#include <pthread.h>
#include <atomic>

int32_t shared_data = 0;
std::atomic<int32_t> atomic_shared_data(0);

void *add(void *param) {
	for (int32_t i = 0; i < 1000000; i++) {
		shared_data++;
	}

	pthread_exit(0);
}
void *sub(void *param) {
	for (int32_t i = 0; i < 1000000; i++) {
		shared_data--;
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
	pthread_create(&tid[0], &attr, add, NULL);
	pthread_create(&tid[1], &attr, sub, NULL);
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

    std::cout << "shared_data: " << shared_data << std::endl;

    pthread_create(&tid[2], &attr, atomic_add, NULL);
	pthread_create(&tid[3], &attr, atomic_sub, NULL);
	pthread_join(tid[2], NULL);
	pthread_join(tid[3], NULL);

    std::cout << "atomic_shared_data: " << atomic_shared_data << std::endl;
}