#ifndef LAMPORT_MUTEX_H
#define LAMPORT_MUTEX_H

#ifdef __cplusplus
extern "C" {
#endif

// Número máximo de threads (pode ser configurável)
#define MAX_THREADS 1000

void lamport_mutex_init(int n_threads); //inicializa o mutex (deve ser chamada antes de qualquer lock/unlock)

void lamport_mutex_lock(int thread_id);

void lamport_mutex_unlock(int thread_id);

void lamport_mutex_destroy();

#ifdef __cplusplus
}
#endif

#endif // LAMPORT_MUTEX_H
