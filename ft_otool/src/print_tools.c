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

void		ft_print_hex(size_t size, int arch, char *start, char *end)
{
	ft_putstr(start);
	ft_put_zero(size, arch);
	ft_puthex(size);
	ft_putstr(end);
}

void		ft_print_section(unsigned int size)
{
	ft_put_zero(size & 0xFF, 2);
	ft_puthex(size & 0xFF);
}

void		print_arch(char *start, char *end, size_t nb)
{
	ft_putstr(start);
	ft_putnbr(nb);
	ft_putstr(end);
}

void		print_arch_hex(char *start, char *end, size_t nb)
{
	ft_putstr(start);
	ft_puthex(nb);
	ft_putstr(end);
}

void		print_arch_double(char *start, size_t nb, size_t nb2)
{
	ft_putstr(start);
	ft_putnbr(nb);
	ft_putstr(" (");
	ft_putnbr(nb2);
	ft_putstr(")\n");
}
