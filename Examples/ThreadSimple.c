#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

#define handle_error_en(en, msg) \
  do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
  do { perror(msg); exit(EXIT_FAILURE); } while (0)
      
#define num_threads 10

static void * thread_start(void *arg)
{
    pthread_t *tinfo = arg;
    
    printf("Hello! I'm thread %lu!\n", *tinfo);

    return NULL;
}

int main(int argc, char **argv)
{
    int thread_num, ret;
    pthread_t tinfo[num_threads];
    pthread_attr_t attr;
    void *res;
    
    ret = pthread_attr_init(&attr);
    if (ret != 0)
        handle_error_en(ret, "pthread_attr_init");
    
    for (thread_num = 0; thread_num < num_threads; thread_num++) {        
        
        ret = pthread_create(&tinfo[thread_num], &attr, &thread_start, &tinfo[thread_num]);
        if (ret != 0)
            handle_error_en(ret, "pthread_create");
    }
    
    ret = pthread_attr_destroy(&attr);
    if (ret != 0)
        handle_error_en(ret, "pthread_attr_destroy");
        
    for (thread_num = 0; thread_num < num_threads; thread_num++) {
        ret = pthread_join(tinfo[thread_num], &res);
        if (ret != 0)
            handle_error_en(ret, "pthread_join");
        
        printf("Joined with thread id %lu\n", tinfo[thread_num]);
        free(res);
    }
    
    exit(EXIT_SUCCESS);
}
