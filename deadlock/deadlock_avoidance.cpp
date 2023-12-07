/*
    Banker's Algorithm
*/

#include <iostream>

#define THREAD_NUM 5
#define RESOURCE_NUM 3

int available[RESOURCE_NUM] = { 3, 3, 2 };
int max[THREAD_NUM][RESOURCE_NUM] = {
    7, 5, 3,
    3, 2, 2,
    9, 0, 2,
    2, 2, 2,
    4, 3, 3
};
int allocation[THREAD_NUM][RESOURCE_NUM] = {
    0, 1, 0,
    2, 0, 0,
    3, 0, 2,
    2, 1, 1,
    0, 0, 2
};
int need[THREAD_NUM][RESOURCE_NUM];

enum RequestStatus {
    ERROR = 0,
    WAIT,
    SUCCESS
};

bool check_safety() {
    int work[RESOURCE_NUM];
    bool finish[THREAD_NUM];

    for (int i = 0; i < RESOURCE_NUM; i++) {
        work[i] = available[i];
    }

    for (int i = 0; i < THREAD_NUM; i++) {
        finish[i] = false;
    }

    for (int i = 0; i < THREAD_NUM; i++) {
        for (int j = 0; j < THREAD_NUM; j++) {
            if (finish[j]) {
                continue;
            }

            bool need_condition = true;

            for (int k = 0; k < RESOURCE_NUM; k++) {
                if (need[j][k] > work[k]) {
                    need_condition = false;
                    break;
                }
            }

            if (need_condition) {
                for (int k = 0; k < RESOURCE_NUM; k++) {
                    work[k] = work[k] + allocation[j][k];
                }
                finish[j] = true;
            }
        }
    }

    for (int i = 0; i < THREAD_NUM; i++) {
        if (!finish[i]) {
            std::cout << "Dead Lock!" << std::endl;
            return false;
        }
    }

    std::cout << "Safety!" << std::endl;
    return true;
}

RequestStatus resource_request(int thread_num, int* request) {
    enum RequestStatus status = SUCCESS;
    for (int i = 0; i < RESOURCE_NUM; i++) {
        if (need[thread_num][i] < request[i]) {
            status = ERROR; 
            std::cout << "error (need < request)" << std::endl;
            return status;
        }
    }

    for (int i = 0; i < RESOURCE_NUM; i++) {
        if (available[i] < request[i]) {
            status = WAIT; 
            std::cout << "wait (available < request)" << std::endl;
            return status;
        }
    }

    std::cout << "success request!" << std::endl;

    for (int i = 0; i < RESOURCE_NUM; i++) {
        available[i] = available[i] - request[i];
        allocation[thread_num][i] = allocation[thread_num][i] + request[i];
        need[thread_num][i] = need[thread_num][i] - request[i];
    }

    return status;
}

int main() {
    for (int i = 0; i < THREAD_NUM; i++) {
        for (int j = 0; j < RESOURCE_NUM; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    int request_1[RESOURCE_NUM] = { 1, 0, 2 };
    std::cout << request_1 << std::endl;

    resource_request(1, request_1);
    check_safety();
}