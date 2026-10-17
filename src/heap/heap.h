/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 16:56:11 by cebouhad          #+#    #+#             */
/*   Updated: 2026/10/17 17:02:53 by cebouhad         ###   ########.fr       */
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

int			heap_add_node(t_heap_node **heap, t_heap_node *node,
				size_t *heap_size);
void		heap_clear(t_heap_node *root, void (*f)(void *));
t_heap_node	*heap_new_node(void *content);

#endif
