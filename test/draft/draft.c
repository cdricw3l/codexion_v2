#include "../include/test.h"

typedef struct coder
{
    pthread_cond_t *cond_co;
    pthread_cond_t *cond_mo;
    pthread_mutex_t *mu_mo;
    pthread_mutex_t *mu_co;
    int *can_coder_compile;
    int *can_monitor;

} t_coder;

typedef struct monitor
{
    pthread_cond_t *cond_co;
    pthread_cond_t *cond_mo;
    pthread_mutex_t *mu_mo;
    pthread_mutex_t *mu_co;
    int *can_coder_compile;
    int *can_monitor;

} t_monitor;


void *monitor_routine(void *data)
{
    t_monitor *monitor;

    monitor = (t_monitor *)data;
    while (1)
    {
       
        
        printf("monitor job for 2sec\n");
        usleep(2);
        pthread_mutex_lock(monitor->mu_mo);
        *monitor->can_coder_compile = 1;
        printf("Send message to coder\n");
        pthread_cond_signal(monitor->cond_co);
        pthread_mutex_unlock(monitor->mu_co);
        usleep(2);
        pthread_mutex_lock(monitor->mu_mo);
        while (!*monitor->can_monitor)
        {
            pthread_cond_wait(monitor->cond_mo, monitor->mu_mo);
        }

    }
    
}
void *coder_routine(void *data)
{
    t_coder *coder;

    coder = (t_coder *)data;
    while (1)
    {
        pthread_mutex_lock(coder->mu_co);
        while (!(*coder->can_coder_compile))
        {
            printf("coder is waiting\n");
            pthread_cond_wait(coder->cond_co, coder->mu_co);
        }
        printf("Message recu par le coder\n");
        sleep(5);
        *coder->can_coder_compile = 0;
        pthread_mutex_unlock(coder->mu_co);
        pthread_mutex_lock(coder->mu_mo);
        *coder->can_monitor = 1;
        pthread_mutex_unlock(coder->mu_mo);
        pthread_cond_signal(coder->cond_mo);
    }
    
}


int main(void)
{
    pthread_t thread_m;
    pthread_t thread_c;
    int can_compile;
    int can_monitor;
    t_coder coder;
    t_monitor monitor;
    pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
    pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t mu1 = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t mu2 = PTHREAD_MUTEX_INITIALIZER;


    coder.mu_co = &mu1;
    coder.mu_mo = &mu2;

    monitor.mu_co = &mu1;
    monitor.mu_mo = &mu2;

    coder.cond_co = &cond1;
    monitor.cond_co = &cond1;

    coder.cond_mo = &cond2;
    monitor.cond_mo = &cond2;

    can_compile = 0;
    can_monitor = 0;
    monitor.can_coder_compile = &can_compile;
    coder.can_coder_compile = &can_compile;
    monitor.can_monitor = &can_monitor;
    coder.can_monitor = &can_monitor;

  

    pthread_create(&thread_m, NULL, monitor_routine, &monitor);
    sleep(1);
    pthread_create(&thread_c, NULL, coder_routine, &coder);

    pthread_join(thread_c, NULL);
    pthread_join(thread_m, NULL);

    return (0);
}