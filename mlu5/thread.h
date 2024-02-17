#pragma once
#include <pthread.h>

typedef struct {
  pthread_t thread;
} thread;

typedef void *(*thread_func)(void* args);

void thread_kill(thread* thread);
int thread_create(thread *thread, thread_func func, void *args);
int thread_join(thread *thread, void **return_value);
