#include <stdio.h>
#include <pthread.h>

void thread_1(void* a)
{
	int i=0;
	int b = (int)a;
	printf("11this is a %d\n",b );
	for(i=0;i<6;i++)
	{
		printf("this is a pthread_1..\n");
		if(i==2)
			pthread_exit(0);
		sleep(1);
	}
}

void thread_2(void* a)
{
	int i;
	int b = (int)a;
	printf("11this is a %d\n",b );
	for (int i = 0; i < 3; ++i)
	{
		printf("this is a pthread_2\n");
	}
	pthread_exit(0);
}


int main()
{
	pthread_t id_1,id_2;
	int i,ret;
	ret = pthread_create(&id_1,NULL,thread_1,(void*)6);
	if (ret !=0)
	{
		printf("Create pthread error!\n");
		return -1;
	}

	ret = pthread_create(&id_2,NULL,thread_2,(void*)7);
	if (ret !=0)
	{
		printf("Create pthread error!\n");
		return -1;
	}
	pthread_join(id_1,NULL);
	pthread_join(id_2,NULL);

	return 0;
}