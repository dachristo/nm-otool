/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:43:00 by dchristo          #+#    #+#             */
/*   Updated: 2018/03/09 14:43:06 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm_otool.h"

void	ft_sort32(t_data32 *data, int nsyms)
{
	int i;
	int j;
	int tmp;

	i = -1;
	while (++i < nsyms)
	{
		j = -1;
		while (++j < nsyms)
		{
			if (ft_strcmp(data->stringtable +
						data->array[data->index[i]].n_un.n_strx,
						data->stringtable +
						data->array[data->index[j]].n_un.n_strx) < 0)
			{
				tmp = data->index[i];
				data->index[i] = data->index[j];
				data->index[j] = tmp;
			}
		}
	}
}

void	ft_sort64(t_data *data, int nsyms)
{
	int i;
	int j;
	int tmp;

	i = -1;
	while (++i < nsyms)
	{
		j = -1;
		while (++j < nsyms)
		{
			if (ft_strcmp(data->stringtable +
						data->array[data->index[i]].n_un.n_strx,
						data->stringtable +
						data->array[data->index[j]].n_un.n_strx) < 0)
			{
				tmp = data->index[i];
				data->index[i] = data->index[j];
				data->index[j] = tmp;
			}
		}
	}
}
