#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
void handler1(int sig) {
printf("child got SIGUSR1\n");
}
void handler2(int sig) {
printf("parent got SIGUSR1\n");
}
int main() {
pid_t pid;
if ((pid = fork()) == 0) {
signal(SIGUSR1, handler1);
kill(getpid(), SIGUSR1);
sleep(1);
exit(0);
}
else {
signal(SIGUSR1, handler2);
kill(getpid(), SIGUSR1);
waitpid(pid, NULL, 0);
}
return 0;
}
