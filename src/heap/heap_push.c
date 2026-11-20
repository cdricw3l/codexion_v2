/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 21:11:29 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/20 00:32:04 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static void	heap_push_organise(t_heap *heap,
		int (*cmp)(t_heap_node *, t_heap_node *))
{
	int			idx_current;
	int			idx_parent;

	idx_current = heap->heap_size - 1;
	idx_parent = ((idx_current - 1)) / 2;
	while (idx_parent >= 0
		&& cmp(heap->queue[idx_parent], heap->queue[idx_current]))
	{
		heap_swap_node(heap->queue[idx_parent], heap->queue[idx_current]);
		idx_current = idx_parent;
		idx_parent = ((idx_parent - 1)) / 2;
	}
}

int	heap_push(t_heap *heap, t_heap_node *node,
		int (*cmp)(t_heap_node *, t_heap_node *))
{
	t_heap_node	**new_queue;

	if (!heap || !cmp)
		return (false);
	new_queue = malloc(sizeof(t_heap_node *) * (heap->heap_size + 1));
	if (!new_queue)
		return (false);
	ft_memcopy(heap->queue, new_queue, sizeof(t_heap_node *) * heap->heap_size);
	if (heap->queue)
		free(heap->queue);
	new_queue[heap->heap_size] = node;
	heap->queue = new_queue;
	heap->heap_size++;
	if (heap->heap_size < 2)
		return (true);
	heap_push_organise(heap, cmp);
	return (true);
}
