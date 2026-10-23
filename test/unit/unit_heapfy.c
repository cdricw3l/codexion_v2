/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_heapfy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 11:35:27 by cdric.b           #+#    #+#             */
/*   Updated: 2026/10/23 15:24:17 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"
#include <string.h>





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
    i = 9;
    while (i >= 0)
    {
        node = heap_new_node(create_request(i,0,0));
        assert(heap_add_node(heap, node) == TRUE);
        heappush(heap, cmp_request_fifo);

        i--;
    }
    assert(heap->size_queue == 10);
    t_heap_node **arr = bfs_binary_tree_as_arr(heap);
    assert(arr && *arr);

    assert(((t_requests *)(arr[0]->content))->request_id  == 0);
    assert(((t_requests *)(arr[1]->content))->request_id  == 1);
    assert(((t_requests *)(arr[2]->content))->request_id  == 4);
    assert(((t_requests *)(arr[3]->content))->request_id  == 3);
    assert(((t_requests *)(arr[4]->content))->request_id  == 2);
    assert(((t_requests *)(arr[5]->content))->request_id  == 8);
    assert(((t_requests *)(arr[6]->content))->request_id  == 5);
    assert(((t_requests *)(arr[7]->content))->request_id  == 9);
    assert(((t_requests *)(arr[8]->content))->request_id  == 6);
    assert(((t_requests *)(arr[9]->content))->request_id  == 7);
    free(arr);

    heappop(heap, cmp_request_fifo, free);
    heappop(heap, cmp_request_fifo, free);
    heappop(heap, cmp_request_fifo, free);
    heappop(heap, cmp_request_fifo, free);
    heappop(heap, cmp_request_fifo, free);
    heappop(heap, cmp_request_fifo, free);
    heappop(heap, cmp_request_fifo, free);
    heappop(heap, cmp_request_fifo, free);
    heappop(heap, cmp_request_fifo, free);
    heappop(heap, cmp_request_fifo, free);
    
    assert(heap->size_queue == 0);
    assert(!*heap->queue);

    arr = bfs_binary_tree_as_arr(heap);
    assert(arr == NULL);
    
    int j = 0;
    while (arr && arr[j])
    {
        display_node(arr[j], display_request);
        j++;
    }
    
    
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