#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdbool.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>

void *func(void *p)
{
	sem_t *sem2 = p;

	for(int i=0; i<1; ++i){
		sem_wait(sem2);
		printf("sem\n");
	}
	return (NULL);
}

int main()
{
	sem_t *sem;
	sem_t *sem2;
	pid_t pid;
	int status;
	pthread_t thread;
	int keep[1000];
	for(int i=0; i<1000; ++i)
		keep[i] = i;
	sem_unlink("/aaa");
	sem = sem_open("/aaa", O_CREAT, 0600, 1); // "/" から始まれば名前付きsem。同じ名前で共有できる。
	sem2 = sem;
	sem_unlink("/aaa");// 全プロセスでこれがクローズされたら、自動でセマフォ削除される
	pid = fork();
	if (pid == 0)
	{
		for(int i=0; i<20; ++i)
			printf("keep[%d]:%d\n", i, keep[i]);
		pthread_create(&thread, NULL, (void *)&func, sem2);
//		sem_post(sem);
		pthread_join(thread, NULL);
		exit(0);
	}
	int microsecond = 1.5 * 1000000;
	for(int i=0; i<20; ++i)
		printf("keep[%d]:%d\n", i, keep[i]);
	for (int i=0; i<2; ++i){
		usleep(microsecond);
		sem_post(sem);
	}
	waitpid(-1, &status, 0);
	return (0);
}
