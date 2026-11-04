/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_swap_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 21:16:24 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/04 07:23:39 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"

void	heap_swap_node(t_heap_node *parent, t_heap_node *current)
{
	void	*tmp;

	if (parent == current)
		return ;
	tmp = parent->content;
	parent->content = current->content;
	current->content = tmp;
}
