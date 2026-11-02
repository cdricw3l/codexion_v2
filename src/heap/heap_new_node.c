/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_new_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 21:14:07 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/02 21:14:35 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"

t_heap_node	heap_new_node(void *content)
{
	t_heap_node	node;

	node.content = content;
	return (node);
}
