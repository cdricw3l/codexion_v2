/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_display_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 10:21:25 by cebouhad          #+#    #+#             */
/*   Updated: 2026/10/19 16:29:23 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"

void	display_node(t_heap_node *node, void (*display_content)(void *))
{
	if (!node)
		return ;
	printf("\n");
	printf("Node: %p\n", node);
	printf("Parent: %p\n", node->parent);
	printf("Left: %p\n", node->left);
	printf("Right: %p\n", node->right);
	printf("content:\n");
	display_content(node->content);
	printf("\n");
}
