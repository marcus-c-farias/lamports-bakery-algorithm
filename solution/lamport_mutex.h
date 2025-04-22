#ifndef lamport_mutex_h
#define lamport_mutex_h

void lamport_mutex_init(int n_threads);

void lamport_mutex_lock(int thread_num);

void lamport_mutex_unlock(int thread_num);

void lamport_mutex_destroy();

#endif