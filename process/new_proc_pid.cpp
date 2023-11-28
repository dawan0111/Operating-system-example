#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int value = 5;

int main()
{
	// pid_t pid;
	// pid_t pid2;
	// pid_t pid3;
	// pid = fork();
	// printf("fork1 ");
	// printf("pid: %d \n", pid);
	// pid2 = fork();
	// printf("fork2 ");
	// printf("pid2: %d \n", pid2);
	// pid3 = fork();
	// printf("fork3 ");
	// printf("pid3: %d \n", pid3);
	pid_t pid;
	/* fork a child process */
	pid = fork();

	if (pid < 0) { /* error occurred */
		fprintf(stderr, "Fork Failed\n");
		return 1;
	}
	else if (pid == 0) { /* child process */
		printf("I am the child %d\n",value);
		value += 15;
		execlp("/bin/ls","ls",NULL);
	}
	else { /* parent process */
		/* parent will wait for the child to complete */
		wait(NULL);
		printf("Child Complete %d\n", value);
	}
    
    return 0;
}