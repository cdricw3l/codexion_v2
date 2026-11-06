/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_request.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 12:35:07 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/06 08:15:35 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNIT_REQUEST_H
#define UNIT_REQUEST_H

#define NB_THREAD 2


#include "../unit.h"

void unit_request_init(void);
void unit_request_new_node(void);
void unit_request_get_last_node(void);
void unit_request_push(void);
void unit_request_pop(void);

#endif