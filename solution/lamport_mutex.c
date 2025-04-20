#include <stdio.h>
#include <stdlib.h>
#include "lamport_mutex.h"

static int *choosing;
static int *ticket;
static int num_threads = 0;

void lamport_mutex_init(int n_threads) {

  int i;
  num_threads = n_threads;
  
  choosing = malloc(n_threads * sizeof(int));
  ticket = malloc(n_threads * sizeof(int));

  if (!choosing || !ticket) {
    fprintf(stderr, "Erro ao alocar memória para o mutex\n");
    exit(EXIT_FAILURE);
  }

  for(i=0; i<num_threads; i++) {
    choosing[i] = 0;
    ticket[i] = 0;
  }
}

int max_ticket() {
  int i, max = ticket[0];
  for (i = 1; i < num_threads; i++) {
    max = ticket[i] > max ? ticket[i] : max;
  }
  
  return max;
}

void lamport_mutex_lock(int thread_id) {
    
    int j, i = thread_id;

    choosing[i] = 1;
    ticket[i] = max_ticket() + 1;
    choosing[i] = 0;
    for (j = 0; j < num_threads; j++) {
        while (choosing[j]) 
        while (ticket[j] != 0 && (
              (ticket[j] < ticket[i]) || (ticket[j] == ticket[i] && j < i))
        );
    }
}

void lamport_mutex_unlock(int thread_id) {
  ticket[thread_id] = 0;
}

void lamport_mutex_destroy() {
  free(choosing);
  free(ticket);
}