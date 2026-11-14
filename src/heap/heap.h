/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 09:53:29 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/14 14:32:22 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAP_H
# define HEAP_H

# include <sys/types.h>
# include <stdlib.h>
# include <unistd.h>
# include "../../include/color_codes.h"

# define NO_SWAP 	0
# define SWAP_LEFT	1
# define SWAP_RIGHT	2
# define NEW_Q_ERR 0
# define CMP_ERR 1

typedef struct s_heap_node
{
	void				*content;
}	t_heap_node;

typedef struct s_heap
{
	t_heap_node	**queue;
	size_t		heap_size;

}	t_heap;

typedef struct s_direction
{
	int			direction;
	size_t		current_idx;
	t_heap_node	*current;
	t_heap_node	*left;
	t_heap_node	*right;

}	t_direction;

t_heap		*heap_init(void);
t_heap_node	*heap_new_node(void *content);
void		heap_swap_node(t_heap_node *parent, t_heap_node *current);
void		heap_clear(t_heap **heap, void (*del)(void *));
int			heap_push(t_heap *heap, t_heap_node *node,
				int (*cmp)(t_heap_node *, t_heap_node *));
t_heap_node	*heap_pop(t_heap *heap, int (*cmp)(t_heap_node *, t_heap_node *));
t_heap_node	*heap_get_node(t_heap *heap, size_t idx);

#endif