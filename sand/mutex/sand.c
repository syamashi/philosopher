#include "stdio.h"
#include "pthread.h"
#include "stdbool.h"

int a = 0;
pthread_mutex_t mutex;

void *func_thread(void *p) {
	bool *B = p;

  printf("start %d\n", *(int*)p);

  int i=0;
  for(i=0; i < 10000; i++){
    pthread_mutex_lock(&mutex);
	int next = a + 1;
	int now = a;
	a = next;
    pthread_mutex_unlock(&mutex);

	if (now+1 != next) {
	  printf("other theard change %d %d\n", a+1, next);
	}
	if (i == 5000)
		*B = true;
  }

  return 0;
}

int main(void) {
  pthread_mutex_init(&mutex, NULL);

  printf("test\n");

  int b = 42;
  bool parent = false;
  bool *child = &parent;
  int a=10;
  int *c = &a;

  pthread_t pthread;
  pthread_create( &pthread, NULL, &func_thread, (void*)child);

  int i=0;
  for(i=0; i < 10000; i++){
    pthread_mutex_lock(&mutex);
	int next = a + 1;
	int now = a;
	a = next;
    pthread_mutex_unlock(&mutex);

	if (now+1 != next) {
	  printf("other theard change %d %d\n", a+1, next);
	}
  }
  if (parent)
		printf("parent true\n");

  pthread_join(pthread, NULL); // pthreadで作られたスレッドが終わるまで待つ
  printf("a=%d\n", a);

  return 0;
}