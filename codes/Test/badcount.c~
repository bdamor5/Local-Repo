#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
int cnt = 0;
void *worker(void *args)
{
	int i=0;
	for(i=0;i<50000;i++)
		cnt++;
}
int main()
{
	pthread_t tid[2];
	int i=0;
		
	while(1)
	{		
		for(i=0;i<2;i++)
			pthread_create(&tid[i],NULL,worker,NULL);

		for(i=0;i<2;i++)
			pthread_join(tid[i],NULL);

		printf("counter value: %d\n",cnt);
		if(cnt<50000)
		{
			printf("Finish\n");
			break;
		}
		cnt=0;
	}
}

