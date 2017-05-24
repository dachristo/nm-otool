/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 13:43:48 by dchristo          #+#    #+#             */
/*   Updated: 2017/05/24 15:48:28 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm-otool.h"

static int		ft_strlen(char *str)
{
	int			i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void			ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

void			ft_putnbr(long n)
{
	char		c;

	if (n < 0)
	{
		c = '-';
		write(1, &c, 1);
		n *= -1;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		c = n % 10 + '0';
		write(1, &c, 1);
	}
	else if (n < 10)
	{
		c = n + '0';
		write(1, &c, 1);
	}
}
