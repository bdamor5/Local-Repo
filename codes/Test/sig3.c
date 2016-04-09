#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
struct two_int {int a; int b; } data;
/* print a message, then request another SIGALRM */ 
void handler_sigalrm(int sig) {
   printf("%d %d\n", data.a, data.b);
   alarm(1); /* Request another SIGALRM in 1 second. */
}

int main() {
    static struct two_int zeros = {0, 0}, ones = {1, 1};
    
    signal(SIGALRM, handler_sigalrm);
    data.a = 0; data.b = 0; 
    
    alarm(1); /* Request a SIGALRM in 1 second. */
    while (1)  {
         data.a = zeros.a; data.b = zeros.b;
         data.a = ones.a; data.b = ones.b;
    }
}
