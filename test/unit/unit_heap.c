/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_heap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 11:35:27 by cdric.b           #+#    #+#             */
/*   Updated: 2026/11/02 13:01:16 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"

void unit_heap_init(void)
{
	START_TEST;

	t_heap *heap;

	heap = heap_init();
	assert(heap);
	assert(heap->heap_size == 0);
	assert(heap->queue == NULL);

	END_TEST;	
}


int unit_heap(void)
{
	unit_heap_init();
	return (TRUE);
}