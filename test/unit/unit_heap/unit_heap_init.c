/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_heap_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 07:30:26 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/04 14:01:58 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../unit.h"

void unit_heap_init(void)
{
	START_TEST;

	t_heap *heap;

	heap = heap_init();
	assert(heap);
	assert(heap->heap_size == 0);
	assert(!heap->queue);
	free(heap->queue);
	free(heap);
	END_TEST;	
}

