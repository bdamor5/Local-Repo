#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/sem.h> 
#include<semaphore.h>
#include<fcntl.h>
int cnt = 0;
sem_t *s;
void *worker(void *args)
{
	int i=0;
	for(i=0;i<50000;i++)
	{
	     	sem_wait(s);
		cnt++;
		sem_post(s);
	}
}
int main()
{
s = sem_open("/sem1", O_CREAT, 0600,1);
pthread_t tid[2];
int i=0;

		
	
	for(i=0;i<2;i++)
		pthread_create(&tid[i],NULL,worker,NULL);
	for(i=0;i<2;i++)
		pthread_join(tid[i],NULL);
	printf("counter value: %d\n",cnt);
	printf("Finish\n");
		

}

