#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void *ping(void*);
void *pong(void*);

pthread_mutex_t sync_mutex;
pthread_cond_t sync_cond;

pthread_mutex_t _mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t _cond = PTHREAD_MUTEX_INITIALIZER;

pthread_t tids[2];
int tcnt = 0;

typedef void* (*func_ptr_t)(void*);
func_ptr_t arr_pfuncs[2];
int pfuncscnt = 0;


int main()
{
    int thresult;
    int status;
    int i;

    pthread_mutex_init(&sync_mutex, NULL);
    pthread_cond_init(&sync_cond, NULL);

    arr_pfuncs[pfuncscnt++] = pong;
    arr_pfuncs[pfuncscnt++] = ping;

    for ( i = 0; i < pfuncscnt; i++)
    {
	pthread_mutex_lock(&sync_mutex);
	if (pthread_create(&tids[i], NULL, arr_pfuncs[i], (void*)NULL) < 0)
	{
	    perror("error:");
	    exit(0);
	}
	pthread_cond_wait(&sync_cond, &sync_mutex);
	pthread_mutex_unlock(&sync_mutex);
    }

    for ( i = 0; i < tcnt; i++)
    {
		pthread_join(tids[i], (void**)&status);
    }
    
    return 0;
}

void *ping(void *data)
{

    int i=0;
    pthread_mutex_lock(&sync_mutex);
    pthread_cond_signal(&sync_cond);
    pthread_mutex_unlock(&sync_mutex);
    while(1)
    {
        pthread_mutex_lock(&_mutex);
        printf("%d : ping\n", i);
        pthread_cond_signal(&_cond);
        pthread_cond_wait(&_cond, &_mutex);
        pthread_mutex_unlock(&_mutex);
        usleep(random()%100);
        i++;
    }
    return NULL;
}


void *pong(void *data)
{
    int i = 0;
    pthread_mutex_lock(&sync_mutex);
    sleep(1);
    pthread_cond_signal(&sync_cond);
    pthread_mutex_unlock(&sync_mutex);
    while(1)                              
    {
        pthread_mutex_lock(&_mutex);
        pthread_cond_wait(&_cond, &_mutex);
        printf("%d : pong\n", i);
        pthread_cond_signal(&_cond);
        pthread_mutex_unlock(&_mutex);
        i++;
    }
    
    return NULL;
}

