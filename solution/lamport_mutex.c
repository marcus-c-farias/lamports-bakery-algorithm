#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include "lamport_mutex.h"


static int *choosing;
static int *ticket;
static int num_threads = 0;


void lamport_mutex_init(int n_threads) { //inicializa o mutex (deve ser chamada antes de qualquer lock/unlock)
  int i;
  num_threads = n_threads;
  
  choosing = malloc(n_threads * sizeof(int));
  ticket = malloc(n_threads * sizeof(int));
  printf("Mutex: allocated choosing[] and ticket[] for %d threads\n", n_threads);

  

  if (!choosing || !ticket) {
    fprintf(stderr, "Erro ao alocar memória para o mutex\n");
    exit(EXIT_FAILURE);
  }

  
  for(i=0; i<num_threads; i++) {
    choosing[i] = 0;
    ticket[i] = 0;
  }
  /*
  printf("choosing[301] = %d\n", choosing[301]);
  printf("choosing[300] = %d\n", choosing[300]);
  printf("choosing[400] = %d\n", choosing[400]);
  printf("choosing[350] = %d\n", choosing[350]);
  printf("choosing[299] = %d\n", choosing[299]);
  printf("choosing[1000] = %d\n", choosing[1000]);
  
  */

}

/*
int max_ticket() {
  int max = 0;
  for (int i = 0; i < num_threads; i++) {
      if (ticket[i] > max)
          max = ticket[i];
  }
  return max;
}

*/

int max_ticket() { //retorna o maior número de ticket entre todas as threads.
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
