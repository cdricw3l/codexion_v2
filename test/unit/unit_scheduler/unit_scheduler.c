/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_scheduler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 12:43:30 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/20 00:31:20 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_scheduler.h"

void who_can_compile(t_scheduler *scheduler);

t_request *new_request(t_coder *coder, size_t i)
{
    t_request *request;

    request = malloc(sizeof(t_request));
    assert(request);
    request->coder_id = coder->coder_id;
    request->can_compile = coder->can_compile;
    *request->can_compile = false;
    request->can_compile_cond = coder->can_compile_cond;
    request->can_compile_mu = coder->can_compile_mu;
    request->dongle_l = coder->dongle_left;
    request->dongle_r = coder->dongle_right;
    assert(!pthread_mutex_lock(coder->can_compile_mu));
    assert(!pthread_mutex_unlock(coder->can_compile_mu));
    request->request_id = i;
    return(request);
}

static void assert_dongle(size_t i, int dongle[2], int params[2])
{
    if (i == 0)
        assert(dongle[LEFT] == params[number_of_coders] - 1 && dongle[RIGHT] == i);
    else
        assert(dongle[LEFT] == i - 1 && dongle[RIGHT] == i );
}

static void display_heaps(t_scheduler *scheduler)
{
    size_t i;
    size_t j;
    t_request *request;

    i = 0;
    while (i < scheduler->params[number_of_coders])
    {
        j = 0;
        printf(BGRN"Heap %ld\n"CRESET, i);
        while (j < scheduler->heaps[i]->heap_size)
        {
            request = (t_request *)(scheduler->heaps[i]->queue[j]->content);
            printf("coder: %ld\n",request->coder_id);
            j++;
        }
        i++;
    }
}

static int init_heap_queue(int param[8], t_scheduler *scheduler, t_coder *coder ,int debbug)
{
    size_t i;
    t_request *request_1;
    t_heap_node *node_1;
    t_heap_node *node_2;
    int dongle[2] = {-1,-1};
    t_heap *heap_left;
    t_heap *heap_right;
    size_t j;
    
    j = 0;
    while (j < 2)
    {
        i = 0;
        while (i < param[number_of_coders])
        {
            if (i % 2 == j)
            {
                get_dongle_arr(i, param, dongle);
                assert_dongle(i, dongle, param);
                request_1 = new_request(&coder[i], scheduler->heaps[i]->heap_size);
                assert(request_1);
                assert(!*request_1->can_compile);
                node_1 = heap_new_node(request_1);
                node_2 = heap_new_node(request_1);
                heap_left = scheduler->heaps[dongle[LEFT]];
                heap_right = scheduler->heaps[dongle[RIGHT]];
                if (debbug == ON)
                    printf("Coder: %ld, heap left: %ld %p dongle right: %ld %p\n",i, dongle[LEFT],  heap_left, dongle[RIGHT], heap_right );
                assert(heap_left);
                assert(heap_right);
                assert(heap_push(heap_left, node_1, fifo));
                assert(heap_push(heap_right, node_2, fifo));
            }
            i++;
        }
        j++;
    }
}

void unit_scheduler(void)
{
    START_BLOCK;
    START_TEST;
   t_data data;
   
    size_t i;
     int params[8];

    unit_get_param(params);
    if(!initialisation(&data, params))
    {
        printf(BRED"Erreur d'initialisation"CRESET"\n");
        return;
    }
    assert(data.sim);
    assert(data.dongles);
    assert(data.coder);
    assert(data.scheduler);
    
    init_heap_queue(params, data.scheduler,data.coder, OFF);
    display_heaps(data.scheduler);
    who_can_compile(data.scheduler);
    who_can_compile(data.scheduler);

    clear_data(&data, 0);
    END_TEST;
}