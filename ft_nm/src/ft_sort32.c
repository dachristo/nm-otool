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

static int	ft_sort_alpha32(t_data32 *data, t_sort sort, t_options *options,
							int start1)
{
	char	*s1;
	char	*s2;

	s1 = data->stringtable +
		data->array[sort.index2[sort.c1 - start1]].n_un.n_strx;
	s2 = data->stringtable +
		data->array[data->index[sort.c2]].n_un.n_strx;
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
		{
			if (options->flag_r == TRUE)
				return ((*s1 < *s2) ? 1 : 0);
			else
				return ((*s1 > *s2) ? 1 : 0);
		}
		++s1;
		++s2;
	}
	if (options->flag_r == TRUE)
		return ((!*s1 && *s2) ? 1 : 0);
	else
		return ((*s1 && !*s2) ? 1 : 0);
}

static int	ft_sort_same32(t_data32 *data, t_sort sort, int start1)
{
	return (ft_strcmp(data->stringtable +
					data->array[sort.index2[sort.c1 - start1]].n_un.n_strx,
					data->stringtable +
					data->array[data->index[sort.c2]].n_un.n_strx)
			== 0 &&
			ft_sort_numeric(data->array[sort.index2[sort.c1 - start1]].n_value,
			data->array[data->index[sort.c2]].n_value,
			data->ptr_file->options));
}

static void	ft_data32(t_data32 *data, int start1, int end1, int end2)
{
	t_sort	sort;
	int		i;

	sort.c1 = start1;
	sort.c2 = end1 + 1;
	sort.index2 = ft_index(data->index, start1, end1);
	i = start1 - 1;
	while (++i <= end2)
	{
		if (sort.c1 == end1 + 1)
			break ;
		else if (sort.c2 == end2 + 1)
			data->index[i] = sort.index2[sort.c1++ - start1];
		else if (!ft_sort_alpha32(data, sort, data->ptr_file->options, start1))
		{
			if (ft_sort_same32(data, sort, start1))
				data->index[i] = data->index[sort.c2++];
			else
				data->index[i] = sort.index2[sort.c1++ - start1];
		}
		else
			data->index[i] = data->index[sort.c2++];
	}
	free(sort.index2);
}

void		ft_sort32(t_data32 *data, int start, int end)
{
	int		mid;

	if (start != end)
	{
		mid = (end + start) / 2;
		ft_sort32(data, start, mid);
		ft_sort32(data, mid + 1, end);
		ft_data32(data, start, mid, end);
	}
}
