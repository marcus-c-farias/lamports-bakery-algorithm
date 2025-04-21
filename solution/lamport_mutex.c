#include <stdio.h>
#include <stdlib.h>
#include "lamport_mutex.h"

int N;
int *choosing;
int *ticket;

void lamport_mutex_init(int num_threads) {
  printf("INICIALIZANDO lamport_mutex_init\n");

  N = num_threads;
  choosing = malloc(N * sizeof(int));
  ticket = malloc(N * sizeof(int));
  
  if (!choosing || !ticket) {
    fprintf(stderr, "Allocating error memory for mutex.\n");
    exit(EXIT_FAILURE);
  }

  // //ALOCA TUDO COMO ZERO, N PRECISA DISSO
  // for(int i = 0; i < num_threads; i++) {
    
  //   printf("Choosing[%d]: %d\n",i,choosing[i]);
  //   printf("Ticket[%d]: %d\n",i,ticket[i]);
  //   // choosing[i] = 0;
  //   // ticket[i] = 0;
  // }

  printf("ENCERRANDO lamport_mutex_init\n");
}

int max_ticket() {
  int i, max = ticket[0];
  for (i = 1; i < N; i++)
    max = ticket[i] > max ? ticket[i] : max;

  return max; //pq no original n tem o return
}

void lamport_mutex_lock(int thread_num) {
  printf("Locking... Thread: %d.\n", thread_num);
    
  int i, j = thread_num;
  choosing[i] = 1;
  ticket[i] = max_ticket () + 1;
  choosing[i] = 0;

  for (j = 0; j < N; j++) {
    while (choosing[j])
    while (ticket[j] != 0 && 
          ((ticket[j] < ticket[i]) || (ticket[j] == ticket[i] && j < i))
    );
  }
}


void lamport_mutex_unlock(int thread_num) {
  printf("Unlocking... Thread: %d.\n", thread_num);
  ticket[thread_num] = 0;
}


void lamport_mutex_destroy() {
  printf("INICIALIZANDO lamport_mutex_destroy\n");
  free(choosing);
  free(ticket);
  printf("ENCERRANDO lamport_mutex_destroy\n");
}