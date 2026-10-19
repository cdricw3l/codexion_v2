/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_get_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 17:38:59 by cebouhad          #+#    #+#             */
/*   Updated: 2026/10/19 16:29:48 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"

static int	get_path(int target_node_idx, char buffer[HEAP_BIT_MAX + 1])
{
	int	i;
	int	on;
	int	bit;

	i = 0;
	on = 0;
	bit = HEAP_BIT_MAX - 1;
	if (target_node_idx > INT_MAX)
		return (FALSE);
	while (bit >= 0)
	{
		if (!on && ((target_node_idx >> bit) & 1) == 1)
		{
			on = 1;
			bit--;
			continue ;
		}
		if (on)
			buffer[i++] = ((target_node_idx >> bit) & 1) + '0';
		bit--;
	}
	buffer[i] = '\0';
	return (TRUE);
}

t_heap_node	*heap_get_node(t_heap_node *root, int target_node_idx)
{
	size_t		i;
	char		path[HEAP_BIT_MAX + 1];

	if (get_path(target_node_idx, path) == FALSE)
	{
		printf("Heap queue is full\n");
		return (FALSE);
	}
	i = 0;
	while (path[i])
	{
		if (path[i] == '1')
			root = root->right;
		else if (path[i] == '0')
			root = root->left;
		i++;
	}
	return (root);
}
