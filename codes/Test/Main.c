#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
        pid_t cpid;
        if(fork()==0)
        {
                printf("I am in Child");
                exit(0);
        }
        else
                cpid = wait(NULL);
        printf("Parent pid = %d\n",getpid());
        printf("child pid = %d\n",cpid);
        while(1);
}

