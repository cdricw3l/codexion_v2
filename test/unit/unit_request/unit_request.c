/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_request.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 12:36:41 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/20 00:32:04 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_request.h"

int unit_request(void)
{
	START_BLOCK;

	unit_request_init();
	unit_request_push();
	unit_request_get_last_node();
	unit_request_push();
	unit_request_pop();
	return (true);
}