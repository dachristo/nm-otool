/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 15:51:04 by dchristo          #+#    #+#             */
/*   Updated: 2018/03/16 15:51:05 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm_otool.h"

int			*ft_index(int *index, int start, int end)
{
	int	i;
	int	*index2;

	if ((index2 = malloc(sizeof(int) * (end - start + 1))) == NULL)
		return (NULL);
	i = start - 1;
	while (++i <= end)
		index2[i - start] = index[i];
	return (index2);
}

int			ft_sort_numeric(int val1, int val2, t_options *options)
{
	if (options->flag_r == TRUE)
		return ((val1 < val2) ? 1 : 0);
	else
		return ((val1 > val2) ? 1 : 0);
}
