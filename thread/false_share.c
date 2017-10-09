#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

#define NR_THREAD 2

static long num_rect = 800000000;

typedef struct sum_struct {
  double sum;
  //char padding[24];
} sum_struct;

struct sum_struct __sum[NR_THREAD];

void* calc_pi(void* ptr)
{
  int index = (int)ptr;

  double mid = 0.0;
  double height = 0.0;
  double width = 1.0/((double)num_rect);

  int cur = index;
  for(;cur < num_rect; cur += NR_THREAD)
  {
    mid = (cur+0.5)*width;
    height = 4.0/(1 + mid*mid);
    __sum[index].sum += height;
  }

  __sum[index].sum *= width;
}

int main()
{
  int i = 0;
  int ret; 
  double result = 0.0;
  pthread_t tid[NR_THREAD];

  fprintf(stdout, "size = %ld\n", sizeof(struct sum_struct));
  for( i=0; i<NR_THREAD; i++)
  {
    __sum[i].sum = 0.0;

    ret = pthread_create(&tid[i], NULL, calc_pi, (void*) i);
    if(ret!=0)
    {
      exit(1);
    }
  }

  for(i=0;i<NR_THREAD;i++)
  {
    pthread_join(tid[i], NULL);
    result += __sum[i].sum;
  }

  fprintf(stdout,"the PI = %.32f\n", result);
  return 0;
}
