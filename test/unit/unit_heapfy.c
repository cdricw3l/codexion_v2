/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_heapfy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 11:35:27 by cdric.b           #+#    #+#             */
/*   Updated: 2026/10/19 16:34:25 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"
#include <string.h>


t_requests *create_request(int request_id, int coder_id, clock_t last_compilation)
{
    t_requests *request;

    request = malloc(sizeof(t_requests));
    if (!request)
    {
        perror("Error creation request:");
        return (NULL);
    }
    request->coder_id = coder_id;
    request->request_id = request_id;
    request->coder_last_compilation = last_compilation;
    return (request);
}
void display_request(void *ptr)
{
    t_requests *request;

    request = (t_requests *)ptr;
    NL;
    printf("Coder id: %zu\n", request->coder_id);
    printf("Request id: %zu\n", request->request_id);
    printf("Last compilation: %lu\n", request->coder_last_compilation);
    NL;

}











void print_bit(int value, int bit)
{
    int size;

    size = bit -1;
    while (size >= 0)
    {
        printf("%d", value >> size & 1);
        size--;
    }
    NL;
}

int manual_heapfy(void)
{
    t_heap_node *node_1;
    t_heap_node *node_2;
    t_heap_node *node_3;
    t_heap_node *node_4;
    t_heap_node *node_5;
    t_heap_node *node_6;
    t_heap_node *node_7;
    t_heap_node *node_8;
    t_heap_node *node_9;
    t_heap_node *node_10;
    t_heap_node *node_11;
    t_heap_node *node_12;
    t_heap *heap;

    heap = heap_init();
    if (!heap)
        return (FALSE);
    node_1 = heap_new_node(strdup("1"));
    node_2 = heap_new_node(strdup("2"));
    node_3 = heap_new_node(strdup("3"));
    node_4 = heap_new_node(strdup("4"));
    node_5 = heap_new_node(strdup("5"));
    node_6 = heap_new_node(strdup("6"));
    node_7 = heap_new_node(strdup("7"));
    node_8 = heap_new_node(strdup("8"));
    node_9 = heap_new_node(strdup("9"));
    node_10 = heap_new_node(strdup("10"));
    node_11 = heap_new_node(strdup("11"));
    node_12 = heap_new_node(strdup("12"));
    
    node_1->left = node_2;
    node_1->right = node_3;

    node_2->left = node_4;
    node_2->right = node_5;
    
    node_3->left = node_6;
    node_3->right = node_7;

    node_4->left = node_8;
    node_4->right = node_9;

    node_5->left = node_10;
    node_5->right = node_11;

    heap->size_queue = 11;
    *heap->queue = node_1;
    
    heap_add_node(heap, node_12);

    //heap_iter(*queue, print_node);
    assert(heap->size_queue == 12);
    return (TRUE);
}


int cmp_request(void *r1, void *r2)
{
    t_requests *request_1;
    t_requests *request_2;

    request_1 = (t_requests *)r1;
    request_2 = (t_requests *)r2;

    if (request_1->request_id < request_2->request_id)
        return (TRUE);
    return (FALSE);
}

int auto_heapfy(void)
{
    t_heap *heap;
    t_heap_node *node;
    int         i;

    heap = heap_init();
    if (!heap)
        return (FALSE);
    assert(heap->queue);
    assert(!*heap->queue);
    assert(heap->size_queue == 0);
    i = 1;
    while (i <= 10)
    {
        node = heap_new_node(create_request(i,0,0));
        assert(heap_add_node(heap, node) == TRUE);
        i++;
    }
    assert(heap_add_node(heap, heap_new_node(create_request(0,0,0))) == TRUE);
    heapfy(heap, cmp_request);
    heap_iter(*heap->queue, display_node, display_request);
    heap_clear(heap->queue, free);
    assert(*heap->queue == NULL);
    heap_destroy(&heap);
    assert(!heap);
    return (TRUE);
}

int unit_heapfy(void)
{
    auto_heapfy();
    return (TRUE);
}