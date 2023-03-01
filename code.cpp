#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <thread>
#include <time.h>
#include<unistd.h>
#include<string>
using namespace std;

#define NUM_THREADS 8
#define MAX 1000000
pthread_mutex_t mutx;

int data[MAX];
long global_sum = 0;

void *sum(void *threadid)
{
   long tid;
   long sum = 0;
   tid = (long)threadid;
  // printf("Bye World! It's me, thread #%ld!\n", tid);
  int range = MAX/NUM_THREADS;
  int start = tid * range ;
  int end = start + range ;

  for(int i = start ; i < end ; i++) {
        sum += data[i];
  }

  //enforce sequential update
  pthread_mutex_lock(&mutx);
  global_sum += sum;

  pthread_mutex_unlock(&mutx);

  //enforce sequential update

   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{ 
    int cores = std::thread::hardware_concurrency();
    pthread_mutex_init(&mutx, NULL);

    cout<<" the number of cores on this machine = "<<cores<<endl;
   // srand(time(NULL));
   for(int i = 0; i < MAX; i++) {
       data[i] = rand() % 20;
   }

   pthread_t threads[NUM_THREADS];
   long tid = 0;

   for(tid = 0; tid < NUM_THREADS; tid++) {
       pthread_create(&threads[tid], NULL, sum, (void *)tid);
   }


   for(tid = 0; tid < NUM_THREADS; tid++) {
       pthread_join(threads[tid], NULL);
   }

   
   cout<<"the final sum ="<<global_sum<<endl;
}
