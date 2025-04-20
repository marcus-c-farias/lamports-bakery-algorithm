#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

void dormir () {
  usleep((rand() % 11) * 100000); /* dormir 0, 100, 200, ..., 1000 milissegundos */
}

/* Variaveis compartilhadas */
#define N 10

int choosing [N];
int ticket [N];

int max_ticket() {
  int i, max = ticket[0];
  for (i = 1; i < N; i++)
    max = ticket[i] > max ? ticket[i] : max;
}

static void * thread_process(void *arg)
{
    int j, i = *((int *) arg);

    printf("Hello! I'm thread %d!\n", i);

    do {
      choosing[i] = 1;
      ticket[i] = max_ticket () + 1;
      choosing[i] = 0;
      for (j = 0; j < N; j++) {
              while (choosing[j]) /* nao fazer nada */;
	      while (ticket[j] != 0 && (
				      (ticket[j] < ticket[i]) || (ticket[j] == ticket[i] && j < i)
			)) /* nao fazer nada */;
      }
      
      printf("I'm thread %d and I'm entering my critical region!\n", i);
      dormir();
      printf("I'm thread %d and I'm leaving my critical region!\n", i);

      ticket[i] = 0; /* indicar que saimos da secao critica */
    } while (1);

    return NULL;
}

int main(int argc, char **argv)
{
    int thread_num, ret;
    pthread_t tinfo_process[N];
    int tinfo_id[N];
    pthread_attr_t attr;
    void *res;
    
    ret = pthread_attr_init(&attr);
    
    for (thread_num = 0; thread_num < N; thread_num++) {
	    tinfo_id [thread_num] = thread_num;
	    ret = pthread_create(&tinfo_process[thread_num], &attr, &thread_process, &tinfo_id[thread_num]);
    }

    ret = pthread_attr_destroy(&attr);
    
    for (thread_num = 0; thread_num < N; thread_num++) {
    	ret = pthread_join(tinfo_process[thread_num], &res);
    	printf("Joined with thread id %d\n", thread_num);
    	free(res);
    }

    exit(EXIT_SUCCESS);
}
