/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heapfy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 18:39:24 by cebouhad          #+#    #+#             */
/*   Updated: 2026/10/19 16:28:35 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"

int	heapfy(t_heap *heap, int (*cmp)(void *p1, void *p2))
{
	t_heap_node	*target_node;
	void		*tmp;

	target_node = heap_get_node(*heap->queue, (heap->size_queue));
	if (!target_node)
		return (FALSE);
	while (target_node)
	{
		if (target_node->parent
			&& cmp(target_node->content, target_node->parent->content))
		{
			tmp = target_node->content;
			target_node->content = target_node->parent->content;
			target_node->parent->content = tmp;
			target_node = target_node->parent;
		}
		else
			return (TRUE);
	}
	return (TRUE);
}
