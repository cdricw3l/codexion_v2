/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 16:56:11 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/05 11:28:24 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAP_H
# define HEAP_H

# include "../../include/codexion.h"

typedef struct s_heap_node
{
	void				*content;

}	t_heap_node;

typedef struct s_heap
{
	t_heap_node	**queue;
	size_t		heap_size;		

}	t_heap;

t_heap		*heap_init(void);
t_heap_node	*heap_new_node(void *content);
void		heap_swap_node(t_heap_node *parent, t_heap_node *current);
void		heap_clear(t_heap **heap, void (*del)(void *));
int			heap_push(t_heap *heap, t_heap_node *node,
				int (*cmp)(t_heap_node *parent, t_heap_node *current));
t_heap_node	*heap_pop(t_heap *heap, int (*cmp)(t_heap_node *, t_heap_node *));
t_heap_node	*heap_get_node(t_heap *heap, size_t idx);
#endif