/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_pop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 04:29:53 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/24 13:34:57 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"

/*

	heap parent node = (idx - 1) / 2
	heap children left = 2 * idx + 1
	heap children right = 2 * idx + 2

*/

int		ft_memcopy(void *src, void *dst, unsigned long size);
void	*err_msg(char *err);

static void	*heap_pop_err_msg(int err_code)
{
	char	*msg;

	if (err_code == NEW_Q_ERR)
		msg = BRED"[POP ERR] new queue malloc initialisation error"CRESET"\n";
	else if (err_code == CMP_ERR)
		msg = BRED\
"[POP ERR] Please provide the comparison function for the heap reorganization."\
CRESET"\n";
	else
		return (NULL);
	return (err_msg(msg));
}

static int	get_direction(t_heap *heap, t_direction *direction,
		int (*cmp)(t_heap_node *, t_heap_node *))
{
	direction->current = heap_get_node(heap, direction->current_idx);
	direction->left = heap_get_node(heap, 2 * direction->current_idx + 1);
	direction->right = heap_get_node(heap, 2 * direction->current_idx + 2);
	if (!direction->right || !direction->left)
		direction->direction = NO_SWAP;
	if (!cmp(direction->current, direction->left)
		&& !cmp(direction->current, direction->right))
		direction->direction = NO_SWAP;
	else if (!cmp(direction->left, direction->right))
		direction->direction = SWAP_LEFT;
	else if (cmp(direction->left, direction->right))
		direction->direction = SWAP_RIGHT;
	return (direction->direction);
}

static void	heap_pop_organise(t_heap *heap,
		int (*cmp)(t_heap_node *children_l, t_heap_node *children_r))
{
	t_direction	direction;

	if (heap->heap_size == 0)
		return ;
	direction.current_idx = 0;
	get_direction(heap, &direction, cmp);
	while (direction.direction)
	{
		if (direction.direction == SWAP_RIGHT)
			heap_swap_node(direction.current, direction.right);
		else if (direction.direction == SWAP_LEFT)
			heap_swap_node(direction.current, direction.left);
		direction.current_idx = 2 * direction.current_idx + direction.direction;
		get_direction(heap, &direction, cmp);
	}
}

t_heap_node	*heap_pop(t_heap *heap, int (*cmp)(t_heap_node *, t_heap_node *))
{
	t_heap_node	**new_queue;
	t_heap_node	*node;

	if (!heap || !heap->queue || heap->heap_size <= 0)
		return (NULL);
	if (heap->heap_size == 1)
	{
		node = heap->queue[0];
		heap->heap_size--;
		*heap->queue = NULL;
		return (node);
	}
	heap_swap_node(heap->queue[0], heap->queue[heap->heap_size - 1]);
	new_queue = malloc(sizeof(t_heap_node *) * (heap->heap_size - 1));
	if (!new_queue)
		return (heap_pop_err_msg(NEW_Q_ERR));
	ft_memcopy(heap->queue, new_queue,
		sizeof(t_heap_node *) * (heap->heap_size - 1));
	node = heap_get_node(heap, heap->heap_size - 1);
	heap->heap_size--;
	free(heap->queue);
	heap->queue = new_queue;
	heap_pop_organise(heap, cmp);
	return (node);
}
