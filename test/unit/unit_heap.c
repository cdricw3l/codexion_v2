/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_heap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 11:35:27 by cdric.b           #+#    #+#             */
/*   Updated: 2026/10/23 20:09:44 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"
#include <string.h>

#define TREE_SIZE 10

static void	assert_heappop(t_heap *heap)
{
	START_TEST;
	size_t size;

	size = heap->size_queue;
	while (heappop(heap, cmp_request_fifo, free))
	{
		assert(heap->size_queue == size - 1);
		size--;
	}
	assert(heap->size_queue == 0);
	assert(!*heap->queue);
	heappop(heap, cmp_request_fifo, free);      /*--> check the heappop fonction whith empty queue */
	heappop(NULL, cmp_request_fifo, free);      /*--> check the heappop fonction whith NULL heap */
	END_TEST;
}

static void assert_heappush(t_heap *heap, int nb_of_node)
{
	
	START_TEST;
	t_heap_node *node;
	t_heap_node **arr;
	
	while (nb_of_node >= 0)
	{
		node = heap_new_node(create_request(nb_of_node,0,0));
		assert(heappush(heap, node, cmp_request_fifo));
		nb_of_node--;
	}
	assert(heap->size_queue == 10);
	arr = bfs_binary_tree_as_arr(heap);
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

	/* this part check the null pointer managment of the heappush fonction */
	assert(heappush(heap, NULL, cmp_request_fifo) == FALSE);
	node = heap_new_node(create_request(100,0,0));
	assert(node);
	assert(heappush(NULL, node, cmp_request_fifo) == FALSE);
	free(node);
	node = NULL;
	assert(heappush(NULL, NULL, cmp_request_fifo) == FALSE);

	END_TEST;
}

int unit_heap(void)
{
	t_heap *heap;
	
	heap = heap_init();             /*--> heap initialisation */
   
	assert(heap);                   /*--> check if the heap allocation is OK */
	assert(heap->queue);            /*--> check if the heap queue allocation is OK */
	assert(!*heap->queue);          /*--> check if the heap queue is empty and pointe to NULL */
	assert(heap->size_queue == 0);  /*--> check if the heap size queue is equal to zero */
	
	assert_heappush(heap, 9);          /*--> create a new binary heap of 10 elements */
	heap_clear(heap, free);         /*--> destroy the ten node of the heap   */

	assert(heap->queue);            /*--> check if heap existe after clean  */
	assert(!*heap->queue);          /*--> check if heap queue is empty  */
	assert(heap->size_queue == 0);  /*--> check if heap size queue  is equal to zero  */
	
	assert_heappush(heap, 9);          /*--> create a new binary heap of 10 elements */
	assert_heappop(heap);           /*--> clear the queue with the heappop fonction*/
	
	assert(heap->queue);            /*--> check if heap existe after clean  */
	assert(!*heap->queue);          /*--> check if heap queue is empty  */
	assert(heap->size_queue == 0);  /*--> check if heap size queue  is equal to zero  */

	heap_destroy(&heap);			/*--> destroy the heap */
	assert(!heap);					/*--> check if heap == NULL */

	return (TRUE);
}