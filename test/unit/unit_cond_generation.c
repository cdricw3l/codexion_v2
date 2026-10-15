/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_cond_generation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 12:34:30 by cdric.b           #+#    #+#             */
/*   Updated: 2026/09/08 10:58:48 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"

typedef struct s_data
{
    int value;
    pthread_cond_t *cond;
    pthread_mutex_t *mutex;
    pthread_mutex_t *data_mutex;
    
} t_data;


int get_data_value(t_data *data)
{
    int value;
    pthread_mutex_lock(data->data_mutex);
    value = data->value;
    pthread_mutex_unlock(data->data_mutex);
    if (value == 0)
        return (0);
    return (1);
}

void *thread_1(void *d)
{
    t_data *data;

    data = (t_data *)d;
    printf("start thread 1\n");
    assert(data->mutex);
    pthread_mutex_lock(data->mutex);
   
    while (!get_data_value(data))
    {
        pthread_cond_wait(data->cond, data->mutex);
    }
    printf("thread 1 receive the signal from thread 2\n");
    sleep(1);
    return (NULL);
}
void *thread_2(void *d)
{
    t_data *data;

    data = (t_data *)d;
    printf("start thread 2\n");
    pthread_mutex_lock(data->data_mutex);
    sleep(1);
    data->value = 1;
    pthread_cond_signal(data->cond);
    printf("cond signal sended from thread_2\n");
    pthread_mutex_unlock(data->data_mutex);
    return (NULL);
}

int unit_cond_generation(void)
{
    START_TEST;
    t_data data;
    pthread_t thrd_1;
    pthread_t thrd_2;
    pthread_cond_t *arr_cond;
    pthread_mutex_t *arr_mutex;
    pthread_mutex_t data_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    int i;


    arr_cond = init_dynamique_cond(-10);
    assert(!arr_cond);
    arr_cond = init_dynamique_cond(10);
    assert(arr_cond);
    arr_mutex = init_dynamique_mutex(10);
    assert(arr_mutex);
    i = 0;
    while (i < 10)
    {
        data.data_mutex = NULL;
        data.value = 0;
        data.cond = &arr_cond[i];
        data.mutex = &data.mutex[i];
        data.data_mutex = &data_mutex;
        assert(data.data_mutex);
        pthread_create(&thrd_1, NULL, thread_1, &data);
        sleep(1);
        pthread_create(&thrd_2, NULL, thread_2, &data);
        pthread_join(thrd_2, NULL);
        pthread_join(thrd_1, NULL);
        printf("End of thread wait i: %d\n", i);
        i++;
    }
    assert(!pthread_mutex_destroy(data.data_mutex));
    clean_dynamique_mutex(&arr_mutex, 10);
    assert(!arr_mutex);
    clean_dynamique_cond(&arr_cond, 10);
    assert(!arr_cond);
    END_TEST;
    return (TRUE);
}