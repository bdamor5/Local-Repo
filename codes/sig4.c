#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
/* Handle SIGCHLD signals. */
void handle_sigchld(int sig)
{
	pid_t pid;
	int status;
	pid = wait(&status);

	printf("Reaped child %d\n",pid);
	sleep(1);
}
int main() {
	int i;
	signal(SIGCHLD, handle_sigchld);
	for (i = 0; i < 3; i++) {
		if (fork() == 0) {
			/* Child-process code. */
			printf("Hello from child %d\n", getpid());
			sleep(2);
			exit(0); /* Term child */
		}
	}
	/* Parent-process code. */
	while (1) /* Wait for children */
		pause(); /* to terminate. */
	return 0;
}
