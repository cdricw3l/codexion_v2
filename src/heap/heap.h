/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 16:56:11 by cebouhad          #+#    #+#             */
/*   Updated: 2026/10/18 10:12:40 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAP_H
# define HEAP_H

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

# define HEAP_BIT_MAX 32

# include <stdlib.h>
# include <stdio.h>
# include <limits.h>

typedef struct s_heap_node
{
	void				*content;
	struct s_heap_node	*parent;
	struct s_heap_node	*left;
	struct s_heap_node	*right;

}	t_heap_node;

typedef struct s_heap
{
	size_t		size_queue;
	t_heap_node	**queue;
	int			(*add_node)(struct s_heap *heap, t_heap_node *node);
	void		(*clear_queue)(t_heap_node **queue, void (*f)(void *));
	void		(*iter_queue)(t_heap_node *root, void (f)(t_heap_node *node));
}	t_heap;

t_heap		*heap_init(void);
t_heap_node	*heap_new_node(void *content);
int			heap_add_node( t_heap *heap, t_heap_node *node);
void		heap_iter(t_heap_node *root, void (f)(t_heap_node *node));
void		heap_clear(t_heap_node **queue, void (*f)(void *));
void		heap_destroy(t_heap **heap);

#endif
