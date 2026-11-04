/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_heap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 07:41:36 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/04 07:42:10 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../unit.h"

void clean_str_heap(void *ptr)
{
	t_heap_node *node;

	node = (t_heap_node *)ptr;
	free(node->content);
	free(node);
}

int ft_cmp_max(t_heap_node *parent, t_heap_node *current)
{
	char *s_parent;
	char *s_current;
	int parent_value;
	int current_value;

	if (!parent || !current)
		return (FALSE);
	s_parent = (char *)parent->content;
	s_current = (char *)current->content;

	parent_value = atoi(s_parent);
	current_value = atoi(s_current);
	if (parent_value < current_value)
		return (TRUE);
	return (FALSE);
}