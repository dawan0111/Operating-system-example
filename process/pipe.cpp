#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(void) {
    char write_msg[BUFFER_SIZE] = "Hello!";
    char read_msg[BUFFER_SIZE];
    char child_write_msg[BUFFER_SIZE];
    char parent_read_msg[BUFFER_SIZE];

    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    /* parent process */
    if (pid > 0) {
        write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);

        wait(NULL);

        read(fd[READ_END], parent_read_msg, BUFFER_SIZE);
        printf("parent read: %s \n", parent_read_msg);

        close(fd[READ_END]);
        close(fd[WRITE_END]);
    } else {
        char *write_msg2 = "World!";

        read(fd[READ_END], read_msg, BUFFER_SIZE);
        printf("child read: %s \n", read_msg);

        sprintf(child_write_msg, "%s", read_msg);

        sprintf(&child_write_msg[strlen(read_msg)], "%s", write_msg2);

        write(fd[WRITE_END], child_write_msg, strlen(child_write_msg) + 1);
        close(fd[WRITE_END]);
        close(fd[READ_END]);
    }
}