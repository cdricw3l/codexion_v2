/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 13:07:51 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/02 13:19:47 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"

void unit_ft_strlen(void)
{
    START_TEST;
    
    assert(ft_strlen(NULL) == 0);
    assert(ft_strlen("") == strlen(""));
    assert(ft_strlen("hello world") == strlen("hello world"));
    assert(ft_strlen("\n\n]ndwqdhello world") == strlen("\n\n]ndwqdhello world"));

    END_TEST;
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
	unit_ft_strlen();
    unit_ft_isdigit();
	return (TRUE);
}