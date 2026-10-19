/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_add_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 17:40:06 by cdric.b           #+#    #+#             */
/*   Updated: 2026/10/18 17:42:08 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"

int	heap_add_node( t_heap *heap, t_heap_node *node)
{
	t_heap_node	*target_node;

	if (!heap || !node)
		return (FALSE);
	if (!(*heap->queue))
	{
		*heap->queue = node;
		heap->size_queue++;
		return (TRUE);
	}
	target_node = heap_get_node(*heap->queue, (heap->size_queue + 1) / 2);
	if (!target_node)
		return (FALSE);
	if ((heap->size_queue + 1) % 2 == 0 && !target_node->left)
		target_node->left = node;
	else if ((heap->size_queue + 1) % 2 != 0 && !target_node->right)
		target_node->right = node;
	else
		return (FALSE);
	node->parent = target_node;
	heap->size_queue++;
	return (TRUE);
}
