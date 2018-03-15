/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:40:00 by dchristo          #+#    #+#             */
/*   Updated: 2018/03/09 14:40:01 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm_otool.h"

static void	ft_put_sym_sec(struct nlist_64 *array, char **sec_str)
{
	if (array->n_sect)
	{
		if (!ft_strcmp(sec_str[array->n_sect - 1], SECT_TEXT))
			(array->n_type & 1) ? ft_putstr("T") : ft_putstr("t");
		else if (!ft_strcmp(sec_str[array->n_sect - 1], SECT_BSS))
			(array->n_type & 1) ? ft_putstr("B") : ft_putstr("b");
		else if (!ft_strcmp(sec_str[array->n_sect - 1], SECT_DATA))
			(array->n_type & 1) ? ft_putstr("D") : ft_putstr("d");
		else
			(array->n_type & 1) ? ft_putstr("S") : ft_putstr("s");
	}
}

static void	ft_put_sym_type(struct nlist_64 *array, char **sec_str)
{
	ft_putstr(" ");
	if ((array->n_type & N_TYPE) == N_UNDF)
		(array->n_value) ? ft_putstr("C") : ft_putstr("U");
	else if ((array->n_type & N_TYPE) == N_ABS)
		ft_putstr("A");
	else if ((array->n_type & N_TYPE) == N_INDR)
		ft_putstr("I");
	else if ((array->n_type & N_TYPE) == N_SECT)
		ft_put_sym_sec(array, sec_str);
	ft_putstr(" ");
}

static void	ft_put_indirect(t_data *data, int i)
{
	ft_putstr(data->stringtable + data->array[data->index[i]].n_un.n_strx);
	ft_putstr(" (indirect for ");
	ft_putstr(data->stringtable + data->array[data->index[i]].n_value);
	ft_putchar(')');
}

void		ft_print_out64(t_data *data, char **sec_str, int n)
{
	int i;

	i = -1;
	while (++i < n)
	{
		if (data->array[data->index[i]].n_type & N_STAB)
			continue;
		if ((((data->array[data->index[i]].n_type & N_TYPE) != N_UNDF ||
				data->array[data->index[i]].n_value) &&
				(data->array[data->index[i]].n_type & N_TYPE) != N_INDR))
		{
			ft_putstr("0000000");
			ft_puthex(data->array[data->index[i]].n_value);
		}
		else
			ft_putstr("                ");
		ft_put_sym_type(&data->array[data->index[i]], sec_str);
		if ((data->array[data->index[i]].n_type & N_TYPE) == N_INDR)
			ft_put_indirect(data, i);
		else
			ft_putstr(data->stringtable +
							data->array[data->index[i]].n_un.n_strx);
		ft_putstr("\n");
	}
}
