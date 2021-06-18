# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>

void *func(void *p)
{
	sem_t *sem2 = p;

	for (int i = 0; i < 5; ++i){
		sem_wait(sem2);
		printf("[func]%d called\n", i);
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

	sem_unlink("/aaa");
	sem = sem_open("/aaa", O_CREAT, 0600, 2); // "/" から始まれば名前付きsem。同じ名前で共有できる。
	sem2 = sem; // アドレス共有するだけで実態は同じ
	sem_unlink("/aaa");// 全プロセスでこれがクローズされたら、自動でセマフォ削除される
	pid = fork();
	if (pid == 0)
	{
		pthread_create(&thread, NULL, &func, sem2);
		pthread_join(thread, NULL);
		exit(0);
	}
	int microsecond = 1.5 * 1000000;
	for (int i = 0; i < 3; ++i){
		usleep(microsecond);
		sem_post(sem);
	}
	waitpid(-1, &status, 0);
	sem_close(sem);
	return (0);
}
