/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_swap_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 08:12:24 by cebouhad          #+#    #+#             */
/*   Updated: 2026/10/21 15:56:53 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"

void	heap_swap_node(t_heap_node *src, t_heap_node *dst)
{
	void	*tmp;

	tmp = src->content;
	src->content = dst->content;
	dst->content = tmp;
}
