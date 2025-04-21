#include <stdio.h>
#include <stdlib.h>
#include "lamport_mutex.h"

static int *choosing;
static int *ticket;
static int num_threads = 0;

void lamport_mutex_init(int n_threads) {
  int i;
  num_threads = n_threads;
  
  choosing = malloc(num_threads * sizeof(int));
  ticket = malloc(num_threads * sizeof(int));

  if (!choosing || !ticket) {
    fprintf(stderr, "Allocating error memory for the mutex.\n");
    exit(EXIT_FAILURE);
  }
  
  for(i=0; i<num_threads; i++) {
    choosing[i] = 0;
    ticket[i] = 0;
  }
}

int max_ticket() {
  int i, max = ticket[0];
  //printf("Debug max1");

  for (i = 1; i < num_threads; i++) {
    max = ticket[i] > max ? ticket[i] : max;
  }
  //printf("Debug max2");
  return max;
}

void lamport_mutex_lock(int thread_id) {
    
    int j, i = thread_id;

    //printf("Thread %d locking...\n", thread_id);

    //printf("Debug1");
    choosing[i] = 1; //locka thread para ela escolher uma senha
    //printf("Debug2");

    ticket[i] = max_ticket() + 1; //thread escolhe uma senha
    //printf("Ticket of thread %d: %d\n", thread_id, ticket[i]);


    choosing[i] = 0; //libera thread, ja escolheu a senha

    //printf("num_threads: %d\n", num_threads);

    for (j = 0; j < num_threads; j++) {

          //printf("choosing[j]: %d\n", choosing[j]);
          while (choosing[j]) { //Espera todas as outras threads escolherem suas senhas.

          }

          //printf("ticket[j]: %d  ticket[i]: %d\n", ticket[j], ticket[i]);

        while (ticket[j] != 0 && ((ticket[j] < ticket[i]) || (ticket[j] == ticket[i] && j < i))) {
          /* nao fazer nada */
        } 
        
    }

}


void lamport_mutex_unlock(int thread_id) {

  //printf("Thread %d unlocking...\n", thread_id);
  ticket[thread_id] = 0;
}


void lamport_mutex_destroy() {
  free(choosing);
  free(ticket);
}