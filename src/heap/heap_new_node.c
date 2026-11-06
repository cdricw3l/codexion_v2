/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_new_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 21:14:07 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/05 21:25:02 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

t_heap_node	*heap_new_node(void *content)
{
	t_heap_node	*node;
	char		*err;

	node = malloc(sizeof(t_heap_node));
	if (!node)
	{
		err = "new node malloc initialisation error\n";
		write(STDERR_FILENO, err, ft_strlen(err));
	}
	node->content = content;
	return (node);
}
