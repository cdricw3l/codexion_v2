/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_request_get_last_node.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 15:20:53 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/05 15:33:17 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_request.h"

void unit_request_get_last_node(void)
{
	START_TEST;

    t_request r1;
    t_request r2;
    t_request r3;

    r1.coder_id = 0;
    r1.next = NULL;
    assert(request_get_last_node(&r1) == &r1);
    r1.next = &r2;
    r2.coder_id = 1;
    r2.next = NULL;
    assert(request_get_last_node(&r1) == &r2);
    r2.next = &r3;
    r3.coder_id = 2;
    r3.next = NULL;
    assert(request_get_last_node(&r1) == &r3);
    assert(request_get_last_node(&r2) == &r3);
    assert(request_get_last_node(&r3) == &r3);
    assert(request_get_last_node(NULL) == NULL);
	
	END_TEST;	
}