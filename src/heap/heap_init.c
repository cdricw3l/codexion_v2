/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 09:01:04 by cebouhad          #+#    #+#             */
/*   Updated: 2026/10/18 10:01:01 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"

t_heap	*heap_init(void)
{
	t_heap	*heap;

	heap = malloc(sizeof(t_heap));
	if (!heap)
	{
		printf("Error heap allocation %d\n", __LINE__ - 3);
		return (NULL);
	}
	heap->queue = malloc(sizeof(t_heap_node *));
	if (!heap->queue)
	{
		printf("Error queue allocation %d\n", __LINE__ - 3);
		free(heap);
		return (NULL);
	}
	*heap->queue = NULL;
	heap->size_queue = 0;
	heap->add_node = heap_add_node;
	heap->iter_queue = heap_iter;
	heap->clear_queue = heap_clear;
	return (heap);
}
