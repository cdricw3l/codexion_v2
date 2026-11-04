/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_pop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 04:29:53 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/04 07:12:38 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"

/*

	heap parent node = (idx - 1) / 2
	heap children left = 2 * idx + 1
	heap children right = 2 * idx + 2

*/

#define NO_SWAP 	0
#define SWAP_LEFT	1
#define SWAP_RIGHT	2

int	get_direction(t_heap_node *current, t_heap_node *left,
		t_heap_node *right, int (*cmp)(t_heap_node *, t_heap_node *))
{
	if (!cmp(current, left) && !cmp(current, right))
		return (NO_SWAP);
	if (!cmp(left, right))
		return (SWAP_LEFT);
	if (cmp(left, right))
		return (SWAP_RIGHT);
	return (-1);
}

static void	heap_organise(t_heap *heap, int (*cmp)(t_heap_node *children_l, t_heap_node *children_r))
{
	size_t current_idx;
	t_heap_node *current;
	t_heap_node *left;
	t_heap_node *right;
	int direction;

	current_idx = 0;
	current = heap_get_node(heap, current_idx);
	left = heap_get_node(heap, 2 * current_idx + 1);
	right = heap_get_node(heap, 2 * current_idx + 2);
	direction = get_direction(current, left, right, cmp);
	while (direction)
	{
		if (direction == NO_SWAP)
			return ;
		else if ( direction == SWAP_RIGHT)
		{
			heap_swap_node(current, right);
			current_idx = 2 * current_idx + 2;
		}
		else if (direction == SWAP_LEFT)
		{
			heap_swap_node(current, left);
			current_idx = 2 * current_idx + 1;
		}
		current = heap_get_node(heap, current_idx);
		left = heap_get_node(heap, 2 * current_idx + 1);
		right = heap_get_node(heap, 2 * current_idx + 2);
		direction = get_direction(current, left, right, cmp);
	}
}

t_heap_node	*heap_pop(t_heap *heap,int (*cmp)(t_heap_node *children_l, t_heap_node *children_r))
{
	t_heap_node **new_queue;
	t_heap_node *node;
	char 		*err;

	if (heap->heap_size == 0)
		return (NULL);
	heap_swap_node(heap->queue[0], heap->queue[heap->heap_size - 1]);
	new_queue = malloc(sizeof(t_heap_node *) * (heap->heap_size - 1));
	if (!new_queue)
	{
		err = "[POP] new queue malloc initialisation error\n";
		write(STDERR_FILENO, err, ft_strlen(err));
	}
	ft_memcopy(heap->queue, new_queue, sizeof(t_heap_node *) * (heap->heap_size - 1));
	node = heap_get_node(heap, heap->heap_size - 1);
	heap->heap_size--;
	free(heap->queue);
	heap->queue = new_queue;
	heap_organise(heap, cmp);
	return (node);
}
