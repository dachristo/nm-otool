/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <kperreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 17:07:21 by kperreau          #+#    #+#             */
/*   Updated: 2015/09/23 17:17:35 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/otool.h"

void	ft_put_zero(size_t size, int arch)
{
	int nb;

	nb = ft_puthex_nb(size, 1);
	while (arch > nb++)
		ft_putchar('0');
}
