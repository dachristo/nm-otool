/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 17:09:31 by dchristo          #+#    #+#             */
/*   Updated: 2018/03/16 17:09:54 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/otool.h"

int		ft_puthex_nb(size_t n, int i)
{
	if (n > 15)
		i = ft_puthex_nb(n / 16, i + 1);
	return (i);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_puthex2(size_t n)
{
	char		c;

	if (n > 15)
	{
		ft_puthex2(n / 16);
		ft_puthex2(n % 16);
	}
	else
	{
		c = (n < 10) ? '0' + n : FT_HEX[n % 10];
		write(1, &c, 1);
	}
}
