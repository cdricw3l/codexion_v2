/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_pop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 04:29:53 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/13 08:12:43 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

/*

	heap parent node = (idx - 1) / 2
	heap children left = 2 * idx + 1
	heap children right = 2 * idx + 2

*/

#define NO_SWAP 	0
#define SWAP_LEFT	1
#define SWAP_RIGHT	2

#define NEW_Q_ERR 0
#define CMP_ERR 1


typedef struct s_direction
{
	int direction;
	t_heap_node	*current;
	t_heap_node	*left;
	t_heap_node	*right;

} t_direction;

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
	write(STDERR_FILENO, msg, ft_strlen(msg));
	return (NULL);
}

static int	get_direction(t_heap_node *current, t_heap_node *left,
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

static void	heap_pop_organise(t_heap *heap,
		int (*cmp)(t_heap_node *children_l, t_heap_node *children_r))
{
	int			direction;
	size_t		current_idx;
	t_heap_node	*current;
	t_heap_node	*left;
	t_heap_node	*right;

	if (heap->heap_size == 0)
		return ;
	current_idx = 0;
	current = heap_get_node(heap, current_idx);
	left = heap_get_node(heap, 2 * current_idx + 1);
	right = heap_get_node(heap, 2 * current_idx + 2);
	direction = get_direction(current, left, right, cmp);
	while (direction)
	{
		if (direction == SWAP_RIGHT)
			heap_swap_node(current, right);
		else if (direction == SWAP_LEFT)
			heap_swap_node(current, left);
		current_idx = 2 * current_idx + direction;
		current = heap_get_node(heap, current_idx);
		left = heap_get_node(heap, 2 * current_idx + 1);
		right = heap_get_node(heap, 2 * current_idx + 2);
		direction = get_direction(current, left, right, cmp);
	}
}

t_heap_node	*heap_pop(t_heap *heap, int (*cmp)(t_heap_node *, t_heap_node *))
{
	t_heap_node	**new_queue;
	t_heap_node	*node;


	if (!heap || !heap->queue || heap->heap_size == 0)
		return (NULL);
	
	if (!cmp)
		return (heap_pop_err_msg(CMP_ERR));
	
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
