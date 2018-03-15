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

int			ft_sort_alpha(char *s1, char *s2)
{
	char	*begin1;
	char	*begin2;

	begin1 = s1;
	begin2 = s2;
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
		{
			/*if ((ft_options(0, NULL, NULL) & FLAG_R))
				return ((*s1 < *s2) ? 1 : 0);
			else*/
			return ((*s1 > *s2) ? 1 : 0);
		}
		++s1;
		++s2;
	}
	/*if ((ft_options(0, NULL, NULL) & FLAG_R))
		return ((!*s1 && *s2) ? 1 : 0);
	else*/
	return ((*s1 && !*s2) ? 1 : 0);
}

static void	ft_data32(t_data32 *data, int start1, int end1, int end2)
{
	int *index2;
	int start2;
	int c1;
	int c2;
	int i;

	start2 = end1 + 1;
	c1 = start1;
	c2 = start2;
	index2 = ft_index(data->index, start1, end1);
	i = start1 - 1;
	while (++i <= end2)
	{
		if (c1 == start2)
			break ;
		else if (c2 == end2 + 1)
			data->index[i] = index2[c1++ - start1];
		else if (!ft_sort_alpha(data->stringtable + \
			data->array[index2[c1 - start1]].n_un.n_strx, \
			data->stringtable + data->array[data->index[c2]].n_un.n_strx))
			data->index[i] = index2[c1++ - start1];
		else
			data->index[i] = data->index[c2++];
	}
	free(index2);
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

static void	ft_data(t_data *data, int start1, int end1, int end2)
{
	int *index2;
	int start2;
	int c1;
	int c2;
	int i;

	start2 = end1 + 1;
	c1 = start1;
	c2 = start2;
	index2 = ft_index(data->index, start1, end1);
	i = start1 - 1;
	while (++i <= end2)
	{
		if (c1 == start2)
			break ;
		else if (c2 == end2 + 1)
			data->index[i] = index2[c1++ - start1];
		else if (!ft_sort_alpha(data->stringtable + \
			data->array[index2[c1 - start1]].n_un.n_strx, \
			data->stringtable + data->array[data->index[c2]].n_un.n_strx))
				data->index[i] = index2[c1++ - start1];
		else
			data->index[i] = data->index[c2++];
	}
	free(index2);
}

void		ft_sort64(t_data *data, int start, int end)
{
	int		mid;

	if (start != end)
	{
		mid = (end + start) / 2;
		ft_sort64(data, start, mid);
		ft_sort64(data, mid + 1, end);
		ft_data(data, start, mid, end);
	}
}
