#include <stdio.h>
#include <stdlib.h>
#include "lamport_mutex.h"

int N;
int *choosing;
int *ticket;

void lamport_mutex_init(int num_threads) {
  //printf("Initializing... mutex\n");

  N = num_threads;
  choosing = malloc(N * sizeof(int));
  ticket = malloc(N * sizeof(int));
  
  if (!choosing || !ticket) {
    fprintf(stderr, "Allocating error memory for mutex.\n");
    exit(EXIT_FAILURE);
  }
}

int max_ticket() {
  int i, max = ticket[0];
  for (i = 1; i < N; i++){
    max = ticket[i] > max ? ticket[i] : max;
  }

  return max;
}

void lamport_mutex_lock(int thread_num) {
    
  int i, j = thread_num;
  choosing[i] = 1;
  ticket[i] = max_ticket() + 1;
  choosing[i] = 0;
  //printf("Thread: %d, Ticket: %d\n", i, ticket[i]);

  for (j = 0; j < N; j++) {
    while (choosing[j]);
    while (ticket[j] != 0 && 
          ((ticket[j] < ticket[i]) || (ticket[j] == ticket[i] && j < i))
    );
  }
}

void lamport_mutex_unlock(int thread_num) {
  ticket[thread_num] = 0;
}

void lamport_mutex_destroy() {
  //printf("Destroying... mutex\n");
  free(choosing);
  free(ticket);
}