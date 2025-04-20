#ifndef lamport_mutex  
#define lamport_mutex

//#define MAX_THREADS 1000

void lamport_mutex_init();
void lamport_mutex_lock(int thread_id);
void lamport_mutex_unlock(int thread_id);
void lamport_mutex_destroy();

#endif