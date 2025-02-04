/*******************************************************************************
 *
 * Program: Example 1
 * 
 * Description: Initial example using pthreads
 *
 * Input: 
 *   none
 * Output: 
 *   message from each thread
 * 
 * Compile:  gcc -g -Wall -o pth_hello pth_hello.c -lpthread
 * Usage:    ./pth_hello <thread_count>
 *
 * Reference:  https://www.youtube.com/watch?v=ldJ8WGZVXZk 
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 

void *computation(); // void function prototype

int main(int argc, char* argv[])
{
  pthread_t thread1; // make a thread variable
  pthread_t thread2; // make a thread variable

  long value1 = 1;
  long value2 = 2;

  pthread_create(&thread1, NULL, computation, (void *) &value1); // create a thread
  pthread_create(&thread2, NULL, computation, (void *) &value2); // create a thread
  
  pthread_join(thread1, NULL); // wait for the thread to finish
  pthread_join(thread2, NULL); // wait for the thread to finish

  return 0;
}

void *computation(void *add) // void function definition
{
  long sum = 0;
  long *add_num = (long *)add; 

  for (long i = 0; i < 1000000000; i++) 
  {
    sum += *add_num; // add the value of the long pointer to the sum
  }
  printf("Add: %ld\n", *add_num); 
  return NULL; // return void null
}



// Visualizations of single-threaded vs. multi-threaded execution.
//
//
//              Single-Threaded Program
//
//          |   int x;
//          |   x = 20;
//          |   int y;
//  Time    |   y = 50;
//          |   int sum;
//          |   sum = x + y;
//          ↓
//     
//
//
//              Multi-Threaded Program 
//
//          |   int x;                 |  int a;
//          |   x = 20;                |  a = 3;
//          |   int y;                 |  int b;
//  Time    |   y = 50;                |  b = 5;
//          |   int sum;               |  int product;
//          |   sum = x + y;           |  product = a * b;
//          ↓                          ↓
//
//          Parallel Execution 
//
//
//
//              Multi-Threaded Program 
//
//          |   int x;                 |  
//          |                          |  int a;
//          |                          |  a = 3;
//          |   x = 20;                |  
//          |   int y;                 |   
//          |                          |  int b;
//  Time    |   y = 50;                |  
//          |                          |  b = 5;
//          |                          |  int product;
//          |   int sum;               |  
//          |   sum = x + y;           |  
//          |                          |  product = a * b;
//          ↓                          ↓
//
//          Concurrent But Not Parallel Execution 
//
//
//
//              Multi-Threaded Program 
//
//          |                             pthread
//          |
//          |   sum = x + y;           
//          |   pthread_create --------   function()
//          |   ...                    |  int a = 5;
//          |   printf("%d", sum);     |  int b = 3;
//  Time    |   ...                    |  int result = x + y;
//          |   pthread_join   --------↓
//          |   ...       | 
//          |   ...       |   
//          ↓          execution PAUSES here until thread done
//
//          Parallel Execution 