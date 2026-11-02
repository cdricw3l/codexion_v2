/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 16:56:11 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/02 17:19:03 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAP_H
# define HEAP_H


#include "../../include/codexion.h"

typedef struct s_heap_node
{
	void				*content;

}	t_heap_node;

typedef struct s_heap
{
	t_heap_node	*queue;
	size_t		heap_size;		

}	t_heap;

t_heap 		*heap_init(void);
t_heap_node heap_new_node(void *content);


#endif