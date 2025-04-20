#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>

#define handle_error_en(en, msg) \
  do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
  do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define num_threads 3

int shared_var = 0;
int num_rep = 3000000;

// MUTEX CODE BEGIN
pthread_mutex_t lock;
// MUTEX CODE END

struct thread_info {
    pthread_t id;
    int num;
};

static void * thread_start(void *arg)
{
    struct thread_info *tinfo = arg;
    
    printf("Hello! I'm thread %d, id %lu!\n", tinfo->num, tinfo->id);
    for (int i = 0; i < num_rep; i++) {
        // MUTEX CODE BEGIN
        pthread_mutex_lock(&lock);
        shared_var = shared_var + 1;
        pthread_mutex_unlock(&lock);
        // MUTEX CODE END
    }
    
    return 0x0;
}

int main(int argc, char **argv)
{
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    int thread_num, ret;
    struct thread_info tinfo[num_threads];
    pthread_attr_t attr;
    void *res;
    
    // MUTEX CODE BEGIN    
    ret = pthread_mutex_init(&lock, NULL);
    if (ret != 0)
        handle_error_en(ret, "pthread_mutex_init");
    // MUTEX CODE END
    
    if (argc > 1)
        num_rep = strtol(argv[1], NULL, 10);
    
    ret = pthread_attr_init(&attr);
    if (ret != 0)
        handle_error_en(ret, "pthread_attr_init");

    /* Create one thread for each command-line argument */    
    for (thread_num = 0; thread_num < num_threads; thread_num++) {
        tinfo[thread_num].num = thread_num + 1;
        
        ret = pthread_create(&tinfo[thread_num].id, &attr, &thread_start, &tinfo[thread_num]);
        if (ret != 0)
            handle_error_en(ret, "pthread_create");
    }
    
    ret = pthread_attr_destroy(&attr);
    if (ret != 0)
        handle_error_en(ret, "pthread_attr_destroy");
        
    for (thread_num = 0; thread_num < num_threads; thread_num++) {
        ret = pthread_join(tinfo[thread_num].id, &res);
        if (ret != 0)
            handle_error_en(ret, "pthread_join");
        
        printf("Joined with thread %d, id %lu\n", tinfo[thread_num].num, tinfo[thread_num].id);
        free(res); /* Free memory allocated by thread */
    }
    
    // MUTEX CODE BEGIN
    pthread_mutex_destroy(&lock);
    // MUTEX CODE END

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\n");
    printf("Global var: %d\n", shared_var);
    printf("CPU time used: %f seconds\n\n", cpu_time_used);
    
    exit(EXIT_SUCCESS);
}
