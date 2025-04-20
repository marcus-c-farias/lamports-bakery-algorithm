#ifndef lamport_mutex  
#define lamport_mutex

void lamport_mutex_init();
void lamport_mutex_lock(int thread_id);
void lamport_mutex_unlock(int thread_id);

#endif