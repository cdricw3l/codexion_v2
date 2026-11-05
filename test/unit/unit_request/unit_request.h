/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_request.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 12:35:07 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/05 15:35:13 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNIT_REQUEST_H
#define UNIT_REQUEST_H


#include "../unit.h"

void unit_request_init(void);
void unit_request_new_node(void);
void unit_request_get_last_node(void);
void unit_request_push(void);

#endif