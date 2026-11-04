/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_heap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 07:41:36 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/04 14:33:00 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_heap.h"

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

int ft_cmp_min(t_heap_node *parent, t_heap_node *current)
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
	if (parent_value > current_value)
		return (TRUE);
	return (FALSE);
}

void display_heap(t_heap *heap)
{
	size_t i;

	i = 0;
	while (i < heap->heap_size)
		printf("Heap node value: %s\n", (char *)heap->queue[i++]->content);
	
}

int is_heap_ok(t_heap *heap, int type)
{
	size_t i;
	size_t j;

	i = 0;
	j = i + 1;
	while (j < heap->heap_size)
	{
		if (type == HEAP_TYPE_MAX)
		{
			if (atoi(heap->queue[i]->content) < atoi(heap->queue[j]->content))
				return (0);
		}
		else if (type == HEAP_TYPE_MIN)
		{
			if (atoi(heap->queue[i]->content) > atoi(heap->queue[j]->content))
				return (0);
		}
		j++;
	}
	return (1);
}