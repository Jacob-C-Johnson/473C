/*******************************************************************************
 *
 * Program: Hello World
 * 
 * Description: Demonstrate basic use of pthreads:
 *   create some threads that each print a message
 *
 * Input: 
 *   none
 * Output: 
 *   message from each thread
 * 
 * Compile:  gcc -g -Wall -o pth_hello pth_hello.c -lpthread
 * Usage:    ./pth_hello <thread_count>
 *
 * Reference: Pacheco Textbook Section 4.2 (pp. 161 and ff.)
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 

void *hello(); // void function prototype
long thread_count; // global variable for thread count

int main(int argc, char* argv[])
{
  if(argc != 2) // if the number of arguments is not 2
  {
    fprintf(stderr, "usage: %s <number of threads>\n", argv[0]); // print the usage message
    exit(0); // exit the program
  }

  long thread_count = strtol(argv[1], NULL, 10); // convert the argument to a long

  pthread_t* threads; // make a matrix for threads

  threads = malloc(thread_count * sizeof(pthread_t)); // allocate memory for the threads

  for (long i = 0; i < thread_count; i++) // loop through the threads
  {
    pthread_create(&threads[i], NULL, hello, (void*) i); // create a thread
  }

  for (long i = 0; i < thread_count; i++) // loop through the threads
  {
    pthread_join(threads[i], NULL); // wait for the thread to finish
  }

  free(threads); // free the memory allocated for the threads

  return 0;
}

void *hello(void* rank) {
  long my_rank = (long) rank; 
  printf("hello from %ld using %ld threads\n",my_rank, thread_count); // print the message
}