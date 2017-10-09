#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/syscall.h>

void* thread_worker(void* param)
{
  int TID = syscall(SYS_gettid);
  printf("thread-%d: gettid return %d\n", TID, TID);
  printf("thread-%d: pthread_self return %p\n", 
      TID, (void*)pthread_self());

  printf("thread-%d: Iwill exit now\n", TID);
  pthread_exit(NULL);
  return NULL;
}
int main(){
  int ret;
  pthread_t tid = 0;
  ret = pthread_create(&tid, NULL, thread_worker, NULL);
  ret = pthread_join(tid, NULL);
  ret = pthread_create(&tid, NULL, thread_worker, NULL);
  ret = pthread_join(tid, NULL);
  return 0;
}
