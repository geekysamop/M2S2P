#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <thread>
#include <time.h>
#include<unistd.h>
#include<string>
using namespace std;
// Define the number of threads that will be created
#define NUM_THREADS 8

// Define the maximum number of elements in the data array
#define MAX 1000000

// Create a mutex lock to ensure sequential updates of the global sum
pthread_mutex_t mutx;

// Declare the data array and global sum variable
int data[MAX];
long global_sum = 0;

// Define the sum function that each thread will execute
void *sum(void *threadid)
{
long tid;
long sum = 0;
tid = (long)threadid;

// Define the range of elements that the current thread will sum
int range = MAX/NUM_THREADS;
int start = tid * range ;
int end = start + range ;

// Calculate the sum of the designated elements in the data array
for(int i = start ; i < end ; i++) {
sum += data[i];
}

// Enforce sequential update of the global sum variable using a mutex lock
pthread_mutex_lock(&mutx);
global_sum += sum;
pthread_mutex_unlock(&mutx);

// Exit the thread
pthread_exit(NULL);
}

// Define the main function
int main(int argc, char *argv[])
{
// Initialize the mutex lock
pthread_mutex_init(&mutx, NULL)

// Print the number of cores on the machine
int cores = std::thread::hardware_concurrency();
cout<<" the number of cores on this machine = "<<cores<<endl;

// Generate random numbers and store them in the data array
for(int i = 0; i < MAX; i++) {
data[i] = rand() % 20;
}

// Create an array of threads and assign them the sum function
pthread_t threads[NUM_THREADS];
long tid = 0;
for(tid = 0; tid < NUM_THREADS; tid++) {
pthread_create(&threads[tid], NULL, sum, (void *)tid);
}

// Wait for all threads to finish before printing the final sum
for(tid = 0; tid < NUM_THREADS; tid++) {
pthread_join(threads[tid], NULL);
}

// Print the final sum of all the numbers generated by the threads
cout<<"the final sum ="<<global_sum<<endl;
}
