/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 13:07:51 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/20 06:50:37 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../unit.h"

void unit_get_param(int params[8])
{
    params[number_of_coders] = NB_CODER;
    params[time_to_burnout] = 410;
    params[time_to_compile] = 200;
    params[time_to_debug] = 100;
    params[time_to_refactor] = 100;
    params[number_of_compiles_required] = 10;
    params[dongle_cooldown] = 10;
    params[arbitration] = FIFO;
}



void unit_ft_isdigit(void)
{
    START_TEST;
    
    assert(!ft_is_digit(10));
    assert(!ft_is_digit(0));
    assert(!ft_is_digit(-42));
    assert(!ft_is_digit(42));
    assert(ft_is_digit(48));
    assert(ft_is_digit(49));
    assert(ft_is_digit(50));
    assert(ft_is_digit(51));
    assert(ft_is_digit(57));
    assert(!ft_is_digit(58));
    
    END_TEST;
}

int unit_utils(void)
{
    START_BLOCK;
    unit_ft_isdigit();
	return (true);
}