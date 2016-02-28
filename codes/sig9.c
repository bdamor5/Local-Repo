#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
int a = 1;
void handler(int sig) {
a = 0;
}
void emptyhandler(int sig) { }
int main() {
signal(SIGINT, handler);
signal(SIGCONT, emptyhandler);
int pid = fork();
if (pid == 0)
{
while (a == 1)
pause();
printf("a");
}
else
{
kill(pid, SIGCONT);
printf("b");
kill(pid, SIGINT);
printf("c");
}
}
