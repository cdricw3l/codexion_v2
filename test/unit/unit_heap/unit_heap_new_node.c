/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_heap_new_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 07:28:43 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/04 07:29:43 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../unit.h"

void unit_heap_new_node(void)
{
	START_TEST;
	t_heap_node *node;
	
	node = heap_new_node(NULL);
	assert(node->content == NULL);
	free(node);
	node = heap_new_node(strdup("hello world"));
	assert(strcmp((char *)node->content, "hello world") == 0);
	free(node->content);
	free(node);
	END_TEST;
}