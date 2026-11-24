/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_scheduler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 12:43:30 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/24 15:56:04 by cebouhad         ###   ########.fr       */
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

static void assert_dongle(int i, int dongle[2], int params[2])
{
    if (i == 0)
        assert(dongle[LEFT] == params[number_of_coders] - 1 && dongle[RIGHT] == i);
    else
        assert(dongle[LEFT] == i - 1 && dongle[RIGHT] == i );
}

static void display_heaps(t_scheduler *scheduler)
{
    int i;
    int j;
    t_request *request;

    i = 0;
    while (i < scheduler->params[number_of_coders])
    {
        j = 0;
        printf(BGRN"Heap %d"CRESET"\n", i);
        while (j < (int)scheduler->heaps[i]->heap_size)
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
    int i;
    t_request *request_1;
    t_request *request_2;
    t_heap_node *node_1;
    t_heap_node *node_2;
    int dongle[2] = {-1,-1};
    t_heap *heap_left;
    t_heap *heap_right;
    int j;
    
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
                request_2 = malloc(sizeof(t_request));
                *request_2 = *request_1;
                assert(request_1);
                assert(request_2);
                assert(!*request_1->can_compile);
                assert(!*request_2->can_compile);
                node_1 = heap_new_node(request_1);
                node_2 = heap_new_node(request_2);
                heap_left = scheduler->heaps[dongle[LEFT]];
                heap_right = scheduler->heaps[dongle[RIGHT]];
                if (debbug == ON)
                    printf("Coder: %d, heap left: %d %p dongle right: %d %p\n",i, dongle[LEFT],  heap_left, dongle[RIGHT], heap_right );
                assert(heap_left);
                assert(heap_right);
                assert(heap_push(heap_left, node_1, fifo));
                assert(heap_push(heap_right, node_2, fifo));
            }
            i++;
        }
        j++;
    }
    return (1);
}

void unit_arbitration_fifo(void)
{
    START_TEST;
    /* fifo */
    t_heap *heap;

    heap = malloc(sizeof(t_heap));
    assert(heap);
    heap->heap_size = 0;
    heap->queue = malloc(sizeof(t_heap_node *));
    assert(heap->queue);
    assert(heap);

    t_request *r1;
    t_request *r2;
    t_heap_node *h1;
    t_heap_node *h2;

    r1 = malloc(sizeof(t_request));
    assert(r1);
    r1->request_id = 1;
    r2 = malloc(sizeof(t_request));
    r2->request_id = 0;
    h1 = heap_new_node(r1);
    assert(h1);
    h2 = heap_new_node(r2);
    assert(h2);
    assert(fifo(h1, h2));
    assert(!fifo(h2, h1));

    free(r1);
    free(r2);
    free(h1);
    free(h2);
    free(heap->queue);
    free(heap);

    END_TEST;
}

void unit_arbitration_edf(int params[8])
{
    START_TEST;
    /* fifo */
    t_heap *heap;

    heap = malloc(sizeof(t_heap));
    assert(heap);
    heap->heap_size = 0;
    heap->queue = malloc(sizeof(t_heap_node *));
    assert(heap->queue);
    assert(heap);

    t_request *r1;
    t_request *r2;
    t_heap_node *h1;
    t_heap_node *h2;
    int64_t t1;
    int64_t t2;

    r1 = malloc(sizeof(t_request));
    t1 = get_now();
    r1->last_compile = &t1;
    r2 = malloc(sizeof(t_request));
    usleep(10000);
    t2 = get_now();
    r2->last_compile = &t2;
    h1 = heap_new_node(r1);
    assert(h1);
    h2 = heap_new_node(r2);
    assert(h2);
    assert(edf(h2, h1, params[time_to_burnout]));
    assert(!edf(h1, h2, params[time_to_burnout]));

    free(r1);
    free(r2);
    free(h1);
    free(h2);
    free(heap->queue);
    free(heap);

    END_TEST;
}

void unit_scheduler(void)
{
    START_BLOCK;
    START_TEST;
    t_data data;
    int params[8];

    unit_get_param(params);
    display_params(params);
    unit_arbitration_fifo();
    unit_arbitration_edf(params);
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
    who_can_compile(data.scheduler);


    /* set dongle is use variable to false manually*/
    int     i;
    size_t  j;
    t_heap *heap;
    t_request *r;

    i = 0;
    while (i < params[number_of_coders])
    {
        j = 0;

        heap = data.scheduler->heaps[i];
        assert(heap->heap_size == 1);
        while (j < heap->heap_size)
        {
            r = (t_request *)heap->queue[j]->content;
            r->dongle_l->is_used = false;
            r->dongle_r->is_used = false;
            j++;
        }
        i++;

    }
    who_can_compile(data.scheduler);
    display_heaps(data.scheduler);
    i = 0;
    while (i < params[number_of_coders])
    {
        heap = data.scheduler->heaps[i];
        assert(heap->heap_size == 0);
        i++;
    }
    clear_data(&data, 0);
    END_TEST;
}