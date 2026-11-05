/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_get_last_node.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 15:18:33 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/05 15:32:12 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "request.h"

t_request *request_get_last_node(t_request *current)
{
    if (!current)
        return (NULL);
    while (current->next)
        current = current->next;
    return (current);    
}