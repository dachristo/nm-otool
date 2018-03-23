/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:49:51 by dchristo          #+#    #+#             */
/*   Updated: 2018/03/14 16:49:52 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/otool.h"

void		ft_putnbr(long n)
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

int			ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (((((unsigned char *)s1)[i] ||
			((unsigned char *)s2)[i])) &&
		i < n &&
		((unsigned char *)s1)[i] == ((unsigned char *)s2)[i])
		i++;
	if (i == n)
		return (0);
	return ((int)(((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]));
}

int			ft_atoi(const char *str)
{
	int		i;
	int		result;
	int		neg;

	result = 0;
	i = 0;
	neg = 1;
	while ((str[i] == ' ' || str[i] == '\t' || str[i] == '\r' || str[i] == '\n'
			|| str[i] == '\f' || str[i] == '\v') && str[i] != '\0')
	{
		i++;
	}
	if (str[i] == '-')
	{
		neg = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0' && ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * neg);
}

char		*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != (unsigned char)c && s[i] != '\0')
		i++;
	return (s[i] == '\0' ? NULL : (char *)&s[i]);
}

int			ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}
