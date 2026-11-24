/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_swap_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 21:16:24 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/24 13:36:00 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	heap_swap_node(t_heap_node *parent, t_heap_node *current)
{
	void	*tmp;

	if (!parent || parent == current)
		return ;
		
	//printf("parent %s et enfant %s\n", (char *)parent->content, (char *)current->content);
	tmp = parent->content;
	parent->content = current->content;
	current->content = tmp;
}
