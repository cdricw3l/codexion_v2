/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integration.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 09:52:35 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/11 10:33:39 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTEGRATION_H
#define INTEGRATION_H

#include "../include/test.h"

void start_coder_thread(t_sim *sim, t_coder *coder, t_scheduler *scheduler);
void *scheduler_routine(void *data);
#endif