/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heappush.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 18:39:24 by cebouhad          #+#    #+#             */
/*   Updated: 2026/10/21 15:56:25 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"

int	heappush(t_heap *heap, int (*cmp)(void *p1, void *p2))
{
	t_heap_node	*current;

	current = heap_get_node(*heap->queue, (heap->size_queue));
	if (!current)
		return (FALSE);
	while (current)
	{
		if (current->parent
			&& cmp(current->content, current->parent->content))
		{
			heap_swap_node(current, current->parent);
			current = current->parent;
		}
		else
			return (TRUE);
	}
	return (TRUE);
}
