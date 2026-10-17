/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 18:24:47 by cdric.b           #+#    #+#             */
/*   Updated: 2026/10/17 18:32:14 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"

void	heap_clear(t_heap_node *root, void (*f)(void *))
{
	if (!root)
		return ;
	heap_clear(root->left, f);
	heap_clear(root->right, f);
	f(root->content);
	f(root);
}
