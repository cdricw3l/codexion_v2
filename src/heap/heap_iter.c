/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_iter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 09:58:53 by cebouhad          #+#    #+#             */
/*   Updated: 2026/10/18 10:13:26 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"

void	heap_iter(t_heap_node *root, void (f)(t_heap_node *node))
{
	if (!root)
		return ;
	heap_iter(root->left, f);
	f(root);
	heap_iter(root->right, f);
}
